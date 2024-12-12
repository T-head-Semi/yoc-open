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

#ifndef __APP_CONFIG_H__
#define __APP_CONFIG_H__


#ifdef CONFIG_CHIP_CH2601

#endif

#ifdef CONFIG_CHIP_D1

#endif

#ifdef CONFIG_CHIP_BL606P_E907
#include <bl606p_gpio.h>
#include <bl606p_glb.h>
#include <bl606p_spi.h>
#endif

#ifdef CVI_SOC_CV181XC
#define CONFIG_HAL_SPI_DISABLED
#endif




#endif