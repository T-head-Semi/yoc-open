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
#include <aos/kernel.h>
#include <errno.h>
#include <aos/hal/uart.h>

#define EVENT_WRITE 0x0F0F0000
#define EVENT_READ  0x00000F0F


typedef struct {
    aos_event_t    event_write_read;
    void *priv;
    int (*rx_read)(const uint8_t *buf, uint32_t size);
    int (*tx_write)(const uint8_t *data, uint32_t size);
} ipc_uart_dev_t;

static ipc_uart_dev_t g_ipc_uart_idx[1];


int32_t hal_uart_init(uart_dev_t *uart)
{
    ipc_uart_dev_t *ipc_uart = &g_ipc_uart_idx[0];

    if (aos_event_new(&ipc_uart->event_write_read, 0) != 0) {
        return -1;
    }

    return 0;
}

int32_t hal_uart_send_poll(uart_dev_t *uart, const void *data, uint32_t size)
{
    ipc_uart_dev_t *ipc_uart = &g_ipc_uart_idx[0];

    ipc_uart->tx_write((const uint8_t *)data, size);

    return size;
}

int32_t hal_uart_send(uart_dev_t *uart, const void *data, uint32_t size, uint32_t timeout)
{
    ipc_uart_dev_t *ipc_uart = &g_ipc_uart_idx[0];

    ipc_uart->tx_write((const uint8_t *)data, size);

    return size;
}

int32_t hal_uart_recv(uart_dev_t *uart, void *data, uint32_t expect_size, uint32_t timeout)
{
    unsigned int actl_flags;
    int          ret = 0;
    long long    time_enter, used_time;
    void *       temp_buf   = data;
    uint32_t     temp_count = expect_size;
    time_enter              = aos_now_ms();

    ipc_uart_dev_t *ipc_uart = &g_ipc_uart_idx[0];

    while (1) {
        ret = ipc_uart->rx_read((const uint8_t *)temp_buf, temp_count);

        temp_count = temp_count - ret;
        temp_buf   = (uint8_t *)temp_buf + ret;

        if (temp_count == 0 || timeout == 0 ||
            timeout <= (used_time = aos_now_ms() - time_enter)) {
            break;
        }

        if (aos_event_get(&ipc_uart->event_write_read, EVENT_READ, AOS_EVENT_OR_CLEAR, &actl_flags,
                          timeout - used_time) == -1) {
            break;
        }
    }

    return expect_size - temp_count;
}

int32_t hal_uart_recv_poll(uart_dev_t *uart, void *data, uint32_t expect_size)
{
    return hal_uart_recv(uart, data, expect_size, -1);
}

int32_t hal_uart_recv_II(uart_dev_t *uart, void *data, uint32_t expect_size,
                         uint32_t *recv_size, uint32_t timeout)
{
    *recv_size = hal_uart_recv(uart, data, expect_size, timeout);

    return 0;
}

int32_t hal_uart_finalize(uart_dev_t *uart)
{
    ipc_uart_dev_t *ipc_uart = &g_ipc_uart_idx[0];

    aos_event_free(&ipc_uart->event_write_read);

    return 0;
}


void log_ipc_uart_register(int id, int (*read)(const uint8_t *buf, uint32_t size),
                            int (*write)(const uint8_t *data, uint32_t size))
{
    ipc_uart_dev_t *ipc_uart = &g_ipc_uart_idx[0];

    ipc_uart->tx_write = write;
    ipc_uart->rx_read = read;
}


void log_ipc_read_event(void)
{
    ipc_uart_dev_t *ipc_uart = &g_ipc_uart_idx[0];

    aos_event_set(&ipc_uart->event_write_read, EVENT_READ, AOS_EVENT_OR);
}

int32_t hal_uart_recv_cb_reg(uart_dev_t *uart, uart_rx_cb cb)
{
    return 0;
}
