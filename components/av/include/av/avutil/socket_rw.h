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

#ifndef __SOCKET_RW_H__
#define __SOCKET_RW_H__

#include "av/avutil/common.h"

__BEGIN_DECLS__

/**
 * @brief  read n bytes from a sockfd with timeout
 * @param  [in] fd
 * @param  [in] buf
 * @param  [in] count
 * @param  [in] timeout_ms
 * @return -1 on err
 */
int sock_readn(int fd, char *buf, size_t count, int timeout_ms);

/**
 * @brief  write n bytes from a sockfd with timeout
 * @param  [in] fd
 * @param  [in] buf
 * @param  [in] count
 * @param  [in] timeout_ms
 * @return -1 on err
 */
int sock_writen(int fd, const char *buf, size_t count, int timeout_ms);

__END_DECLS__

#endif /* __SOCKET_RW_H__ */

