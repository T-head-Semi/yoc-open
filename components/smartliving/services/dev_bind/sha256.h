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

#ifndef __AWSS_SHA256_H__
#define __AWSS_SHA256_H__

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

typedef struct SHA256_CTX {
//  const HASH_VTAB * f;
    uint64_t count;
    uint8_t buf[64];
    uint32_t state[8];  // upto SHA2
} SHA256_CTX;

//typedef HASH_CTX SHA256_CTX;
void SHA256_init(SHA256_CTX* ctx);
void SHA256_update(SHA256_CTX* ctx, const void* data, int len);
const uint8_t* SHA256_final(SHA256_CTX* ctx);
// Convenience method. Returns digest address.
const uint8_t* SHA256_hash(const void* data, int len, uint8_t* digest);

#ifndef SHA256_DIGEST_SIZE
#define SHA256_DIGEST_SIZE 32
#endif

#ifdef __cplusplus
}
#endif // __cplusplus

#endif  // SYSTEM_CORE_INCLUDE_MINCRYPT_SHA256_H_
