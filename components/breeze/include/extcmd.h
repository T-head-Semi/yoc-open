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

#ifndef BZ_EXTCMD_H
#define BZ_EXTCMD_H

#include <stdint.h>
#include "common.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define BZ_EXT_MAX_TLV_01_RSP_LEN       26

#define BZ_EXT_TX_BUFF_LEN              255 /**< Tx buffer size. */

typedef struct extcmd_s {
    tx_func_t tx_func;
    uint8_t tlv_01_rsp[BZ_EXT_MAX_TLV_01_RSP_LEN];
    uint8_t tlv_01_rsp_len;
    uint32_t model_id;
    uint8_t*p_product_key;
    uint8_t product_key_len;
    uint8_t *p_device_secret;
    uint8_t device_secret_len;
    uint8_t *p_device_name;
    uint8_t device_name_len;
    uint8_t tx_buff[BZ_EXT_TX_BUFF_LEN];
} extcmd_t;

ret_code_t extcmd_init(ali_init_t const *p_init, tx_func_t tx_func);
void extcmd_rx_command(uint8_t cmd, uint8_t *p_data, uint16_t length);

#ifdef __cplusplus
}
#endif

#endif // BZ_EXTCMD_H
