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



#ifndef _DM_SHADOW_H_
#define _DM_SHADOW_H_

typedef struct {
    void *handle;
    char product_key[PRODUCT_KEY_MAXLEN];
    char device_name[DEVICE_NAME_MAXLEN];
} dm_shadow_ctx_t;

int dm_shadow_init(void);
int dm_shadow_connect(void);
int dm_shadow_deinit(void);
int dm_shadow_update(void);
int dm_shadow_yield(int timeout_ms);
int dm_shadow_get_handle(void **handle);
int dm_shadow_register_attr(iotx_shadow_attr_pt pattr);

#endif