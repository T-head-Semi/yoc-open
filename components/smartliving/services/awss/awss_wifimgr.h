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

#ifndef __AWSS_WIFIMGR_H__
#define __AWSS_WIFIMGR_H__

#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

#if defined(AWSS_SUPPORT_ADHA) || defined(AWSS_SUPPORT_AHA)

enum {
    SHUB_ERR,
    SHUB_OK
};

int wifimgr_process_get_wifilist_request(void *ctx, void *resource, void *remote, void *request);
int wifimgr_process_mcast_get_device_info(void *ctx, void *resource, void *remote, void *request);
int wifimgr_process_ucast_get_device_info(void *ctx, void *resource, void *remote, void *request);
int wifimgr_process_switch_ap_request(void *ctx, void *resource, void *remote, void *request);

#endif

#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
}
#endif

#endif
