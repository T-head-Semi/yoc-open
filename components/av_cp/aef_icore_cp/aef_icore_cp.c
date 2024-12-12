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

#include <ipc.h>
#include <csi_core.h>
#include <aos/kernel.h>
#include "aef/aef.h"
#include "aef/aef_all.h"
#include "icore/aef_icore_internal.h"
#include "aef_icore_cp.h"

#define TAG    "aef_icore_cp"

struct aef_icore_cp_priv {
#define MESSAGE_NUM  (5)
    ipc_t            *ipc;
    aos_queue_t      queue;
    uint8_t          qbuf[sizeof(message_t) * MESSAGE_NUM];
};

static int _icore_aefx_new(icore_msg_t *msg)
{
    aefx_t *aef;
    aef_icore_new_t *inp;

    inp = icore_get_msg(msg, aef_icore_new_t);
    CHECK_RET_TAG_WITH_RET(inp, -1);

    csi_dcache_invalid_range((uint32_t*)inp->conf, inp->conf_size);
    aef = aefx_new(inp->rate, inp->conf, inp->conf_size, inp->nsamples_max);
    if (aef == NULL) {
        LOGE(TAG, "aef new faild, rate = %u, conf_size = %u, nsamples_max = %u", inp->rate, inp->conf_size, inp->nsamples_max);
        return -1;
    }

    inp->aef = aef;
    return 0;
}

static int _icore_aefx_process(icore_msg_t *msg)
{
    int rc = -1;
    size_t size;
    aefx_t *aef;
    aef_icore_process_t *inp;

    inp = icore_get_msg(msg, aef_icore_process_t);
    CHECK_RET_TAG_WITH_RET(inp, -1);

    aef = inp->aef;
    if (aef) {
        size = inp->nb_samples * sizeof(int16_t);
        csi_dcache_invalid_range((uint32_t*)inp->in, size);
        rc = aefx_process(aef, inp->in, inp->out, inp->nb_samples);
        if (rc == 0) {
            csi_dcache_clean_invalid_range((uint32_t*)inp->out, size);
        }
    }

    return rc;
}

static int _icore_aefx_free(icore_msg_t *msg)
{
    int rc = -1;
    aefx_t *aef;
    aef_icore_free_t *inp;

    inp = icore_get_msg(msg, aef_icore_free_t);
    CHECK_RET_TAG_WITH_RET(inp, -1);

    aef = inp->aef;
    if (aef) {
        rc = aefx_free(aef);
    }

    return rc;
}

typedef int (*icore_handler_t)(icore_msg_t *msg);
static struct {
    msgid_t          id;
    icore_handler_t  handler;
} g_handlers[] = {
    { ICORE_CMD_AEF_NEW, _icore_aefx_new         },
    { ICORE_CMD_AEF_PROCESS, _icore_aefx_process     },
    { ICORE_CMD_AEF_FREE, _icore_aefx_free        },
};

static void _ipc_process(ipc_t *ipc, message_t *msg, void *arg)
{
    struct aef_icore_cp_priv *priv = arg;

    switch (msg->command) {
    case IPC_CMD_AEF_ICORE: {
        aos_queue_send(&priv->queue, msg, sizeof(message_t));
    }
    break;
    default:
        return;
    }
}

static void _aef_icore_cp_task(void *arg)
{
    int i;
    uint32_t len;
    message_t msg;
    icore_msg_t *data;
    struct aef_icore_cp_priv *priv = arg;

    for (;;) {
        aos_queue_recv(&priv->queue, AOS_WAIT_FOREVER, &msg, &len);
        data = (icore_msg_t*)msg.req_data;

        if (data && (msg.req_len == (ICORE_MSG_SIZE + data->size))) {
            data->ret.code = -1;
            for (i = 0; i < ARRAY_SIZE(g_handlers); i++) {
                if (g_handlers[i].id == data->id) {
                    data->ret.code = g_handlers[i].handler(data);
                    break;
                }
            }
        }

        if (msg.flag & MESSAGE_SYNC) {
            memcpy(msg.resp_data, msg.req_data, msg.req_len);
            ipc_message_ack(priv->ipc, &msg, AOS_WAIT_FOREVER);
        }
    }
}

/**
 * @brief  init audio effecter of the cp
 * @return 0/-1
 */
int aef_icore_cp_init()
{
    static int inited = 0;

    if (!inited) {
        struct aef_icore_cp_priv *priv;

        priv = aos_zalloc(sizeof(struct aef_icore_cp_priv));
        CHECK_RET_TAG_WITH_RET(priv, -1);
        aos_queue_new(&priv->queue, priv->qbuf, sizeof(message_t) * MESSAGE_NUM, sizeof(message_t));
        priv->ipc = ipc_get(AEF_ICORE_AP_IDX);
        ipc_add_service(priv->ipc, AEF_ICORE_IPC_SERIVCE_ID, _ipc_process, priv);
        aefx_register();
        aos_task_new("aef_cp_task", _aef_icore_cp_task, (void *)priv, 4*1024);
        inited = 1;
    }

    return inited ? 0 : -1;
}



