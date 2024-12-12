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

#ifndef _SEMAPHORE_H
#define _SEMAPHORE_H

#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SEM_FAILED ((sem_t *)0)
#define SEM_VALUE_MAX 32767

typedef struct {
    void *aos_sem;
} sem_t;

int    sem_init(sem_t *sem, int pshared, unsigned int value);
sem_t *sem_open(const char *name, int oflag, ...);
int    sem_post(sem_t *sem);
int    sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);
int    sem_trywait(sem_t *sem);
int    sem_unlink(const char *name);
int    sem_wait(sem_t *sem);
int    sem_getvalue(sem_t *sem, int *sval);
int    sem_close(sem_t *sem);
int    sem_destroy(sem_t *sem);

#ifdef __cplusplus
}
#endif

#endif /* _SEMAPHORE_H */
