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

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <aos/cli.h>
#include <aos/kernel.h>
#include <yoc/sysinfo.h>

#define HELP_INFO \
    "Usage: sys <command>\n" \
    "\tos: show os version\n" \
    "\tapp: show app version\n" \
    "\tid: show device id\n" \
    "\treboot: reboot sys\n"

static void cmd_get_sysinfo_func(char *wbuf, int wbuf_len, int argc, char **argv)
{
    char *ret = NULL;
    if (argc > 1) {
        if (0 == strcmp(argv[1], "os")) {
            ret = aos_get_os_version();
            if(ret == NULL){
                printf("os version is NULL\n");
            } else {
                printf("%s\n", ret);
            }
            return;
        } else if (0 == strcmp(argv[1], "id")) {
            ret = aos_get_device_id();
            if(ret == NULL){
                printf("device id is NULL\n");
            } else {
                printf("%s\n", ret);
            }
            return;
        } else if (0 == strcmp(argv[1], "app")) {
            ret = aos_get_app_version();
            if(ret == NULL){
                printf("app version is NULL\n");
            } else {
                printf("%s\n", ret);
            }
            return;
        } else if (0 == strcmp(argv[1], "reboot")) {
            aos_reboot();
            return;
        } else if (0 == strcmp(argv[1], "sleep")) {
            if (argc == 3 && argv[2]) {
                aos_msleep(atoi(argv[2]) * 1000);
                return;
            }
        } else if (0 == strcmp(argv[1], "crash")) {
            // int *ptr = (int *)0x7f000001;
            // *ptr = 1;

            if (argc <= 2) {
                int a = 100;
                int b = 0;
                int c = a / b;
                printf("a/b=%d\r\n", c);
            } else {
                int type = atoi(argv[2]);
                switch(type) {
                    case 0: {
                        int *nullprt = NULL;
                        *nullprt = 1;
                        break;
                    }
                    case 1: {
                        typedef void (*func_ptr_t)();
                        func_ptr_t f = (func_ptr_t)0x12345678;
                        f();
                        break;
                    }
                    case 2: {
                        int a = 100;
                        int b = 0;
                        int c = a / b;
                        printf("a/b=%d\r\n", c);
                        break;
                    }
                    default: {
                        int a = 100;
                        int b = 0;
                        int c = a / b;
                        printf("a/b=%d\r\n", c);
                        break;
                    }
         
                }
            }
            return;
        }
    }

    printf(HELP_INFO);
}

void cli_reg_cmd_sysinfo(void)
{
    static const struct cli_command cmd_info = {
        "sys",
        "sys comand",
        cmd_get_sysinfo_func,
    };

    aos_cli_register_command(&cmd_info);
}
