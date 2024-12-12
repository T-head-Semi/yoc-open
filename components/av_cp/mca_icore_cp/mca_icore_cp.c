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
#include "mca/mca.h"
#include "mca/mca_all.h"
#include "icore/mca_icore_internal.h"
#include "mca_icore_cp.h"

#define TAG    "mca_icore_cp"

struct mca_icore_cp_priv {
#define MESSAGE_NUM  (5)
    ipc_t            *ipc;
    aos_queue_t      queue;
    uint8_t          qbuf[sizeof(message_t) * MESSAGE_NUM];
};

static int _icore_mcax_new(icore_msg_t *msg)
{
    mcax_t *mca;
    mca_icore_new_t *inp;

    inp = icore_get_msg(msg, mca_icore_new_t);
    CHECK_RET_TAG_WITH_RET(inp, -1);

    mca = mcax_new(inp->type);
    if (mca == NULL) {
        LOGE(TAG, "mca new faild");
        return -1;
    }

    inp->mca = mca;
    return 0;
}

static int _icore_mcax_iir_fxp32_coeff32_config(icore_msg_t *msg)
{
    int rc = -1;
    mcax_t *mca;
    mca_icore_iir_fxp32_coeff32_config_t *inp;

    inp = icore_get_msg(msg, mca_icore_iir_fxp32_coeff32_config_t);
    CHECK_RET_TAG_WITH_RET(inp, -1);

    mca = inp->mca;
    if (mca) {
        rc = mcax_iir_fxp32_coeff32_config(mca, inp->coeff);
    }

    return rc;
}

static int _icore_mcax_iir_fxp32(icore_msg_t *msg)
{
    int rc = -1;
    size_t size;
    mcax_t *mca;
    mca_icore_iir_fxp32_t *inp;

    inp = icore_get_msg(msg, mca_icore_iir_fxp32_t);
    CHECK_RET_TAG_WITH_RET(inp, -1);

    mca = inp->mca;
    if (mca) {
        size = inp->input_size * sizeof(fxp32_t);
        csi_dcache_invalid_range((uint32_t*)inp->input, size);
        rc = mcax_iir_fxp32(mca, inp->input, inp->input_size, inp->yn1, inp->yn2, inp->output);
        if (rc == 0) {
            size = (inp->input_size - 2) * sizeof(fxp32_t);
            csi_dcache_clean_invalid_range((uint32_t*)inp->output, size);
        }
    }

    return rc;
}

static int _icore_mcax_free(icore_msg_t *msg)
{
    int rc = -1;
    mcax_t *mca;
    mca_icore_free_t *inp;

    inp = icore_get_msg(msg, mca_icore_free_t);
    CHECK_RET_TAG_WITH_RET(inp, -1);

    mca = inp->mca;
    if (mca) {
        rc = mcax_free(mca);
    }

    return rc;
}

typedef int (*icore_handler_t)(icore_msg_t *msg);
static struct {
    msgid_t          id;
    icore_handler_t  handler;
} g_handlers[] = {
    { ICORE_CMD_MCA_NEW, _icore_mcax_new         },
    { ICORE_CMD_MCA_IIR_FXP32_COEFF32_CONFIG, _icore_mcax_iir_fxp32_coeff32_config },
    { ICORE_CMD_MCA_IIR_FXP32, _icore_mcax_iir_fxp32 },
    { ICORE_CMD_MCA_FREE, _icore_mcax_free        },
};

static void _ipc_process(ipc_t *ipc, message_t *msg, void *arg)
{
    struct mca_icore_cp_priv *priv = arg;

    switch (msg->command) {
    case IPC_CMD_MCA_ICORE: {
        aos_queue_send(&priv->queue, msg, sizeof(message_t));
    }
    break;
    default:
        return;
    }
}

static void _mca_icore_cp_task(void *arg)
{
    int i;
    uint32_t len;
    message_t msg;
    icore_msg_t *data;
    struct mca_icore_cp_priv *priv = arg;

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
 * @brief  init inter-core mca of the cp
 * @return 0/-1
 */
int mca_icore_cp_init()
{
    static int inited = 0;

    if (!inited) {
        struct mca_icore_cp_priv *priv;

        priv = aos_zalloc(sizeof(struct mca_icore_cp_priv));
        CHECK_RET_TAG_WITH_RET(priv, -1);
        aos_queue_new(&priv->queue, priv->qbuf, sizeof(message_t) * MESSAGE_NUM, sizeof(message_t));
        priv->ipc = ipc_get(MCA_ICORE_AP_IDX);
        ipc_add_service(priv->ipc, MCA_ICORE_IPC_SERIVCE_ID, _ipc_process, priv);
        mcax_register_local();
        aos_task_new("mca_cp_task", _mca_icore_cp_task, (void *)priv, 4*1024);
        inited = 1;
    }

    return inited ? 0 : -1;
}



