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

#if defined(CONFIG_AVPARSER_MP3) && CONFIG_AVPARSER_MP3
#include "av/avformat/avformat_utils.h"
#include "av/avformat/mp3_rw.h"
#include "av/avformat/avparser_cls.h"

#define TAG                    "avparser_mp3"

static int _avparser_mp3_open(avparser_t *psr, uint8_t *extradata, size_t extradata_size)
{
    //FIXME:
    return 0;
}

static int _avparser_mp3_close(avparser_t *psr)
{
    //FIXME:
    return 0;
}

static int _avparser_mp3_parse(avparser_t *psr, const uint8_t *ibuf, size_t isize, size_t *ipos, uint8_t **obuf, size_t *osize)
{
    int rc;
    struct mp3_hdr_info info, *hinfo = &info;

    rc = mp3_hdr_get(ibuf, hinfo);
    CHECK_RET_TAG_WITH_RET(rc == 0 && hinfo->framesize <= isize, -1);

    *ipos  = hinfo->framesize;
    *osize = hinfo->framesize;
    *obuf  = (uint8_t*)ibuf;

    return rc;
}

const struct avparser_ops avparser_ops_mp3 = {
    .name            = "mp3",
    .id              = AVCODEC_ID_MP3,

    .open            = _avparser_mp3_open,
    .close           = _avparser_mp3_close,
    .parse           = _avparser_mp3_parse,
};
#endif

