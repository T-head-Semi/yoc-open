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

#ifndef __ZCONFIG_UTILS_H__
#define __ZCONFIG_UTILS_H__

#include "os.h"

#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

void zconfig_dump_mac(uint8_t *src, uint8_t *dst);
void zconfig_dump_hex(uint8_t *data, int len, int tab_num);
void zconfig_dump_ascii(uint8_t *data, int len, int tab_num);

uint16_t zconfig_checksum_v3(uint8_t *data, uint8_t len);
uint16_t zconfig_checksum_v5(uint8_t *data, uint8_t len);
char zconfig_is_utf8(const char *ansi_str, int length);

#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
}
#endif

#endif	// _UTILS_H_
