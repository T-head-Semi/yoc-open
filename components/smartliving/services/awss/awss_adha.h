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

#ifndef __AWSS_ADHA_H__
#define __AWSS_ADHA_H__

#if defined(AWSS_SUPPORT_ADHA) || defined(AWSS_SUPPORT_AHA)

#include "zconfig_lib.h"
#include "zconfig_protocol.h"

#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

struct adha_info {
    uint8_t try_idx;
    uint8_t cnt;
    uint8_t aplist[MAX_APLIST_NUM];
};

int awss_init_adha_aplist(void);
int awss_deinit_adha_aplist(void);
extern struct adha_info *adha_aplist;
extern const char *zc_adha_passwd;
extern const char *zc_adha_ssid;

#ifdef AWSS_SUPPORT_ADHA
int awss_open_adha_monitor(void);
int awss_close_adha_monitor(void);
int aws_send_adha_probe_req(void);

int awss_is_ready_switch_next_adha(void);
int awss_recv_callback_adha_ssid(struct parser_res *res);
int awss_ieee80211_adha_process(uint8_t *mgmt_header, int len, int link_type,
                                struct parser_res *res, signed char rssi);
#endif

#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
}
#endif
#endif  // end AWSS_SUPPORT_ADHA || AWSS_SUPPORT_AHA
#endif
