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

#ifndef K_TIME_H
#define K_TIME_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup aos_rhino time
 *  Time management
 *
 *  @{
 */

/**
 * Systick routine handler.
 *
 * @param[in]  NULL
 *
 * @return  NULL
 */
void krhino_tick_proc(void);

/**
 * Get the current time from system startup, in ms.
 *
 * @param[in]  NULL
 *
 * @return  system time
 */
sys_time_t krhino_sys_time_get(void);

/**
 * Get the current time from system startup, in ticks.
 *
 * @param[in]  NULL
 *
 * @return  system ticks
 */
tick_t krhino_sys_tick_get(void);

/**
 * Convert ms to ticks.
 *
 * @param[in]  ms  ms which will be converted to ticks
 *
 * @return  the ticks of the ms
 */
tick_t krhino_ms_to_ticks(sys_time_t ms);

/**
 * Convert ticks to ms.
 *
 * @param[in]  ticks  ticks which will be converted to ms
 *
 * @return  the ms of the ticks
 */
sys_time_t krhino_ticks_to_ms(tick_t ticks);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* K_TIME_H */

