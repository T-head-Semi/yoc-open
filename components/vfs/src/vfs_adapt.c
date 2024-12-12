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

#include <stdint.h>
#include <aos/kernel.h>
#include "vfs_adapt.h"

void *vfs_lock_create(void)
{
    int32_t   ret;
    aos_mutex_t *mutex;

    mutex = aos_malloc(sizeof(aos_mutex_t));
    if (mutex == NULL) {
        return NULL;
    }
    ret = aos_mutex_new(mutex);
    if (ret != 0) {
        aos_free(mutex);
        return NULL;
    }

    return (void *)mutex;
}

int32_t vfs_lock_free(void *lock)
{
    aos_mutex_t *m = (aos_mutex_t *)lock;

    if (m == NULL) {
        return -1;
    }
    aos_mutex_free(m);
    aos_free(m);

    return 0;
}

int32_t vfs_lock(void *lock)
{
    int ret = aos_mutex_lock((aos_mutex_t *)lock, AOS_WAIT_FOREVER);
    return ret;
}

int32_t vfs_unlock(void *lock)
{
    int ret =  aos_mutex_unlock((aos_mutex_t *)lock);
    return ret;
}

void *vfs_malloc(uint32_t size)
{
    return aos_malloc(size);
}

void vfs_free(void *ptr)
{
    aos_free(ptr);
}
