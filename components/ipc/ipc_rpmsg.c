 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <unistd.h>
#include <string.h>
#include <assert.h>

#include <aos/debug.h>
#include <aos/aos.h>
#include <csi_core.h>

#include "rpmsg_lite.h"
#include "rpmsg_queue.h"
#include "rpmsg_ns.h"
#include "internal.h"

#ifndef CONFIG_IPC_SERVICE_TASK_STACK_SIZE
#define CONFIG_IPC_SERVICE_TASK_STACK_SIZE 4096
#endif

#define IPC_WRITE_EVENT CHANNEL_WRITE_EVENT
#define IPC_READ_EVENT  CHANNEL_READ_EVENT

#define RPMSG_LITE_SHMEM_BASE 0x1E000000
#define RPMSG_LITE_LINK_ID    (0)

#define RPMSG_LITE_NS_ANNOUNCE_STRING "rpmsg-virtual-char-channel-1"

#define MIN(a, b) (a) < (b) ? (a) : (b)

#define TAG "ipc"
static slist_t ipc_list;

static service_t *find_service(ipc_t *ipc, int service_id)
{
    service_t *ser;

    slist_for_each_entry(&ipc->service_list, ser, service_t, next)
    {
        if (ser->id == service_id) {
            return ser;
        }
    }

    return NULL;
}

static void ipc_service_entry(void *priv)
{
    service_t *                 ser = (service_t *)priv;
    ipc_t *                     ipc = ser->ipc;
    struct rpmsg_lite_endpoint *ept;
    rpmsg_queue_handle          rp_queue;
    message_t                   msg;
    int                         result = 0;
    volatile uint32_t           remote_addr;
    void *                      rx_buf;
    uint32_t                    len;
    int                         link_state = 0;

    memset(&msg, 0x00, sizeof(message_t));
    struct rpmsg_lite_instance *dev = (struct rpmsg_lite_instance *)ipc->ch->context;

    link_state = rpmsg_lite_wait_for_link_up(dev, RL_BLOCK);
    if (link_state == 1) {
        printf("Link up!\r\n");
    }

    rp_queue = rpmsg_queue_create(dev);
    ept      = rpmsg_lite_create_ept(dev, ser->id, rpmsg_queue_rx_cb, &rp_queue);
    rpmsg_ns_announce(dev, ept, RPMSG_LITE_NS_ANNOUNCE_STRING, RL_NS_CREATE);
    printf("\r\nNameservice sent, ready for incoming messages...\r\n");
    ser->rp_ept = ept;
    while (1) {
        /* Get RPMsg rx buffer with message */
        result
            = rpmsg_queue_recv_nocopy(dev, &rp_queue, (uint32_t *)&remote_addr, (char **)&rx_buf, &len, RL_BLOCK);
        if (result != 0) {
            aos_assert(false);
        }
        msg.service_id = ser->id;
        msg.req_data   = (char *)rx_buf;
        msg.req_len    = len;
        if (ser->process) {
            ser->process(ipc, &msg, ser->priv);
        }
        /* Release held RPMsg rx buffer */
        result = rpmsg_queue_nocopy_free(dev, rx_buf);
        if (result != 0) {
            aos_assert(false);
        }
    }

    aos_task_exit(0);
}

int ipc_message_send(ipc_t *ipc, message_t *m, int timeout_ms)
{
    aos_check_return_einval(ipc && m);

    service_t *ser = find_service(ipc, m->service_id);

    if (ser == NULL) {
        return -1;
    }

    if (ser->rp_ept == NULL) {
        printf("rp ept not ready\r\n");
        return -1;
    }

    struct rpmsg_lite_instance *dev = (struct rpmsg_lite_instance *)ipc->ch->context;

    return rpmsg_lite_send(dev, ser->rp_ept, m->service_id, m->req_data, m->req_len, timeout_ms);
}

ipc_t *ipc_get(int cpu_id)
{
#define IPC_NAME_MAX_LEN 16

    ipc_t *    ipc;
    channel_t *ch;

    slist_for_each_entry(&ipc_list, ipc, ipc_t, next)
    {
        if (ipc->des_cpu_id == cpu_id) {
            return ipc;
        }
    }

    ipc = calloc(1, sizeof(ipc_t) + IPC_NAME_MAX_LEN);
    if (ipc == NULL) {
        return NULL;
    }

    ch = calloc(1, sizeof(channel_t));
    if (ch == NULL) {
        free(ipc);
        return NULL;
    }

    ch->context = (void *)rpmsg_lite_remote_init((void *)RPMSG_LITE_SHMEM_BASE, RPMSG_LITE_LINK_ID, RL_NO_FLAGS);

    slist_add_tail(&ipc->next, &ipc_list);
    ipc->ch         = ch;
    ipc->des_cpu_id = cpu_id;
    ipc->seq        = 1;
    return ipc;
}

int ipc_add_service(ipc_t *ipc, int service_id, ipc_process_t cb, void *priv)
{
    aos_check_param(ipc);

    service_t *ser = find_service(ipc, service_id);

    if (ser != NULL) {
        assert(NULL);
        return -1;
    }

    ser = aos_zalloc(sizeof(service_t));

    if (ser) {
        ser->id      = service_id;
        ser->process = cb;
        ser->priv    = priv;
        ser->ipc     = ipc;
        ser->rp_ept  = NULL;
        slist_add_tail(&ser->next, &ipc->service_list);
        snprintf(ser->ser_name, SER_NAME_MAX_LEN, "ser%d->%d", service_id, ipc->des_cpu_id);
        aos_task_new_ext(&ser->task, ser->ser_name, ipc_service_entry, ser, CONFIG_IPC_SERVICE_TASK_STACK_SIZE, 9);
        return 0;
    }

    return -1;
}
