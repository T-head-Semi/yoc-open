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

#ifndef BZ_TRANSPORT_H
#define BZ_TRANSPORT_H

#include <stdint.h>
#include "common.h"
#include "breeze_hal_os.h"
#include "bzopt.h"

#ifdef __cplusplus
extern "C"
{
#endif

enum {
    TX_NOTIFICATION,
    TX_INDICATION,
};

typedef uint32_t (*transport_tx_func_t)(uint8_t *p_data, uint16_t length);

#define TX_BUFF_LEN (BZ_MAX_SUPPORTED_MTU - 3)
#define RX_BUFF_LEN BZ_MAX_PAYLOAD_SIZE
typedef struct transport_s {
    struct {
        uint8_t buff[TX_BUFF_LEN];
        uint8_t *data;
        uint16_t len;
        uint16_t bytes_sent;
        uint8_t encrypted;
        uint8_t msg_id;
        uint8_t cmd;
        uint8_t total_frame;
        uint8_t frame_seq;
        uint8_t pad_len;
        uint16_t pkt_req;
        uint16_t pkt_cfm;
        os_timer_t timer;
        transport_tx_func_t active_func;
        void *mutex_indicate_done;
    } tx;
    struct {
        uint8_t buff[RX_BUFF_LEN];
        uint16_t buff_size;
        uint16_t bytes_received;
        uint8_t msg_id;
        uint8_t cmd;
        uint8_t total_frame;
        uint8_t frame_seq;
        os_timer_t timer;
    } rx;
    uint16_t max_pkt_size;
    void *p_key;
    uint16_t timeout;
    void *p_aes_ctx;
} transport_t;

struct rx_cmd_post_t{
    uint8_t cmd;
    uint8_t frame_seq;
    uint8_t *p_rx_buf;
    uint16_t buf_sz;
};

ret_code_t bz_transport_init(ali_init_t const *p_init);
void transport_reset(void);
ret_code_t transport_tx(uint8_t tx_type, uint8_t cmd,
                        uint8_t const *const p_data, uint16_t length);
void transport_txdone(uint16_t pkt_sent);
void transport_rx(uint8_t *p_data, uint16_t length);
uint32_t transport_update_key(uint8_t *p_key);

#ifdef __cplusplus
}
#endif

#endif // BZ_TRANSPORT_H
