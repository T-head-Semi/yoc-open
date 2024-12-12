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


/******************************************************************************
 * @file     power_manager.h
 * @brief    Header file for the power_manager
 * @version  V1.0
 * @date     23. August 2017
 ******************************************************************************/
#ifndef _POWER_MANAGER_H_
#define _POWER_MANAGER_H_

#include <stdint.h>
#include <drv/common.h>
#include <soc.h>


#ifdef __cplusplus
extern "C" {
#endif

int32_t drv_clock_manager_config(clk_manager_type_t device, uint8_t enable);
void registers_save(uint32_t *mem, uint32_t *addr, int size);
void registers_restore(uint32_t *addr, uint32_t *mem, int size);

#define CLOCK_CONTROL_REGISTER0      (WJ_PMU_BASE + 0x1a8)
#define CLOCK_CONTROL_REGISTER1      (WJ_PMU_BASE + 0x1b4)
#define CLOCK_CONTROL_REGISTER2      (WJ_PMU_BASE + 0x19c)

#ifdef __cplusplus
}
#endif

#endif /* _POWER_MANAGER_H_ */

