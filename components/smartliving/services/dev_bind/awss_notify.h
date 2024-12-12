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

#ifndef __AWSS_NOTIFY_H__
#define __AWSS_NOTIFY_H__

#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif
#include "sl_config.h"

enum {
    AWSS_NOTIFY_DEV_INFO = 0,            // BASE_INFO: Device base information, coap notify
    AWSS_NOTIFY_DEV_BIND_TOKEN,          // BASE_INFO + bind token, coap notify
    AWSS_NOTIFY_DEV_RAND_SIGN,           // BASE_INFO + rand + sign, coap notify
    AWSS_NOTIFY_SUCCESS,                 // BASE_INFO + device type, coap notify
    AWSS_NOTIFY_DEV_RESP,                // BASE_INFO + device awss response, coap response
    AWSS_NOTIFY_TYPE_MAX,
};

#ifdef WIFI_PROVISION_ENABLED
int awss_suc_notify();
int awss_devinfo_notify();
int awss_suc_notify_stop();
int awss_devinfo_notify_stop();
#endif

int awss_dev_bind_notify();
int awss_dev_bind_notify_stop();
int awss_notify_dev_info(int type, int count);
int online_mcast_get_device_info(void *ctx, void *resource, void *remote, void *request);
int online_ucast_get_device_info(void *ctx, void *resource, void *remote, void *request);

#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
}
#endif

#endif
