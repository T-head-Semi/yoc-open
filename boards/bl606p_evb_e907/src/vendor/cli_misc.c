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

#ifdef CONFIG_BOARD_BL606P_EVB
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <aos/cli.h>

#include <board.h>

static void cmd_board_ext_func(char *wbuf, int wbuf_len, int argc, char **argv)
{
    if (argc < 2) {
        return;
    }

    if (strcmp(argv[1], "init") == 0) {
#if defined(CONFIG_BOARD_PWM) && CONFIG_BOARD_PWM
        board_pwm_init();
#endif
#if defined(CONFIG_BOARD_ADC) && CONFIG_BOARD_ADC
        board_adc_init();
#endif
        printf("Please check the LED and button pin jumper\r\n");
    }
}

void cli_reg_cmd_board_ext(void)
{
    static const struct cli_command cmd_info = { "board", "board extend command.", cmd_board_ext_func };

    aos_cli_register_command(&cmd_info);
}
#else
void cli_reg_cmd_board_ext(void)
{
    ;
}

#endif
