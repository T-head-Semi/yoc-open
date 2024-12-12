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

#if defined(CONFIG_AV_AO_DUMMY) && CONFIG_AV_AO_DUMMY
#include "av/avutil/common.h"
#include "av/output/ao_cls.h"

#define TAG                    "ao_dummy"

struct ao_dummy_priv {
    void *pcm;
};

static int _ao_dummy_open(ao_cls_t *o, sf_t sf)
{
    unsigned int rate;
    struct ao_dummy_priv *priv = NULL;

    priv = av_zalloc(sizeof(struct ao_dummy_priv));
    CHECK_RET_TAG_WITH_RET(priv, -1);

    rate = sf_get_rate(sf);
    switch (rate) {
    case 8000 :
    case 16000:
    case 32000:

    case 12000:
    case 24000:
    case 48000:

    case 11025:
    case 22050:
    case 44100:
        break;
    default:
        LOGE(TAG, "rate is not support, rate = %d\n", rate);
        goto err;
    }

    o->sf   = sf;
    o->priv = priv;
    LOGD(TAG, " ao open");
    return 0;
err:
    av_free(priv);

    return -1;
}

static int _ao_dummy_start(ao_cls_t *o)
{
    return 0;
}

static int _ao_dummy_stop(ao_cls_t *o)
{
    return 0;
}

static int _ao_dummy_drain(ao_cls_t *o)
{
    return 0;
}

static int _ao_dummy_close(ao_cls_t *o)
{
    av_free(o->priv);
    return 0;
}

static int _ao_dummy_write(ao_cls_t *o, const uint8_t *buffer, size_t count)
{
    return count;
}

const struct ao_ops ao_ops_dummy = {
    .name          = "dummy",

    .open          = _ao_dummy_open,
    .start         = _ao_dummy_start,
    .stop          = _ao_dummy_stop,
    .drain         = _ao_dummy_drain,
    .close         = _ao_dummy_close,
    .write         = _ao_dummy_write,
};
#endif


