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




#ifndef _IOTX_COMMON_BASE64_H_
#define _IOTX_COMMON_BASE64_H_

#include <stdint.h>

#define UTILS_BASE64_TEST

typedef enum iotx_err
{
    FAIL_RETURN = 0,
    SUCCESS_RETURN
}iotx_err_t;

iotx_err_t utils_base64encode(const uint8_t *data, uint32_t inputLength, uint32_t outputLenMax,
                              uint8_t *encodedData, uint32_t *outputLength);
iotx_err_t utils_base64decode(const uint8_t *data, uint32_t inputLength, uint32_t outputLenMax,
                              uint8_t *decodedData, uint32_t *outputLength);

void utils_base64_encode_stream(int (*read_data)(uint8_t *data, void *opaque), void (*write_data)(const uint8_t data[4], void *opaque), void *opaque);
int base64_cli_init(void);

#endif
