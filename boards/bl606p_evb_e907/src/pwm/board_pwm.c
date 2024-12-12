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

#if defined(CONFIG_BOARD_PWM) && CONFIG_BOARD_PWM
#include <stdlib.h>
#include <stdio.h>

#include <drv/pin.h>
#include <drv/gpio.h>

void board_pwm_init(void)
{
    csi_pin_set_mux(GPIO_PIN_17, GPIO17_PWM1_CH1P);
    csi_pin_set_mux(GPIO_PIN_18, GPIO18_PWM1_CH2P);
    csi_pin_set_mux(GPIO_PIN_19, GPIO19_PWM1_CH3P);
}
#endif

