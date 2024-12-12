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

#ifndef HAL_UART_IMPL_H
#define HAL_UART_IMPL_H

#include <stdint.h>

#include <devices/driver.h>
#include <devices/uart.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef UART_DEV_MAX_NUM
#define UART_DEV_MAX_NUM 6UL
#endif

typedef struct uart_driver {
    driver_t drv;
    aos_mutex_t tx_mtx[UART_DEV_MAX_NUM];
    aos_mutex_t rx_mtx[UART_DEV_MAX_NUM];
    int (*config)(rvm_dev_t *dev, rvm_hal_uart_config_t *config);
    int (*config_get)(rvm_dev_t *dev, rvm_hal_uart_config_t *config);
    int (*set_buffer_size)(rvm_dev_t *dev, uint32_t size);
    int (*send_poll)(rvm_dev_t *dev, const void *data, uint32_t size);
    int (*recv_poll)(rvm_dev_t *dev, void *data, uint32_t size);
    int (*send)(rvm_dev_t *dev, const void *data, uint32_t size, uint32_t timeout_ms);
    int (*recv)(rvm_dev_t *dev, void *data, uint32_t size, uint32_t timeout_ms);
    int (*set_type)(rvm_dev_t *dev, int type);
    void (*set_event)(rvm_dev_t *dev, rvm_hal_uart_callback callback, void *priv);
    int (*trans_dma_enable)(rvm_dev_t *dev, bool enable);
    int (*get_state)(rvm_dev_t *dev, rvm_hal_uart_state_t *state);
} uart_driver_t;

#ifdef __cplusplus
}
#endif

#endif