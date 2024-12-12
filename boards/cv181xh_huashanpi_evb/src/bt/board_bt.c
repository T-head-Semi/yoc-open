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
#include <drv/pin.h>
#include <drv/gpio.h>
#include "pinctrl-mars.h"

#if defined(CONFIG_BOARD_BT_RTL8723DS) && (CONFIG_BOARD_BT_RTL8723DS > 0)
#include <devices/rtl8723ds_bt.h>

#include <drv/pin.h>
#include <pinctrl-mars.h>
#include "cvi_type.h"
static void bt_pin_init(void)
{
    csi_gpio_t bt_dsi_gpio = {0};

    PINMUX_CONFIG(VIVO_CLK, XGPIOB_22);

    if (csi_gpio_init(&bt_dsi_gpio, BT_DIS_PIN_GRP) != CSI_OK) {
        printf("%s gpio init err \n",__func__);
        return;
    }
    csi_gpio_mode(&bt_dsi_gpio , (1 << BT_DIS_PIN_ID) , GPIO_MODE_PULLUP);
    csi_gpio_dir(&bt_dsi_gpio , (1 << BT_DIS_PIN_ID) , GPIO_DIRECTION_OUTPUT);
    csi_gpio_write(&bt_dsi_gpio , (1 << BT_DIS_PIN_ID), 0);
    aos_msleep(200);
    csi_gpio_write(&bt_dsi_gpio , (1 << BT_DIS_PIN_ID), 1);
    aos_msleep(500);
}

void board_bt_init(void)
{
#if defined(CONFIG_BOARD_BT_RTL8723DS) && (CONFIG_BOARD_BT_RTL8723DS > 0)
    rvm_uart_drv_register(RTL8723DS_DEV_BT_UART_ID);
    rtl8723ds_bt_config config = {
        .uart_id    = RTL8723DS_DEV_BT_UART_ID,
        .bt_dis_pin = BT_DISABLE_PIN,
    };

    bt_pin_init();

    bt_rtl8723ds_register(&config);

    extern int hci_h5_driver_init();
    hci_h5_driver_init();
#else
    printf("WARNING: NOT SUPPORT BT\n");
#endif
}
#endif //CONFIG_BOARD_BT_RTL8723DS
#endif // BOARD_BT_SUPPORT