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

#ifndef __AWSS_MANUFACT_AP_FIND_H__
#define __AWSS_MANUFACT_AP_FIND_H__

#include <stdint.h>
#include "os.h"
#include "zconfig_ieee80211.h"

#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

#ifdef MANUFACT_AP_FIND_ENABLE
int manufact_ap_info_set(char *p_ssid_manu, char *p_pwd);
int manufact_ap_find(char *p_ssid, char *p_pwd, uint8_t *p_bssid);
#endif

#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
}
#endif
#endif
