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

extern void cli_reg_cmd_board_specific(void);
extern void cli_reg_cmd_bt_stack(void);
extern void wifidrv_register_iwpriv_cmd(void);
void board_vendor_init(void)
{
#if defined(CONFIG_BOARD_BT) && CONFIG_BOARD_BT
    cli_reg_cmd_bt_stack();
#endif
#if defined(CONFIG_BOARD_WIFI) && CONFIG_BOARD_WIFI
    wifidrv_register_iwpriv_cmd();
#endif
    cli_reg_cmd_board_specific();
}
