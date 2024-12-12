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
#ifndef __UPDATE_DIFF_H__
#define __UPDATE_DIFF_H__

#include <stdint.h>

int diff_init_config(uint32_t bs_ram_size, uint32_t img_flash_sector,
                         uint32_t misc_flash_sector, uint32_t bs_flash_end_addr);
int diff_updata_img(uint32_t old_img_addr, uint32_t old_img_len, uint32_t partion_size,
                        uint32_t diff_img_addr, uint32_t diff_img_len);

#endif