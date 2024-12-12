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

#ifndef AOS_IPC_H
#define AOS_IPC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <aos/kernel.h>
#include <aos/list.h>

#ifdef __cplusplus
extern "C" {
#endif

#define  MESSAGE_ASYNC 0x00
#define  MESSAGE_SYNC  0x01
#define  MESSAGE_ACK   0x02
#define  SHM_CACHE     0x04
#define  MESSAGE_PROBE 0x08

typedef struct message_msg message_t;
typedef struct ipc         ipc_t;

typedef void (*ipc_process_t)(ipc_t *ipc, message_t *msg, void *priv);

struct message_msg {
    uint8_t         flag;            /** flag for MESSAGE_SYNC and MESSAGE_ACK */
    uint8_t         service_id;      /** service id for the service want to comtunicate */
    uint16_t        command;         /** command id the service provide */
    uint32_t        seq;             /** message seq */
    void           *req_data;        /** message data */
    int             req_len;         /** message len */
    uint64_t        queue;           /** queue for SYNC MESSAGE */
    void           *resp_data;
    int             resp_len;
};

/**
 * @brief  get a ipc base on cpu_id want to comtunicate
 * @param  [in] des_cpu_id: destionation cpu_id
 * @return ipc handle
 */
ipc_t     *ipc_get(int des_cpu_id);

/**
 * @brief  send a message
 * @param  [in] ipc          : ipc handle
 * @param  [in] msg          : message want to send
 * @param  [in] timeout_ms   : timeout in microsecond
 * @return 0 on success, -1 on failed
 */
int        ipc_message_send(ipc_t *ipc, message_t *msg, int timeout_ms);

/**
 * @brief  ack a message if it is a MESSAGE_SYNC message
 * @param  [in] ipc          : ipc handle
 * @param  [in] msg          : message arced back
 * @param  [in] timeout_ms   : timeout in microsecond
 * @return 0 on success, -1 on failed
 */
int        ipc_message_ack(ipc_t *ipc, message_t *msg, int timeout_ms);

/**
 * @brief  add a ervice to ipc
 * @param  [in] ipc          : ipc handle
 * @param  [in] service_id   : service id
 * @param  [in] cb           : callback
 * @param  [in] priv         : argv back to cb
 * @return 0 on success, -1 on failed
 */
int        ipc_add_service(ipc_t *ipc, int service_id, ipc_process_t cb, void *priv);

/**
 * @brief  ipc lpm
 * @param  [in] des_cpu_id: destionation cpu_id
 * @return ipc handle
 */

int         ipc_lpm(int cpu_id, int state);

#ifdef __cplusplus
}
#endif

#endif // AOS_IPC_H
