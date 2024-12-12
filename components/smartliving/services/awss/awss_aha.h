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

#ifndef __AWSS_AHA_H__
#define __AWSS_AHA_H__

#include <stdint.h>
#include "os.h"
#include "zconfig_ieee80211.h"

#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

int awss_open_aha_monitor(void);
int awss_close_aha_monitor(void);
int awss_aha_monitor_is_timeout(void);
int aws_send_aha_probe_req(void);
int awss_recv_callback_aha_ssid(struct parser_res *res);
int awss_ieee80211_aha_process(uint8_t *mgmt_header, int len, int link_type, struct parser_res *res, signed char rssi);

extern const char *zc_default_ssid;
extern const char *zc_default_passwd;

#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
}
#endif
#endif
