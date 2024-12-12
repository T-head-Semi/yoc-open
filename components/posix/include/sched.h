
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

#ifndef _SCHED_H
#define _SCHED_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <sys/types.h>
#include <sys/timespec.h>

/* The scheduling policy */
#define SCHED_OTHER 0
#define SCHED_FIFO  1
#define SCHED_RR    2
#define SCHED_CFS   0 /* Alias to SCHED_OTHER */

struct sched_param {
    int      sched_priority; /* process execution scheduling priority */
    uint64_t slice;          /* time slice in SCHED_RR mode (ms) */
};

int sched_yield(void);
int sched_setscheduler(pid_t pid, int policy, const struct sched_param *param);
int sched_get_priority_min(int policy);
int sched_get_priority_max(int policy);
int sched_rr_get_interval(pid_t pid, struct timespec *interval);

#ifdef __cplusplus
}
#endif

#endif /*_SCHED_H*/
