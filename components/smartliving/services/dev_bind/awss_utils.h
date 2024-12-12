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

#ifndef __AWSS_UTILS_H__
#define __AWSS_UTILS_H__

#if defined(__cplusplus) /* If this is a C++ compiler, use C linkage */
extern "C" {
#endif

#include "os.h"
#include "iotx_utils.h"

/**
 * @brief string to hex
 *
 * @param[in] str: input hex string
 * @param[in] str_len: length of input hex string
 * @param[out] out: output hex byte stream
 * @param[in/out] output_len: [in] for output buffer size, [out] for
 *                 output hex byte len
 * @Note None.
 *
 * @retval return num of hex bytes converted, 0 means error.
 */
#define utils_str_to_hex    LITE_hexstr_convert


/**
 * @brief hex to string
 *
 * @param[in] buf: input hex byte stream
 * @param[in] buf_len: input stream length in byte
 * @param[out] str: encoded hex string
 * @param[in/out] str_len: [in] for str buffer size, [out] for
 *                  encoded string length
 * @Note output str buffer is NULL-terminated(if str_buf_len is longer enough)
 *
 * @retval return length of str converted, 0 means error.
 */
#define utils_hex_to_str(buf, buf_len, str, str_buf_len) LITE_hexbuf_convert(buf, str, buf_len, 1)

#if defined(__cplusplus) /* If this is a C++ compiler, use C linkage */
}
#endif

#endif
