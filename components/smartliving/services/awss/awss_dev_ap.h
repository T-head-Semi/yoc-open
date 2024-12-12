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

#ifndef __AWSS_DEV_AP_H__
#define __AWSS_DEV_AP_H__

#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

typedef enum AWSS_MODE_t {
    AWSS_MODE_ZERO_CONFIG = 0,
    AWSS_MODE_DEVAP_CONFIG,
    AWSS_MODE_ONKEY_CONFIG,
    AWSS_MODE_BLE_CONFIG,
    AWSS_MODE_PHONEAP_CONFIG,
    AWSS_MODE_MAX
}awss_mode_t;

int awss_dev_ap_stop(void);
int awss_dev_ap_start(pair_success_callback pair_cb, int timeout_ms);
int wifimgr_process_dev_ap_switchap_request(void *ctx, void *resource, void *remote, void *request);
int wifimgr_process_dev_errcode_request(void *ctx, void *resource, void *remote, void *request);
int wifimgr_process_dev_ap_mcast_get_dev_info(void *ctx, void *resource, void *remote, void *request);

#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
}
#endif

#endif
