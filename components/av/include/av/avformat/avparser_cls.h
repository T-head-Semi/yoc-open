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

#ifndef __AVPARSER_CLS_H__
#define __AVPARSER_CLS_H__

#include "av/avutil/av_typedef.h"
#include "av/avutil/avpacket.h"
#include "av/stream/stream_cls.h"

__BEGIN_DECLS__

typedef struct avparser         avparser_t;

struct avparser_ops {
    const char                  *name;
    avcodec_id_t                id;

    int      (*open)            (avparser_t *psr, uint8_t *extradata, size_t extradata_size);
    int      (*parse)           (avparser_t *psr, const uint8_t *ibuf, size_t isize, size_t *ipos, uint8_t **obuf, size_t *osize);
    int      (*close)           (avparser_t *psr);
};

struct avparser {
    aos_mutex_t                 lock;
    void                        *priv;
    const struct avparser_ops   *ops;
};

__END_DECLS__

#endif /* __AVPARSER_CLS_H__ */

