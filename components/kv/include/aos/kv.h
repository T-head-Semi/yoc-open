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

#ifndef AOS_KV_H
#define AOS_KV_H

#include <aos/kernel.h>

#ifdef __cplusplus
extern "C" {
#endif


#include <string.h>

int aos_kv_init(const char *partname);
int aos_kv_flash_init(const char *flashname, int addr, int block_num);

/**
 * This function will reset all kv, restore factory settting
 * @return  0 on success, negative error on failure.
 */
int aos_kv_reset(void);

/**
 * Add a new KV pair.
 *
 * @param[in]  key    the key of the KV pair.
 * @param[in]  value  the value of the KV pair.
 * @param[in]  len    the length of the value.
 * @param[in]  sync   save the KV pair to flash right now (should always be 1).
 *
 * @return  0 on success, negative error on failure.
 */
int aos_kv_set(const char *key, void *value, int len, int sync);

int aos_kv_setfloat(const char *key, float v);

int aos_kv_setint(const char *key, int v);

/**
 * Get the KV pair's value stored in buffer by its key.
 *
 * @note: the buffer_len should be larger than the real length of the value,
 *        otherwise buffer would be NULL.
 *
 * @param[in]      key         the key of the KV pair to get.
 * @param[out]     buffer      the memory to store the value.
 * @param[in-out]  buffer_len  in: the length of the input buffer.
 *                             out: the real length of the value.
 *
 * @return  0 on success, negative error on failure.
 */
int aos_kv_get(const char *key, void *buffer, int *buffer_len);

int aos_kv_getfloat(const char *key, float *value);

int aos_kv_getint(const char *key, int *value);

/**
 *
 * @param[in]  key    the key of the KV pair.
 * @param[in]  value  the value of the KV pair.
 * @param[in]  len    the length of the value.
 * @param[in]  sync   save the KV pair to flash right now (should always be 1).
 *
 * @setstring return  0 on success, negative error on failure.
 * @getstring return  >=0 on success(read len), negative error on failure.
 */
int aos_kv_setstring(const char *key, const char *v);
int aos_kv_getstring(const char *key, char *value, int len);

/**
 * Delete the KV pair by its key.
 *
 * @param[in]  key  the key of the KV pair to delete.
 *
 * @return  0 on success, negative error on failure.
 */
int aos_kv_del(const char *key);

#ifdef __cplusplus
}
#endif

#endif /* AOS_KV_H */
