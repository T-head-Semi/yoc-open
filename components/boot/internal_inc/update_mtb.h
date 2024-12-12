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
#ifndef __UPDATE_MTB_H__
#define __UPDATE_MTB_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <mtb.h>

/**
 * 更新mtb镜像
 */
int update_img_mtb(uint32_t is_prim);

/**
 * 从FLASH更新到RAM
 */
int mtb_update_ram(mtb_t *mtb);

/**
 * 更新MTB的备份分区内容
 */
int mtb_update_backup(mtb_t *mtb, const char *img_name, mtb_partition_info_t *partition_new_info, int *update_flag);

/**
 * 更新MTB的主分区内容，(拷贝备份分区内容到主分区)
 */
int mtb_update_valid(mtb_t *mtb);

#ifdef __cplusplus
}
#endif

#endif /* __UPDATE_MTB_H__ */
