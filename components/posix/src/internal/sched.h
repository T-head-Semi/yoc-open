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

#ifndef __POSIX_INTERNAL_SCHED_H
#define __POSIX_INTERNAL_SCHED_H

#include <sched.h>
#include <pthread.h>
#include <aos/kernel.h>

/* Convert the schedule policy of posix to aos. */
static inline int sched_policy_posix2aos(int policy)
{
    switch (policy) {
        case SCHED_OTHER:
            return AOS_KSCHED_OTHER;
        case SCHED_FIFO:
            return AOS_KSCHED_FIFO;
        case SCHED_RR:
            return AOS_KSCHED_RR;
        default:
            return -1;
    }
}

/* Convert the schedule policy of aos to posix. */
static inline int sched_policy_aos2posix(int policy)
{
    switch (policy) {
        case AOS_KSCHED_OTHER:
            return SCHED_OTHER;
        case AOS_KSCHED_FIFO:
            return SCHED_FIFO;
        case AOS_KSCHED_RR:
            return SCHED_RR;
        default:
            return -1;
    }
}

/* In aos: lower priority value means higher priority.
 * In posix standard: higher priority value means higher priority.
 */
static inline int sched_priority_posix2aos(int policy, int priority)
{
    int pri = aos_sched_get_priority_max(policy) - priority;
    return pri < 0 ? 0 : pri;
}

#define sched_priority_aos2posix sched_priority_posix2aos

#endif /*__POSIX_INTERNAL_SCHED_H*/
