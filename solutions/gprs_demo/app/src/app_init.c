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
#include <aos/kv.h>
#include <vfs.h>
#include <vfs_cli.h>
#include <uservice/uservice.h>
#include <littlefs_vfs.h>
#include <yoc/partition.h>
#include <yoc/init.h>
#include "board.h"
#include "app_main.h"
#ifdef AOS_COMP_DEBUG
#include <debug/dbg.h>
#endif

#define TAG "init"

static void stduart_init(void)
{
    extern void console_init(int idx, uint32_t baud, uint16_t buf_size);
    console_init(CONSOLE_UART_IDX, CONFIG_CLI_USART_BAUD, CONFIG_CONSOLE_UART_BUFSIZE);
}

/*static void fs_init(void)
{
    int ret;

    aos_vfs_init();
    ret = vfs_lfs_register("lfs");
    if (ret != 0) {
        LOGE(TAG, "littlefs register failed(%d)", ret);
        return;
    }
    LOGI(TAG, "filesystem init ok.");

    cli_reg_cmd_ls();
    cli_reg_cmd_rm();
    cli_reg_cmd_cat();
    cli_reg_cmd_mkdir();
    cli_reg_cmd_mv();
}*/

void board_yoc_init(void)
{
    board_init();
    stduart_init();
    board_cli_init();
    printf("###YoC###[%s,%s]\n\r", __DATE__, __TIME__);
    printf("cpu clock is %dHz\n\r", soc_get_cpu_freq(0));

    event_service_init(NULL);

#ifdef AOS_COMP_DEBUG
    aos_debug_init();
    printf("aos debug init ok.\n\r");
#endif
    ulog_init();

    aos_set_log_level(AOS_LL_DEBUG);

    // int ret = partition_init();
    // if (ret <= 0) {
    //     LOGE(TAG, "partition init failed \r\n");
    // } else {
    //     LOGI(TAG, "find %d partitions", ret);
    //     if (aos_kv_init("kv")) {
    //         LOGE(TAG, "kv init failed.");
    //     }
    //     fs_init();
    // }
}
