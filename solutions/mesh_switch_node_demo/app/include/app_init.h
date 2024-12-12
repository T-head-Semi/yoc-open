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

#ifndef __APP_INIT_H
#define __APP_INIT_H

#define DEVICE_NAME "YoC Mesh Switch"

#define SWITCH_DEV_UUID                                                                                                \
    {                                                                                                                  \
        0xcf, 0xa0, 0xea, 0x72, 0x17, 0xd9, 0x11, 0xe8, 0x86, 0xd1, 0x5f, 0x1c, 0xe2, 0x8a, 0xdf, 0x00                 \
    }

/* Board hardware and yoc modules initilization */
void board_yoc_init(void);
void board_cli_init();

/* Switch the on off state for next round operation */
void prepare_onoff_state(uint8_t onoff);

#endif
