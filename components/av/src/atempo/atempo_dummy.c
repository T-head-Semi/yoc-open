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

#if defined(CONFIG_ATEMPOER_DUMMY) && CONFIG_ATEMPOER_DUMMY

#include "av/avutil/av_typedef.h"
#include "av/atempo/atempo_cls.h"

#define TAG                   "atempo_dummy"
struct atempo_dummy_priv {
    //TODO:
    int                       dummy;
};

static int _atempo_dummy_init(atempo_t *atempo)
{
    struct atempo_dummy_priv *priv;

    priv = av_zalloc(sizeof(struct atempo_dummy_priv));

    atempo->priv = priv;
    return 0;
}

static int _atempo_dummy_write(atempo_t *atempo, const int16_t *in, size_t isamples)
{
    //TODO:
    return 0;
}

static int _atempo_dummy_read(atempo_t *atempo, int16_t *out, size_t osamples)
{
    //TODO:
    return 0;
}

static int _atempo_dummy_set_speed(atempo_t *atempo, float speed)
{
    //TODO:
    return 0;
}

static int _atempo_dummy_flush(atempo_t *atempo)
{
    //TODO:
    return 0;
}

static int _atempo_dummy_uninit(atempo_t *atempo)
{
    struct atempo_dummy_priv *priv = atempo->priv;

    av_free(priv);
    atempo->priv = NULL;

    return 0;
}

const struct atempo_ops atempo_ops_dummy = {
    .name            = "atempo_dummy",

    .init            = _atempo_dummy_init,
    .write           = _atempo_dummy_write,
    .read            = _atempo_dummy_read,
    .set_speed       = _atempo_dummy_set_speed,
    .flush           = _atempo_dummy_flush,
    .uninit          = _atempo_dummy_uninit,
};

#endif

