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
#ifndef __UPDATE_H__
#define __UPDATE_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CONFIG_RAM_MAX_USE
#define CONFIG_RAM_MAX_USE 50*1024 //BYTE
#endif

#if CONFIG_MANTB_VERSION < 4
#error "Not support, CONFIG_MANTB_VERSION must be defined as 4"
#endif

int update_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __UPDATE_H__ */
