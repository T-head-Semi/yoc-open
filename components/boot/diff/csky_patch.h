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
#ifndef CSKY_PATCH_H_
#define CSKY_PATCH_H_

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>

#if (CONFIG_NO_OTA_UPGRADE == 0) && (CONFIG_OTA_NO_DIFF == 0)
typedef uint32_t ck_uint_t;
/**
 * patch process
 *
 * @param[in]     old_img_addr          old_img_addr
 * @param[in]     old_img_len           old_img_len
 * @param[in]    partion_size           the max size image can update
 * @param[in]     diff_img_addr         diff_img_addr
 * @param[in]     diff_img_len          diff_img_len
 * @return        -1 on failure; 0 on success
 */
int pat_process(ck_uint_t old_img_addr[] , ck_uint_t  old_img_len, ck_uint_t partion_size,ck_uint_t diff_img_addr[] , ck_uint_t diff_img_len);


/**
 * init resource info config for patch process
 * @param[in]  ram_buf              patch_libs needs ram buf
 * @param[in]  img_flash_sector    the dev img store flash sector
 * @param[in]  misc_flash_sector    the dev nisc store flash sector
 * @param[in]  misc_flash_end_addr        the dev img store flash end ,it must be flash sector padding
 * @return      other on failure; 0 on success
 */
int pat_config(ck_uint_t ram_buf, ck_uint_t img_flash_sector, ck_uint_t misc_flash_sector, ck_uint_t misc_flash_end_addr);

#endif

#ifdef __cplusplus
}
#endif

#endif /* CSKY_PATCH_ */
