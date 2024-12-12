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



#ifndef _DM_FOTA_H_
#define _DM_FOTA_H_

#define DM_FOTA_TASK_STACK_SIZE (4096)

typedef struct {
    int is_report_new_config;
} dm_fota_ctx_t;

int dm_fota_init(void);
int dm_fota_deinit(void);
int dm_fota_perform_sync(_OU_ char *output, _IN_ int output_len);
int dm_fota_status_check(void);
int dm_fota_request_image(_IN_ const char *version, _IN_ int buffer_len);

#endif
