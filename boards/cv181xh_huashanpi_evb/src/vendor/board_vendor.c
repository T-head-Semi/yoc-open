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

/**
 * @brief 板级厂商初始化，用于扩展未定义board_xxx_init等外设的初始化
 *        或板级需要测试验证的命令行初始化
 *        支持改函数的解决方案，在board_yoc_init函数的末尾调用
 */
extern void wifidrv_register_iwpriv_cmd(void);
extern void cli_reg_cmd_bt_stack(void);
extern void cli_reg_cmd_vendor(void);

void board_vendor_init()
{
#if defined(BOARD_BT_SUPPORT) && BOARD_BT_SUPPORT
    cli_reg_cmd_bt_stack();
#endif
#if defined(BOARD_WIFI_SUPPORT) && BOARD_WIFI_SUPPORT
    wifidrv_register_iwpriv_cmd();
#endif
#if defined(CONFIG_BOARD_VENDOR) && CONFIG_BOARD_VENDOR
    cli_reg_cmd_vendor();
#endif
}
