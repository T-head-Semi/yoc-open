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

#if defined(CONFIG_ATEMPOER_SONIC) && CONFIG_ATEMPOER_SONIC

#include "av/avutil/av_typedef.h"
#include "av/atempo/atempo_cls.h"
#include "sonic.h"

#define TAG                   "atempo_sonic"
struct atempo_sonic_priv {
    sonicStream               stream;
};

static int _atempo_sonic_init(atempo_t *atempo)
{
    sonicStream stream = NULL;
    struct atempo_sonic_priv *priv = NULL;

    priv   = av_zalloc(sizeof(struct atempo_sonic_priv));
    stream = sonicCreateStream(atempo->rate, 1);
    CHECK_RET_TAG_WITH_GOTO(priv && stream, err);
    sonicSetSpeed(stream, atempo->speed);

    priv->stream = stream;
    atempo->priv = priv;
    return 0;
err:
    if (stream)
        sonicDestroyStream(stream);
    av_free(priv);
    return -1;
}

static int _atempo_sonic_write(atempo_t *atempo, const int16_t *in, size_t isamples)
{
    int rc;
    struct atempo_sonic_priv *priv = atempo->priv;
    sonicStream stream             = priv->stream;

    rc = sonicWriteShortToStream(stream, (short*)in, isamples);

    return rc == 1 ? 0 : -1;
}

static int _atempo_sonic_read(atempo_t *atempo, int16_t *out, size_t osamples)
{
    int rc;
    struct atempo_sonic_priv *priv = atempo->priv;
    sonicStream stream             = priv->stream;

    rc = sonicReadShortFromStream(stream, (short*)out, osamples);

    return rc;
}

static int _atempo_sonic_set_speed(atempo_t *atempo, float speed)
{
    struct atempo_sonic_priv *priv = atempo->priv;
    sonicStream stream             = priv->stream;

    sonicSetSpeed(stream, speed);

    return 0;
}

static int _atempo_sonic_flush(atempo_t *atempo)
{
    struct atempo_sonic_priv *priv = atempo->priv;
    sonicStream stream             = priv->stream;

    sonicFlushStream(stream);

    return 0;
}

static int _atempo_sonic_uninit(atempo_t *atempo)
{
    struct atempo_sonic_priv *priv = atempo->priv;
    sonicStream stream             = priv->stream;

    sonicDestroyStream(stream);
    av_free(priv);
    atempo->priv = NULL;
    return 0;
}

const struct atempo_ops atempo_ops_sonic = {
    .name            = "atempo_sonic",

    .init            = _atempo_sonic_init,
    .write           = _atempo_sonic_write,
    .read            = _atempo_sonic_read,
    .set_speed       = _atempo_sonic_set_speed,
    .flush           = _atempo_sonic_flush,
    .uninit          = _atempo_sonic_uninit,
};

#endif

