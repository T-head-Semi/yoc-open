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
#include "tfft/fft.h"
#include "tfft/fft_all.h"
#include "icore/fft_icore_internal.h"
#include "fft_icore_cp.h"

#define TAG    "fft_icore_cp"

struct fft_icore_cp_priv {
#define MESSAGE_NUM  (5)
    ipc_t            *ipc;
    aos_queue_t      queue;
    uint8_t          qbuf[sizeof(message_t) * MESSAGE_NUM];
};

static int _icore_fftx_new(icore_msg_t *msg)
{
    fftx_t *fft;
    fft_icore_new_t *inp;

    inp = icore_get_msg(msg, fft_icore_new_t);
    CHECK_RET_TAG_WITH_RET(inp, -1);

    fft = fftx_new(inp->size);
    if (fft == NULL) {
        LOGE(TAG, "fft new faild, size = %u", inp->size);
        return -1;
    }

    inp->fft = fft;
    return 0;
}

static int _icore_fftx_forward(icore_msg_t *msg)
{
    int rc = -1;
    size_t size;
    fftx_t *fft;
    fft_icore_forward_t *inp;

    inp = icore_get_msg(msg, fft_icore_forward_t);
    CHECK_RET_TAG_WITH_RET(inp, -1);

    fft = inp->fft;
    if (fft) {
        size = fft->size * sizeof(int16_t);
        csi_dcache_invalid_range((uint32_t*)inp->in, size);
        rc = fftx_forward(fft, inp->in, inp->out);
        if (rc == 0) {
            csi_dcache_clean_invalid_range((uint32_t*)inp->out, size);
        }
    }

    return rc;
}

static int _icore_fftx_backward(icore_msg_t *msg)
{
    int rc = -1;
    size_t size;
    fftx_t *fft;
    fft_icore_backward_t *inp;

    inp = icore_get_msg(msg, fft_icore_backward_t);
    CHECK_RET_TAG_WITH_RET(inp, -1);

    fft = inp->fft;
    if (fft) {
        size = fft->size * sizeof(int16_t);
        csi_dcache_invalid_range((uint32_t*)inp->in, size);
        rc = fftx_backward(fft, inp->in, inp->out);
        if (rc == 0) {
            csi_dcache_clean_invalid_range((uint32_t*)inp->out, size);
        }
    }

    return rc;
}

static int _icore_fftx_free(icore_msg_t *msg)
{
    int rc = -1;
    fftx_t *fft;
    fft_icore_free_t *inp;

    inp = icore_get_msg(msg, fft_icore_free_t);
    CHECK_RET_TAG_WITH_RET(inp, -1);

    fft = inp->fft;
    if (fft) {
        rc = fftx_free(fft);
    }

    return rc;
}

typedef int (*icore_handler_t)(icore_msg_t *msg);
static struct {
    msgid_t          id;
    icore_handler_t  handler;
} g_handlers[] = {
    { ICORE_CMD_FFT_NEW, _icore_fftx_new         },
    { ICORE_CMD_FFT_FORWARD, _icore_fftx_forward  },
    { ICORE_CMD_FFT_BACKWARD, _icore_fftx_backward     },
    { ICORE_CMD_FFT_FREE, _icore_fftx_free        },
};

static void _ipc_process(ipc_t *ipc, message_t *msg, void *arg)
{
    struct fft_icore_cp_priv *priv = arg;

    switch (msg->command) {
    case IPC_CMD_FFT_ICORE: {
        aos_queue_send(&priv->queue, msg, sizeof(message_t));
    }
    break;
    default:
        return;
    }
}

static void _fft_icore_cp_task(void *arg)
{
    int i;
    uint32_t len;
    message_t msg;
    icore_msg_t *data;
    struct fft_icore_cp_priv *priv = arg;

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
 * @brief  init inter-core fft of the cp
 * @return 0/-1
 */
int fft_icore_cp_init()
{
    static int inited = 0;

    if (!inited) {
        struct fft_icore_cp_priv *priv;

        priv = aos_zalloc(sizeof(struct fft_icore_cp_priv));
        CHECK_RET_TAG_WITH_RET(priv, -1);
        aos_queue_new(&priv->queue, priv->qbuf, sizeof(message_t) * MESSAGE_NUM, sizeof(message_t));
        priv->ipc = ipc_get(FFT_ICORE_AP_IDX);
        ipc_add_service(priv->ipc, FFT_ICORE_IPC_SERIVCE_ID, _ipc_process, priv);
        fftx_register();
        aos_task_new("fft_cp_task", _fft_icore_cp_task, (void *)priv, 4*1024);
        inited = 1;
    }

    return inited ? 0 : -1;
}



