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

#ifndef __AVFILTER_ATEMPO_H__
#define __AVFILTER_ATEMPO_H__

#include "av/avutil/sf.h"
#include "av/avfilter/avfilter.h"

__BEGIN_DECLS__

#define AVF_CMD_ATEMPO_SET_SPEED  (20)

typedef struct {
    sf_t                      sf;
    float                     speed;          ///< suggest: 0.5 ~ 2.0;
} atempo_avfp_t;

/**
 * @brief  open atempo avfilter
 * @param  [in] inst_name : the name of avfilter_t instance
 * @param  [in] atempop
 * @return NULL on error
 */
avfilter_t *avf_atempo_open(const char *inst_name, const atempo_avfp_t *atempop);

#define avf_atempo_control(f, cmd, arg, arg_size) avf_control(f, cmd, arg, arg_size)

#define avf_atempo_filter_frame(f, i, o) avf_filter_frame(f, i, o)

#define avf_atempo_close(f) avf_close(f)

__END_DECLS__

#endif /* __AVFILTER_ATEMPO_H__ */

