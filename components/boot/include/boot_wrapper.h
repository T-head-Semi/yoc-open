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
#ifndef __BOOT_WRAPPER_H__
#define __BOOT_WRAPPER_H__

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
  * load and jump to next image
*/
/* TODO weak */
void boot_load_and_jump(void);

/**
  * system reboot
*/
/* TODO weak */
void boot_sys_reboot(void);

/**
 * @brief  check the image is needed ota or not
 * @param name partition name
 * @return true: no needed ota, false: need ota
 */
/* TODO weak */
bool boot_is_no_needed_ota(const char *name);

#ifdef __cplusplus
}
#endif
#endif