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

#ifndef K_SCHED_H
#define K_SCHED_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup aos_rhino sched
 *  Task schedule.
 *
 *  @{
 */

#define KSCHED_FIFO          0u
#define KSCHED_RR            1u
#define KSCHED_CFS           2u

#define SCHED_MAX_LOCK_COUNT 200u
#define NUM_WORDS            ((RHINO_CONFIG_PRI_MAX + 31) / 32)

/**
 * Ready tasks information
 * 'cur_list_item' as task ready list per priority.
 * When a task enters 'ready' from another state, it is put into the list;
 * When a task leaves 'ready' to another state, it is get out of the list;
 * The 'task_bit_map' is used to improve performance.
 * The Nth bit in the bitmap starting from msb corresponds to the priority N-1.
 */
typedef struct {
    klist_t  *cur_list_item[RHINO_CONFIG_PRI_MAX];
    uint32_t  task_bit_map[NUM_WORDS];
    uint8_t   highest_pri;
} runqueue_t;


typedef struct {
    /* to add */
    uint8_t dis_sched;
} per_cpu_t;

/**
 * Disable task schedule
 *
 * @return the operation status, RHINO_SUCCESS is OK, others is error
 */
kstat_t krhino_sched_disable(void);

/**
 * Enable task schedule
 *
 * @return the operation status, RHINO_SUCCESS is OK, others is error
 */
kstat_t krhino_sched_enable(void);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* K_SCHED_H */

