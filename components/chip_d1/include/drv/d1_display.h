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

#ifndef __D1_DRV_DISPLAT_H__
#define __D1_DRV_DISPLAT_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct d1_touch_config {
    uint16_t iic_port;
    uint16_t iic_addr;
    uint32_t rst_pin;
    uint32_t int_pin;
} d1_touch_config_t;

/**
 * @brief  register display driver chip d1
 * @param  [in] config
 */
void drv_d1_display_register(void);

/**
 * @brief  register display driver chip d1
 * @param  [in] config
 */
void drv_d1_720p_display_register(void);

/**
 * @brief  register display driver chip d1
 * @param  [in] config
 */
void drv_d1_480p_display_register(void);


/**
 * @brief  register touch driver chip d1
 * @param  [in] config
 */
void drv_d1_gt9xx_touch_register(d1_touch_config_t *config);

/**
 * @brief  register touch driver chip d1
 * @param  [in] config
 */
void drv_d1_ft6336_touch_register(d1_touch_config_t *config);

/**
 * @brief  register touch driver chip d1
 * @param  [in] config
 */
void drv_d1_ft6336_480p_touch_register(d1_touch_config_t *config);
#ifdef __cplusplus
}
#endif

#endif /*__DRV_LRADC_H__*/
