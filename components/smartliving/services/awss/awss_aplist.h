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

#ifndef __AWSS_APLIST_H__
#define __AWSS_APLIST_H__

#include <stdint.h>
#include "os.h"
#include "zconfig_protocol.h"
#include "sl_config.h"

#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif
#ifdef AWSS_SUPPORT_APLIST
struct ap_info {
	uint8_t auth;
	uint8_t channel;
	uint8_t encry[2];
	uint8_t mac[ETH_ALEN];
	char ssid[ZC_MAX_SSID_LEN];
	signed char rssi;
};

void aws_try_adjust_chan(void);

int awss_clear_aplist(void);
int awss_is_ready_clr_aplist(void);
int awss_open_aplist_monitor(void);
int awss_close_aplist_monitor(void);
int awss_init_ieee80211_aplist(void);
int awss_deinit_ieee80211_aplist(void);
int awss_get_auth_info(uint8_t *ssid, uint8_t *bssid, uint8_t *auth,
                       uint8_t *encry, uint8_t *channel);
int awss_ieee80211_aplist_process(uint8_t *mgmt_header, int len, int link_type,
                                  struct parser_res *res, signed char rssi);
int awss_save_apinfo(uint8_t *ssid, uint8_t* bssid, uint8_t channel, uint8_t auth,
                     uint8_t pairwise_cipher, uint8_t group_cipher, signed char rssi);

/* storage to store apinfo */
extern struct ap_info *zconfig_aplist;
/* aplist num, less than MAX_APLIST_NUM */
extern uint8_t zconfig_aplist_num;
#endif

#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
}
#endif
#endif
