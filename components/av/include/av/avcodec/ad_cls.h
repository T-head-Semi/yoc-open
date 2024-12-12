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

#ifndef __AD_CLS_H__
#define __AD_CLS_H__

#include "av/avutil/av_typedef.h"
#include "av/avutil/avpacket.h"
#include "av/avutil/avframe.h"

__BEGIN_DECLS__

typedef struct ad_cls ad_cls_t;

struct ad_ops {
    const char                *name;
    avcodec_id_t              id;

    int      (*open)          (ad_cls_t *o);
    int      (*decode)        (ad_cls_t *o, avframe_t *frame, int *got_frame, const avpacket_t *pkt);
    int      (*control)       (ad_cls_t *o, int cmd, void *arg, size_t *arg_size);
    int      (*reset)         (ad_cls_t *o);
    int      (*close)         (ad_cls_t *o);
};

struct ad_cls {
    sh_audio_t                ash;
    aos_mutex_t               lock;

    void                      *priv;
    const struct ad_ops       *ops;
};

enum {
    CODEC_CMD_UNKNOWN,
};

__END_DECLS__

#endif /* __AD_CLS_H__ */

