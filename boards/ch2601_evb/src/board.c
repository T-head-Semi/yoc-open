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
#include <drv/pin.h>

static void board_pinmux_config(void)
{
    csi_pin_set_mux(CONSOLE_TXD, CONSOLE_TXD_FUNC);
    csi_pin_set_mux(CONSOLE_RXD, CONSOLE_RXD_FUNC);
}

void board_init(void)
{
    board_pinmux_config();
    board_uart_init();
    board_flash_init();
}

#if defined(CONFIG_KERNEL_RTTHREAD)
#include <rthw.h>
#include <rtthread.h>
#include <devices/uart.h>
#include <aos/console_uart.h>

extern unsigned long __heap_start;
extern unsigned long __heap_end;

void rt_hw_board_init(void)
{
    /* initalize interrupt */
    rt_hw_interrupt_init();

#ifdef RT_USING_HEAP
    /* initialize memory system */
    rt_system_heap_init((void *)&__heap_start, (void *)&__heap_end);
#endif

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif
}

extern int32_t aos_debug_printf(const char *fmt, ...);
void rt_hw_console_output(const char *str)
{
    aos_debug_printf("\r%s", str);
}

char rt_hw_console_getchar(void)
{
    int ch = -1;

    while (rvm_hal_uart_recv(console_get_uart(), &ch, 1, -1) != 1);

    return ch;
}
#endif /* CONFIG_KERNEL_RTTHREAD */
