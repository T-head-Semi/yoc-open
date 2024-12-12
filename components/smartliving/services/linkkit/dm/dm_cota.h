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



#ifndef _DM_COTA_H_
#define _DM_COTA_H_

typedef struct {
    int is_report_new_config;
} dm_cota_ctx_t;

int dm_cota_init(void);
int dm_cota_deinit(void);
int dm_cota_perform_sync(_OU_ char *output, _IN_ int output_len);
int dm_cota_get_config(const char *config_scope, const char *get_type, const char *attribute_keys);
int dm_cota_status_check(void);

#endif