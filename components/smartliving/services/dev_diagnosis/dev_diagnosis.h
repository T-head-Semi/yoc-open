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

#ifndef __DEV_DIAGNOSIS_H__
#define __DEV_DIAGNOSIS_H__

#define RESPONSE_ID "id"
#define RESPONSE_CODE "code"
#define RESPONSE_MESSAGE "message"
#define RESPONSE_METHOD "method"

#define DIAGNOSIS_FINISH_METHOD "device.diagonsis.finish"
#define TOPIC_DEV_DIAGNOSIS_FINISH_REPLY "/sys/device/diagonsis/finish_reply"

#define REPLAY_FINISH_PAYLOAD_LEN (64)
#define REPLAY_PAYLOAD_LEN (256)

#define TOPIC_URL_LEN (128)

#define GET_REPLY_FMT "{\"id\":%s,\"code\":%d,\"data\":%s}"

typedef enum _respose_code_e
{
    RESPONSE_CODE_OK = 200,
    RESPONSE_CODE_NO_PAYLOAD = 10000,
    RESPONSE_CODE_PARSE_JSON_FAILED,
    RESPONSE_CODE_METHOD_NOT_MATCH
} respose_code_e;

#include "iot_export.h"

#endif /* __DEV_DIAGNOSIS_H__ */