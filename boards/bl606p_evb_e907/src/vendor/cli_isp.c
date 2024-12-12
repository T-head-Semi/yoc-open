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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bl606p_hbn.h>
#include <aos/cli.h>
#include <aos/kernel.h>

typedef enum {
    ISP_REBOOT_AS_BOOTPIN,           /*!< reboot as bootpin level */
    ISP_REBOOT_FROM_INTERFACE,       /*!< reboot from interface, download mode */
    ISP_REBOOT_FROM_MEDIA,           /*!< reboot from media, running mode */
    ISP_REBOOT_MAX                   /*!< reboot max value */
} isp_reboot_cfg_t;

void isp_reboot_config(isp_reboot_cfg_t rbot)
{
    switch(rbot){
        case ISP_REBOOT_AS_BOOTPIN:
            HBN_Set_Hand_Off_Config(0);
            break;
        case ISP_REBOOT_FROM_INTERFACE:
            HBN_Set_Hand_Off_Config(1);
            break;
        case ISP_REBOOT_FROM_MEDIA:
            HBN_Set_Hand_Off_Config(2);
            break;
        default :
            HBN_Set_Hand_Off_Config(0);
        break;
    }
}

static void cmd_ispboot_func(char *wbuf, int wbuf_len, int argc, char **argv)
{   
    if (argc < 2) {
        printf("usage:\r\n");
        printf("ispboot if/media\r\n");
        return;
    }
    
    if (strcmp(argv[1], "if") == 0) {
        isp_reboot_config(ISP_REBOOT_FROM_INTERFACE);
        aos_reboot();
    } else if (strcmp(argv[1], "media") == 0) {
        isp_reboot_config(ISP_REBOOT_FROM_MEDIA);
        aos_reboot();
    } else {
        printf("error\r\n");
    }
}

void cli_reg_cmd_isp(void)
{
    static const struct cli_command cmd_info = { "ispboot", "isp boot command.", cmd_ispboot_func };

    aos_cli_register_command(&cmd_info);
}
