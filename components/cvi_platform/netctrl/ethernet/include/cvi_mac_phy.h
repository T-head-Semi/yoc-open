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

#ifndef __CVI_MAC_PHY_H__
#define __CVI_MAC_PHY_H__


int csi_eth_mac_phy_init(void);
void csi_eth_phy_update_link_task(void *arg);
void csi_send_packet(uint8_t *buf, uint32_t len, uint32_t flags);
int32_t csi_receive_packet(uint8_t *buf, uint32_t len);
int32_t csi_get_macaddr(uint8_t *mac);
int32_t csi_set_macaddr(uint8_t *mac);
/* loopack test Ethernet code */
void loopback_test(void);

#endif
