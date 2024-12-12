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



#ifndef _DM_OTA_H_
#define _DM_OTA_H_

typedef struct {
    void *ota_handle;
    char product_key[PRODUCT_KEY_MAXLEN];
    char device_name[DEVICE_NAME_MAXLEN];
} dm_ota_ctx_t;

int dm_ota_init(void);
int dm_ota_sub(void);
int dm_ota_deinit(void);
int dm_ota_get_ota_handle(void **handle);
int dm_ota_download(char *payload, unsigned int payload_len);
#endif