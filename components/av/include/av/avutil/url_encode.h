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

#ifndef __URL_ENCODE_H__
#define __URL_ENCODE_H__

#include "av/avutil/common.h"

__BEGIN_DECLS__

/**
 * @brief  url string decode
 * @param  [in] src
 * @param  [in] src_size
 * @param  [in] dst
 * @param  [in] dst_size
 * @return -1 on error
 */
int url_decode(const char* src, const size_t src_size, char* dst, const size_t dst_size);

/**
 * @brief  encode the origin url
 * @param  [in] src
 * @param  [in] src_size
 * @param  [in] dst
 * @param  [in] dst_size
 * @return -1 on error
 */
int url_encode(const char* src, const size_t src_size, char* dst, const size_t dst_size);

/**
 * @brief  encode the url(don't encode :/$#@, etc)
 * @param  [in] s
 * attention: need free the return val by caller
 * @return NULL on error
 */
char* url_encode2(const char* s);

__END_DECLS__

#endif /* __URL_ENCODE_H__ */

