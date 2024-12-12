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

#include <stdio.h>
#include "k_api.h"

#if (RHINO_CONFIG_CPU_USAGE_STATS > 0)
void idle_count_set(idle_count_t value)
{
    CPSR_ALLOC();

    RHINO_CPU_INTRPT_DISABLE();

    g_idle_count[cpu_cur_get()] = value;

    RHINO_CPU_INTRPT_ENABLE();
}

idle_count_t idle_count_get(void)
{
    CPSR_ALLOC();
    idle_count_t idle_count;

    RHINO_CPU_INTRPT_DISABLE();

    idle_count = g_idle_count[cpu_cur_get()];

    RHINO_CPU_INTRPT_ENABLE();

    return idle_count;
}
#endif

void idle_task(void *arg)
{
    uint8_t cpu_num;
#if (RHINO_CONFIG_CPU_NUM > 1)
    CPSR_ALLOC();
    klist_t *head;
    ktask_t *task_del;
    head =  &g_task_del_head;
#endif

    /* avoid warning */
    (void)arg;
    cpu_num = cpu_cur_get();

#if (RHINO_CONFIG_USER_HOOK > 0)
    krhino_idle_pre_hook();
#endif

    while (RHINO_TRUE) {
#if (RHINO_CONFIG_CPU_NUM > 1)
        RHINO_CPU_INTRPT_DISABLE();
        if (head->next != head) {
            task_del = krhino_list_entry(head->next, ktask_t, task_del_item);
            if (task_del->cur_exc == 0) {
                klist_rm(&task_del->task_del_item);
                if (task_del->mm_alloc_flag == K_OBJ_DYN_ALLOC) {
                    krhino_task_dyn_del(task_del);
                } else {
                    krhino_task_del(task_del);
                }
            }
        }
        RHINO_CPU_INTRPT_ENABLE();
#endif
        /* type conversion is used to avoid compiler optimization */
        *(volatile idle_count_t *)(&g_idle_count[cpu_num]) = g_idle_count[cpu_num] + 1;

#if (RHINO_CONFIG_USER_HOOK > 0)
        krhino_idle_hook();
#endif

#if (RHINO_CONFIG_PWRMGMT > 0)
        cpu_pwr_down();
#endif
    }
}

