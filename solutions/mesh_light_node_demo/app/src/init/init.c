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

#include <stdbool.h>
#include <aos/aos.h>
#include <aos/kv.h>
#include <yoc/yoc.h>
#include <yoc/partition.h>
#include <board.h>
#include "app_init.h"
#include "app_main.h"
#include "drv_light.h"

const char *TAG = "INIT";

void board_yoc_init()
{
    int ret;

    board_init();

#if defined(CONFIG_BOARD_BT) && CONFIG_BOARD_BT
    board_bt_init();
#endif

#if defined(CONFIG_BOARD_LED) && CONFIG_BOARD_LED
    board_led_init();
#endif

    console_init(CONSOLE_UART_IDX, CONFIG_CLI_USART_BAUD, 0);

#if defined(CONFIG_GW_SMARTLIVING_SUPPORT) && CONFIG_GW_SMARTLIVING_SUPPORT
    board_cli_init();
#endif

    ulog_init();
    aos_set_log_level(AOS_LL_DEBUG);

    /* load partition */
    ret = partition_init();

    if (ret <= 0) {
        LOGE(TAG, "partition init failed");
    } else {
        LOGI(TAG, "find %d partitions", ret);
    }

    /* kvfs init */
    aos_kv_init("kv");

    LOGI(TAG, "Build:%s,%s", __DATE__, __TIME__);
}
