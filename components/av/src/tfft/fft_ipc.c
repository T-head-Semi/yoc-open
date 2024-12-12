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

#if defined(CONFIG_FFTXER_IPC) && CONFIG_FFTXER_IPC

#include "av/tfft/fft_cls.h"
#include "fft_icore.h"

#define TAG                   "fft_ipc"

struct fft_ipc_priv {
    fft_icore_t                *hdl;
};

static int _fft_ipc_init(fftx_t *fft, size_t size)
{
    int rc;
    void *hdl = NULL;
    struct fft_ipc_priv *priv = NULL;

    rc = fft_icore_init();
    CHECK_RET_TAG_WITH_RET(rc == 0, -1);

    priv = av_zalloc(sizeof(struct fft_ipc_priv));
    hdl = fft_icore_new(size);
    CHECK_RET_TAG_WITH_GOTO(hdl, err);

    priv->hdl = hdl;
    fft->priv = priv;
    return 0;
err:
    av_free(priv);
    return -1;
}

static int _fft_ipc_forward(fftx_t *fft, const int16_t *in, int16_t *out)
{
    struct fft_ipc_priv *priv = fft->priv;

    fft_icore_forward(priv->hdl, in, out);

    return 0;
}

static int _fft_ipc_backward(fftx_t *fft, const int16_t *in, int16_t *out)
{
    struct fft_ipc_priv *priv = fft->priv;

    fft_icore_backward(priv->hdl, in, out);

    return 0;
}

static int _fft_ipc_uninit(fftx_t *fft)
{
    struct fft_ipc_priv *priv = fft->priv;

    fft_icore_free(priv->hdl);
    av_free(priv);
    fft->priv = NULL;
    return 0;
}

const struct fftx_ops fftx_ops_ipc = {
    .name            = "fft_ipc",

    .init            = _fft_ipc_init,
    .forward         = _fft_ipc_forward,
    .backward        = _fft_ipc_backward,
    .uninit          = _fft_ipc_uninit,
};

#endif

