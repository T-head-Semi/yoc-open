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

#ifndef AOS_MAILBOX_H
#define AOS_MAILBOX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <aos/list.h>


typedef struct channel     channel_t;

// irq hardware channel interface

#define CHANNEL_WRITE_EVENT (0x01)
#define CHANNEL_READ_EVENT (0x02)

typedef void (*channel_cb)(int event, void *priv);

struct channel {
    slist_t    next;

    channel_cb cb;
    void      *priv;
    uint32_t   des_id;
    void      *context;
};

int channel_put_message(channel_t *ch, void *msg, int len, uint32_t timeout_ms);// send message to channel
int channel_get_message(channel_t *ch, void *msg, int len, uint32_t timeout_ms);// read message from channel

//mailbox
channel_t *channel_mailbox_get(int cpu_id, channel_cb cb, void *priv);
int channel_mailbox_lpm(channel_t *ch, int state);

#endif // AOS_IPC_H
