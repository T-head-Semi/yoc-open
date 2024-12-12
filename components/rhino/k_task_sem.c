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

#include "k_api.h"

#if (RHINO_CONFIG_TASK_SEM > 0)
kstat_t krhino_task_sem_create(ktask_t *task, ksem_t *sem, const name_t *name,
                               size_t count)
{
    kstat_t ret;

    if (task == NULL) {
        return RHINO_NULL_PTR;
    }

    NULL_PARA_CHK(task);

    ret = krhino_sem_create(sem, name, count);
    if (ret == RHINO_SUCCESS) {
        task->task_sem_obj = sem;
    } else {
        task->task_sem_obj = NULL;
    }

    return ret;
}

kstat_t krhino_task_sem_del(ktask_t *task)
{
    NULL_PARA_CHK(task);

    return krhino_sem_del(task->task_sem_obj);
}

kstat_t krhino_task_sem_give(ktask_t *task)
{
    NULL_PARA_CHK(task);

    return krhino_sem_give(task->task_sem_obj);
}

kstat_t krhino_task_sem_take(tick_t ticks)
{
    return krhino_sem_take(krhino_cur_task_get()->task_sem_obj, ticks);
}

kstat_t krhino_task_sem_count_set(ktask_t *task, sem_count_t count)
{
    NULL_PARA_CHK(task);

    return krhino_sem_count_set(task->task_sem_obj, count);
}

kstat_t krhino_task_sem_count_get(ktask_t *task, sem_count_t *count)
{
    NULL_PARA_CHK(task);

    return krhino_sem_count_get(task->task_sem_obj, count);
}
#endif

