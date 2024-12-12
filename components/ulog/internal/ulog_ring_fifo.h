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

#ifndef ULOG_RING_FIFO_H_
#define ULOG_RING_FIFO_H_
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef void (*pop_callback)(void*, void* src, const uint16_t len);

extern int uring_fifo_push_s(const void* buf, const uint16_t len);

extern int uring_fifo_pop_cb(pop_callback cb, void* cb_arg);

extern int uring_fifo_init(void);

extern void uring_fifo_flush(pop_callback cb, void* cb_arg);

#ifdef __cplusplus
}
#endif

#endif /*ULOG_RING_FIFO_H_*/
