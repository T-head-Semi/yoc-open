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

#include <stdlib.h>
#include <stdio.h>
#include <drv/uart.h>
#include <board.h>

csi_uart_t g_console_handle;
static volatile int g_tx_async_flag = 0;
static char *g_data = "ABCDEFGHIJKLMN\r\n";

static void _uart_event_cb_fun(csi_uart_t *uart_handler, csi_uart_event_t event, void *arg)
{
    switch (event) {
    case UART_EVENT_SEND_COMPLETE:
        g_tx_async_flag = 1;
        break;
    default:
        break;
    }
}

int example_uart(void)
{
    int ret;
    /* init the console */
    csi_uart_init(&g_console_handle, CONSOLE_UART_IDX);

    /* config the UART */
    csi_uart_baud(&g_console_handle, CONFIG_CLI_USART_BAUD);
    csi_uart_format(&g_console_handle, UART_DATA_BITS_8, UART_PARITY_NONE, UART_STOP_BITS_1);
    printf("bare_drv_uart demo start\n");

    printf("==uart_test_sync_mode start==\n");
    ret = csi_uart_send(&g_console_handle, g_data, strlen(g_data), 200);
    if (ret != strlen(g_data))
        goto error;
    for (int i = 0; i < ret; i++)
        csi_uart_putc(&g_console_handle, g_data[i]);
    printf("==uart_test_sync_mode end==\n");

    printf("==uart_test_async_mode start==\n");
    csi_uart_uninit(&g_console_handle);

    /* FIXME: may be cause NO.7 busy detect irq on async mode for some cpu with xiaohui fpga */
    mdelay(100);
    csi_uart_init(&g_console_handle, CONSOLE_UART_IDX);
    csi_uart_baud(&g_console_handle, CONFIG_CLI_USART_BAUD);
    csi_uart_format(&g_console_handle, UART_DATA_BITS_8, UART_PARITY_NONE, UART_STOP_BITS_1);

    csi_uart_attach_callback(&g_console_handle, &_uart_event_cb_fun, NULL);
    csi_uart_send_async(&g_console_handle, g_data, strlen(g_data));
    while (g_tx_async_flag == 0);
    printf("==uart_test_async_mode end==\n");

    printf("bare_drv_uart success\n");
    return 0;

error:
    printf("bare_drv_uart failed\n");
    return -1;
}

