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

#ifndef __AVFILTER_SWR_H__
#define __AVFILTER_SWR_H__

#include "av/avutil/sf.h"
#include "av/avfilter/avfilter.h"

__BEGIN_DECLS__

typedef struct {
    sf_t                      isf;  ///< input sample format
    sf_t                      osf;  ///< output sample format
} swr_avfp_t;

/**
 * @brief  open swr avfilter
 * @param  [in] inst_name : the name of avfilter_t instance
 * @param  [in] swrp
 * @return NULL on error
 */
avfilter_t *avf_swr_open(const char *inst_name, const swr_avfp_t *swrp);

#define avf_swr_control(f, cmd, arg, arg_size) avf_control(f, cmd, arg, arg_size)

#define avf_swr_filter_frame(f, i, o) avf_filter_frame(f, i, o)

#define avf_swr_close(f) avf_close(f)

__END_DECLS__

#endif /* __AVFILTER_SWR_H__ */

