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

#if defined(CONFIG_FFTXER_SPEEX) && CONFIG_FFTXER_SPEEX

#include "av/tfft/fft_cls.h"
#include "speex/fftwrap.h"

#define TAG                   "fft_speex"

struct fft_speex_priv {
    void                      *hdl;
};

static int _fft_speex_init(fftx_t *fft, size_t size)
{
    void *hdl = NULL;
    struct fft_speex_priv *priv = NULL;

    priv = av_zalloc(sizeof(struct fft_speex_priv));
    hdl = spx_fft_init(size);
    CHECK_RET_TAG_WITH_GOTO(hdl, err);

    priv->hdl = hdl;
    fft->priv = priv;
    return 0;
err:
    av_free(priv);
    return -1;
}

static int _fft_speex_forward(fftx_t *fft, const int16_t *in, int16_t *out)
{
    struct fft_speex_priv *priv = fft->priv;

    spx_fft(priv->hdl, (spx_word16_t*)in, (spx_word16_t*)out);

    return 0;
}

static int _fft_speex_backward(fftx_t *fft, const int16_t *in, int16_t *out)
{
    struct fft_speex_priv *priv = fft->priv;

    spx_ifft(priv->hdl, (spx_word16_t*)in, (spx_word16_t*)out);

    return 0;
}

static int _fft_speex_uninit(fftx_t *fft)
{
    struct fft_speex_priv *priv = fft->priv;

    spx_fft_destroy(priv->hdl);
    av_free(priv);
    fft->priv = NULL;
    return 0;
}

const struct fftx_ops fftx_ops_speex = {
    .name            = "fft_speex",

    .init            = _fft_speex_init,
    .forward         = _fft_speex_forward,
    .backward        = _fft_speex_backward,
    .uninit          = _fft_speex_uninit,
};

#endif

