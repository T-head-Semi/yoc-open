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

#ifndef __AVFILTER_CLS_H__
#define __AVFILTER_CLS_H__

#include "av/avutil/av_typedef.h"
#include "av/avutil/avpacket.h"
#include "av/avutil/avframe.h"

__BEGIN_DECLS__

typedef struct avfilter       avfilter_t;
typedef struct avfilter_ops   avfilter_ops_t;

struct avfilter_ops {
    const char                *name;
    avmedia_type_t            type;

    int      (*init)          (avfilter_t *avf);
    int      (*control)       (avfilter_t *avf, int cmd, void *arg, size_t *arg_size);
    int      (*filter_frame)  (avfilter_t *avf, const avframe_t *in, avframe_t *out);
    int      (*uninit)        (avfilter_t *avf);
};

#define AVF_IS_SRC(avf)       ((avf)->prev == NULL)
#define AVF_IS_SINK(avf)      ((avf)->next == NULL)

struct avfilter {
    uint8_t                   eof;
    uint8_t                   bypass;
    aos_mutex_t               lock;
    char                      *inst_name; ///< name of the avfilter instance
    avframe_t                 *oframe;     ///< used for sync filtering

    void                      *dobj;      ///< derived obj
    const struct avfilter_ops *ops;
    struct avfilter           *prev;
    struct avfilter           *next;
};

__END_DECLS__

#endif /* __AVFILTER_CLS_H__ */

