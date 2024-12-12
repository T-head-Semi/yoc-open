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
#include <drv/gpio.h>
#include <drv/dma.h>
#include <sys_clk.h>

void board_gpio_init(void)
{
    csi_gpio_t gpio_handler;

    soc_clk_init();
    csi_gpio_init(&gpio_handler, 0);
}

void board_dma_init(void)
{
    csi_dma_t dma;
    csi_dma_init(&dma, 0);
}

void board_init(void)
{
    board_gpio_init();
    board_dma_init();
}
