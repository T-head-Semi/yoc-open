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
#ifndef _GATEWAY_OTA_PROCESS_H
#define _GATEWAY_OTA_PROCESS_H
#include <stdint.h>
#include "k_types.h"
#include "k_api.h"
#include "k_err.h"
#include "k_sys.h"
#include "k_list.h"
#include "k_obj.h"
#include "k_ringbuf.h"
#include "k_buf_queue.h"
#include "k_task.h"
#include "k_sem.h"
#include "k_mutex.h"
#include "k_timer.h"
#include "ota_server.h"

typedef union
{
    ota_state_ongoing ongoing_data;
    ota_state_success success_data;
    ota_state_fail    fail_data;
} ota_process_cmd_data;

typedef struct {
    uint8_t              event;
    ota_process_cmd_data data;
} ota_process_cmd_message;

typedef enum _ota_process_cmd
{
    OTA_EVENT_ONGOING   = 0x01,
    OTA_EVENT_SUCCESS   = 0x02,
    OTA_EVENT_FAILED     = 0x03,
    OTA_EVENT_SEND_CMD  = 0x04,
    OTA_EVENT_STOP_CMD  = 0x05,
    OTA_EVENT_EXIST_CMD = 0x06,
} ota_process_cmd;

typedef enum _ota_process_err
{
    OTA_PROCESS_SERVER_INIT_FAIL = 0x01,
    OTA_PROCESS_NO_DEV_FOUND     = 0x02,
    OTA_PROCESS_DEV_CANCEL       = 0x03,
    OTA_PROCESS_FIRMWARE_CANCEL  = 0x04,
    OTA_PROCESS_DEV_FAIL         = 0x05,
} ota_process_err;

int32_t ota_process_task_create(ktask_t *task_handle, void *arg, uint32_t stack, uint32_t priority);
int     ota_process_cmd_set(ota_process_cmd_message *cmd);

#endif
