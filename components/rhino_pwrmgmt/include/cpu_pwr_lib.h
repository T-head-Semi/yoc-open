/* cpu_pwr_lib.c - CPU power manager common library */

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

#ifndef __cpu_pwr_lib_h__
#define __cpu_pwr_lib_h__

#ifdef __cplusplus
extern "C" {
#endif

#include "k_api.h"
#include "k_cpuset.h"
#include "pwr_state.h"
#include "dl_list.h"

#ifndef container_of
#define container_of(ptr, type, member) \
        ((type *)((char *)(ptr) - offsetof(type,member)))
#endif /* container_of */

/* Maximum number of CPUs */

#ifdef RHINO_CONFIG_SMP
#define CPUS_NUM_MAX     4
#else
#define CPUS_NUM_MAX     1
#endif /* RHINO_CONFIG_SMP */

extern void   cpu_pwrmgmt_init(void);
extern void   cpu_pwr_down (void);
extern void   cpu_pwr_up (void);
extern void    cpu_pwr_enabled (int enabled);

#if RHINO_CONFIG_CPU_PWR_P_STATE_SUPPORT
extern void (*_func_cpu_pwr_idle_enter_hook) (void);
extern void (*_func_cpu_pwr_int_enter_hook)  (void);
extern void (*_func_cpu_pwr_int_exit_hook)  (void);
#endif /* RHINO_CONFIG_CPU_PWR_P_STATE_SUPPORT */

extern void   (*_func_cpu_tickless_up) (void);
extern void   (*_func_cpu_tickless_down) (void);
extern kstat_t (*_func_tickless_ignore_list_add) (klist_t *p_tick_node);

#ifdef __cplusplus
}
#endif

#endif /* __cpu_pwr_lib_h__ */
