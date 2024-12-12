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

#if defined(CONFIG_RESAMPLER_DUMMY) && CONFIG_RESAMPLER_DUMMY

#include "av/swresample/resample_cls.h"

#define TAG                   "res_dummy"

struct res_dummy_priv {
    //TODO:
    int                       dummy;
};

static int _resample_dummy_init(resx_t *r)
{
    struct res_dummy_priv *priv;

    priv    = av_zalloc(sizeof(struct res_dummy_priv));
    r->priv = priv;

    return 0;
}

static int _resample_dummy_convert(resx_t *r, void **out, size_t nb_osamples, const void **in, size_t nb_isamples)
{
    //TODO:
    return 0;
}

static int _resample_dummy_uninit(resx_t *r)
{
    struct res_dummy_priv *priv = r->priv;

    av_free(priv);
    r->priv = NULL;
    return 0;
}

const struct resx_ops resx_ops_dummy = {
    .name            = "dummy",

    .init            = _resample_dummy_init,
    .convert         = _resample_dummy_convert,
    .uninit          = _resample_dummy_uninit,
};

#endif


