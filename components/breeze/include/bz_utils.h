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

#ifndef BZ_UTILS_H
#define BZ_UTILS_H

#define SET_U16_LE(data, val) {                              \
    *(uint8_t *)(data) = (uint8_t)(val & 0xFF);              \
    *((uint8_t *)(data) + 1) = (uint8_t)((val >> 8) & 0xFF); \
}

#define SET_U32_LE(data, val) {                               \
    *(uint8_t *)(data) = (uint8_t)(val & 0xFF);               \
    *((uint8_t *)(data) + 1) = (uint8_t)((val >> 8) & 0xFF);  \
    *((uint8_t *)(data) + 2) = (uint8_t)((val >> 16) & 0xFF); \
    *((uint8_t *)(data) + 3) = (uint8_t)((val >> 24) & 0xFF); \
}

#define SET_U32_BE(data, val) {                               \
    *(uint8_t *)(data) =  (uint8_t)((val >> 24) & 0xFF);      \
    *((uint8_t *)(data) + 1) = (uint8_t)((val >> 16) & 0xFF); \
    *((uint8_t *)(data) + 2) = (uint8_t)((val >> 8) & 0xFF);  \
    *((uint8_t *)(data) + 3) = (uint8_t)(val & 0xFF);         \
}

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

uint8_t hex2ascii(uint8_t digit);
void hex2string(uint8_t *hex, uint32_t len, uint8_t *str);
void utf8_to_pw(uint8_t *data, uint8_t len, char *pw);

void get_random(uint8_t *random, uint8_t random_len);
void hex_byte_dump_debug(uint8_t *data, int len, int tab_num);
void hex_byte_dump_verbose(uint8_t *data, int len, int tab_num);

#endif  // BZ_UTILS_H
