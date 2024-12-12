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

#include <board.h>

#if defined(BOARD_BT_SUPPORT) && BOARD_BT_SUPPORT > 0
#include <stdlib.h>
#include <stdio.h>
#include <devices/devicelist.h>
#include <devices/rtl8723ds_bt.h>
#include <drv/pin.h>

void board_bt_init(void)
{
    rvm_uart_drv_register(1);

    csi_pin_set_mux(PG6, PG6_UART1_TX);
    csi_pin_set_mux(PG7, PG7_UART1_RX);

    csi_pin_set_mux(PG8, PG8_UART1_RTS);
    csi_pin_set_mux(PG9, PG9_UART1_CTS);

    csi_pin_set_mux(PG18, PIN_FUNC_GPIO);

    rtl8723ds_bt_config config = {
        .uart_id    = 1,
        .bt_dis_pin = PG18,
    };

    bt_rtl8723ds_register(&config);

    extern int hci_h5_driver_init();
    hci_h5_driver_init();
}
#endif
