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

#ifndef __IOTX_OTA_H__
#define __IOTX_OTA_H__

int iotx_ota_get_config(void *handle, const char *configScope, const char *getType,
                        const char *attributeKeys);

int iotx_req_image(void *handle, const char *version);
int iotx_ota_download(void *pcontext, const char *payload, unsigned int payload_len);

#endif  /* #ifndef __IOTX_OTA_H__ */
