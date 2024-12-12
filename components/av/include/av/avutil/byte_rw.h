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

#ifndef __BYTE_RW_H__
#define __BYTE_RW_H__

#include "av/avutil/common.h"

__BEGIN_DECLS__

uint16_t byte_r16be(const uint8_t *buf);

uint32_t byte_r24be(const uint8_t *buf);

uint32_t byte_r32be(const uint8_t *buf);

uint64_t byte_r64be(const uint8_t *buf);

uint16_t byte_r16le(const uint8_t *buf);

uint32_t byte_r24le(const uint8_t *buf);

uint32_t byte_r32le(const uint8_t *buf);

uint64_t byte_r64le(const uint8_t *buf);

__END_DECLS__

#endif /* __BYTE_RW_H__ */

