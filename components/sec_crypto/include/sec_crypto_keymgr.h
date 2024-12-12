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


#ifndef _SC_KEYMGR_H_
#define _SC_KEYMGR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

int sc_get_bootkey(uint8_t *bk, int bk_size);
int sc_verify_bootkey(uint8_t *bk, int bk_size, uint8_t *bk_hash);
int sc_srv_get_auth_key(uint8_t *key, uint32_t *len);

#ifdef __cplusplus
}
#endif

#endif