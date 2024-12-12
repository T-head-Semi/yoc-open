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



#ifndef _ALCS_LOCALSETUP_H_
#define _ALCS_LOCALSETUP_H_

#include "iot_export.h"

void alcs_localsetup_init(void *adapter_handle, void* coap_handler, char *product_key,char *device_name);
void alcs_localsetup_add_sub_device (void *adapter_handle,char *product_key,char *device_name);
void alcs_localsetup_deinit(void *handle);

#endif
