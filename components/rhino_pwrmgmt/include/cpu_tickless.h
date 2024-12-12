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

/*
modification history
--------------------
14jan2018, init vesion
*/

#ifndef __cpu_tickless_h__
#define __cpu_tickless_h__

#ifdef __cplusplus
extern "C" {
#endif

#include "k_api.h"
#include "pwr_state.h"

typedef kstat_t (*FUNC_ONE_SHOT_INIT) (void);
typedef uint32_t (*FUNC_ONE_SHOT_SECONDS_MAX) (void);
typedef kstat_t (*FUNC_ONE_SHOT_START) (uint64_t  planUse);
typedef kstat_t (*FUNC_ONE_SHOT_STOP) (uint64_t * pPassedUs);

typedef struct
    {
    FUNC_ONE_SHOT_INIT          one_shot_init;
    FUNC_ONE_SHOT_SECONDS_MAX   one_shot_seconds_max;
    FUNC_ONE_SHOT_START         one_shot_start;
    FUNC_ONE_SHOT_STOP          one_shot_stop;
}one_shot_timer_t;

extern kstat_t tickless_init (void);
extern void    tickless_c_states_add(uint32_t c_state_set);
extern void    tickless_one_shot_timer_save
                    (cpu_cstate_t c_state, one_shot_timer_t * p_timer);


#ifdef __cplusplus
}
#endif

#endif /* __cpu_tickless_h__ */

