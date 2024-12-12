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
#include <board.h>
#include <aos/kernel.h>
#include <aos/cli.h>
#include <ulog/ulog.h>
#include <drv/lradc.h>

#define TAG "app"

extern void  cxx_system_init(void);
extern void board_yoc_init(void);

static void lradc_irq_callback(uint32_t irq_status, uint32_t data)
{
    // Here, we only catpure key button's up IRQ to confirm user press key one times
    if (irq_status & LRADC_ADC0_UPPEND) {
        aos_cli_printf("user key is pressed one times\n");
    }
}

static int test_lradc(void)
{
    int ret = -1;

    printf("Run lradc test\n");

    ret = csi_lradc_init();
    if (ret) {
        printf("lradc init failed!\n");
        return -1;
    }

    csi_lradc_register_callback(lradc_irq_callback);

    return 0;
}

int main(int argc, char *argv[])
{
    cxx_system_init();
    board_yoc_init();
    test_lradc();
    while (1) {
        aos_msleep(3000);
    };
}