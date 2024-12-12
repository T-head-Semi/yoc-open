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

#ifndef K_CRITICAL_H
#define K_CRITICAL_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup aos_rhino critical
 *  Critical zone protection, os use internally.
 *
 *  @{
 */

#if (RHINO_CONFIG_SYS_STATS > 0)
/* For measure max int disable count */
#define RHINO_INTDIS_MEAS_START() intrpt_disable_measure_start()
#define RHINO_INTDIS_MEAS_STOP()  intrpt_disable_measure_stop()
#else
#define RHINO_INTDIS_MEAS_START()
#define RHINO_INTDIS_MEAS_STOP()
#endif

/**
 * Critical zone begin.
 *
 * @return none
 */
#define RHINO_CRITICAL_ENTER()      \
    do {                            \
        RHINO_CPU_INTRPT_DISABLE(); \
        RHINO_INTDIS_MEAS_START();  \
    } while (0)

/**
 * Critical zone end.
 *
 * @return none
 */
#define RHINO_CRITICAL_EXIT()       \
    do {                            \
        RHINO_INTDIS_MEAS_STOP();   \
        RHINO_CPU_INTRPT_ENABLE();  \
    } while (0)

/**
 * Critical zone end and trigger scheduling.
 *
 * @return none
 */
#if (RHINO_CONFIG_CPU_NUM > 1)
#define RHINO_CRITICAL_EXIT_SCHED() \
    do {                            \
        RHINO_INTDIS_MEAS_STOP();   \
        core_sched();               \
        cpu_intrpt_restore(cpsr);   \
    } while (0)
#else
#define RHINO_CRITICAL_EXIT_SCHED() \
    do {                            \
        RHINO_INTDIS_MEAS_STOP();   \
        core_sched();               \
        RHINO_CPU_INTRPT_ENABLE();  \
    } while (0)
#endif

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* K_CRITICAL_H */

