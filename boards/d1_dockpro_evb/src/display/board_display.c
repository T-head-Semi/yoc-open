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

#if defined(CONFIG_BOARD_DISPLAY) && CONFIG_BOARD_DISPLAY > 0
#include <stdio.h>
#include <drv/pin.h>
#include <drv/d1_display.h>

void board_display_init(void)
{
    csi_pin_set_mux(PG14, PIN_FUNC_GPIO);
    csi_pin_set_mux(PG15, PIN_FUNC_GPIO);

    d1_touch_config_t config = {
        .iic_addr = 0x5D,
        .iic_port = 2,
        .int_pin  = PG14,
        .rst_pin  = PG15,
    };

    drv_d1_display_register();

    drv_d1_gt9xx_touch_register(&config);
}
#endif
