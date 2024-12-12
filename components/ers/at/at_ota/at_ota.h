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

#ifndef _AT_OTA_H_
#define _AT_OTA_H_

typedef enum
{
    AT_OTA_TARGET_LOCAL  = 0x00,
    AT_OTA_TARGET_REMOTE = 0x01,
    AT_OTA_TARGET_MAX
} at_ota_target_en;

enum
{
    AT_OTA_ERR_NULL   = -3,
    AT_OTA_ERR_RUNING = -2,
    AT_OTA_ERR        = -1, /* at_ota module return error */
    AT_OTA_SUCCESS    = 0,  /* at_ota module return success */
    AT_OTA_UPGRADED   = 1,  /* the file is used for upgrade by upper module*/
    AT_OTA_UPGRAD_SKIP
    = 2, /* the file is skiped by upper module, at_ota module should process this file if possiable */
};

typedef int (*at_ota_prepare_func_t)(void);
typedef int (*at_ota_upgrade_func_t)(at_ota_target_en target, void *file, uint32_t file_size);
typedef int (*at_ota_finish_func_t)(int result);

typedef struct _at_ota_ops_t {
    at_ota_prepare_func_t prepare;
    at_ota_upgrade_func_t upgrade;
    at_ota_finish_func_t  finish;
} at_ota_ops_t;

typedef struct _at_ota_config_t {
    int           at_ota_port;
    at_ota_ops_t *ops;
} at_ota_config_t;

int at_ota_init(at_ota_config_t config);

int at_ota_start();

#endif
