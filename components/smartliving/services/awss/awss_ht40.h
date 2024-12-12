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

#ifndef __AWSS_HT40_H__
#define __AWSS_HT40_H__

#ifdef  AWSS_SUPPORT_HT40

#include <stdint.h>
#include "os.h"
#include "zconfig_ieee80211.h"
#include "zconfig_protocol.h"

#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

struct ht40_ctrl {
    uint16_t length;
    uint8_t filter;
    signed char rssi;
};

int ht40_init(void);
int awss_ieee80211_ht_ctrl_process(uint8_t *ht_ctrl, int len, int link_type,
                                   struct parser_res *res, signed char rssi);
int awss_recv_callback_ht_ctrl(struct parser_res *res);
#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
}
#endif
#endif
#endif

