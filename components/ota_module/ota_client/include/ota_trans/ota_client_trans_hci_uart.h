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
#ifndef _OTA_TRANS_CLIENT_HCI_UART_H
#define _OTA_TRANS_CLIENT_HCI_UART_H

int ota_client_trans_hci_uart_init(void (*cb)(uint8_t, void *, uint16_t));
int ota_client_trans_hci_uart_disconnect();
int ota_client_trans_hci_uart_send(uint8_t msg_id, uint8_t cmd, uint8_t *p_msg, uint16_t len, uint8_t ack);

#endif
