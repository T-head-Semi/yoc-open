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

#ifndef _MQUEUE_H
#define _MQUEUE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#include <time.h>

#define DEFAULT_MQUEUE_SIZE  10240
#define DEFAULT_MAX_MSG_SIZE 1024

typedef int mqd_t;

struct mq_attr {
    long mq_flags;    /* message queue flags */
    long mq_maxmsg;   /* maximum number of messages */
    long mq_msgsize;  /* maximum message size */
    long mq_curmsgs;  /* number of messages currently queued */
};

mqd_t   mq_open(const char *name, int oflag, ...);
int     mq_close(mqd_t mqdes);
ssize_t mq_receive(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned *msg_prio);
int     mq_send(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned msg_prio);
int     mq_setattr(mqd_t mqdes, const struct mq_attr *mqstat, struct mq_attr *omqstat);
int     mq_getattr(mqd_t mqdes, struct mq_attr *mqstat);
ssize_t mq_timedreceive(mqd_t mqdes, char *msg_ptr, size_t msg_len, unsigned *msg_prio, const struct timespec *abs_timeout);
int     mq_timedsend(mqd_t mqdes, const char *msg_ptr, size_t msg_len, unsigned msg_prio, const struct timespec *abs_timeout);
int     mq_unlink(const char *name);

#ifdef __cplusplus
}
#endif

#endif /* _MQUEUE_H */
