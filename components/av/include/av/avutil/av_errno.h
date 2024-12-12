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

#ifndef __AV_ERRNO_H__
#define __AV_ERRNO_H__

#include <stdio.h>

/* attention: interface design is ugly for special use in this file, Not recommended */

#ifdef __cplusplus
extern "C" {
#endif

#define AV_ERRNO_OK                       (0)
#define AV_ERRNO_UNKNOWN_ERROR            (-1)
#define AV_ERRNO_OOM                      (-2)
#define AV_ERRNO_TIMEOUT                  (-3)
#define AV_ERRNO_PARAM_INVALID            (-4)
#define AV_ERRNO_FILE_NOT_FOUND           (-5)
#define AV_ERRNO_CONNECT_FAILD            (-6)
#define AV_ERRNO_DNS_FAILD                (-7)
#define AV_ERRNO_NETWORK_FAILD            (-8)
#define AV_ERRNO_READ_FAILD               (-9)
#define AV_ERRNO_WRITE_FAILD              (-10)
#define AV_ERRNO_HTTP_FAILD               (-11)
#define AV_ERRNO_SEEK_FAILD               (-12)

#define AV_ERRNO_STREAM_TYPE_UNKNOWN      (-20)
#define AV_ERRNO_FORMAT_TYPE_UNKNOWN      (-21)
#define AV_ERRNO_CODEC_TYPE_UNKNOWN       (-22)
#define AV_ERRNO_DEMUX_FAILD              (-24)
#define AV_ERRNO_DECODE_FAILD             (-25)
#define AV_ERRNO_OUTPUT_FAILD             (-26)

/**
 * @brief  set the global errno for av, ugly for special use(xiaoya, etc)
 * @param  [in] errno
 * @return
 */
void av_errno_set(int errno);

/**
 * @brief  get the global av errno on play errno.
 * attention: this av-errno is not accurate, just for statistic-online
 * @return AV_ERRNO_XXX
 */
int av_errno_get();

#if CONFIG_AV_ERRNO_DEBUG
#define AV_ERRNO_SET(errno)                                                       \
    do {                                                                          \
        av_errno_set(errno);                                                      \
    } while (0)
#else
#define AV_ERRNO_SET(errno)
#endif

#ifdef __cplusplus
}
#endif

#endif /* __AV_ERRNO_H__ */

