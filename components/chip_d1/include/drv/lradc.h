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

#ifndef __DRV_LRADC_H__
#define __DRV_LRADC_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*lradc_callback_t)(uint32_t irq_status, uint32_t data);

#define LRADC_ADC0_UPPEND       (1<<4)
#define LRADC_ADC0_DOWNPEND     (1<<1)
#define LRADC_ADC0_DATAPEND     (1<<0)

/*****************************************************************************
 * Enums
 *****************************************************************************/
typedef enum{
	LRADC_STATUS_ERROR_PARAMETER = -3,
	LRADC_STATUS_ERROR_CHANNEL = -2,
	LRADC_STATUS_ERROR = -1,
	LRADC_STATUS_OK = 0
} lradc_status_t;

/*****************************************************************************
 * Functions
 *****************************************************************************/
lradc_status_t csi_lradc_init(void);

lradc_status_t csi_lradc_deinit(void);

lradc_status_t csi_lradc_register_callback(lradc_callback_t callback);

#ifdef __cplusplus
}
#endif

#endif /*__DRV_LRADC_H__*/
