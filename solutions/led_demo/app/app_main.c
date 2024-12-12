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

#include "board.h"
#include <aos/kernel.h>
#include <stdio.h>
#include <ulog/ulog.h>
#include <drv/gpio_pin.h>
#include <soc.h>
#define TAG "app"

extern void  cxx_system_init(void);
extern void board_yoc_init(void);

static csi_gpio_pin_t led_pin;
static int led_init(void)
{
    int ret = 0;
    
    ret = csi_gpio_pin_init(&led_pin, LED_PIN);
    if (ret) {
        printf("init err");
        return -1;
}
    /* Set pull-up mode */
    ret = csi_gpio_pin_mode(&led_pin, GPIO_MODE_PULLNONE);
    if (ret) {
        printf("init err");
        return -1;
}
    /* Set input mode */
    ret = csi_gpio_pin_dir(&led_pin, GPIO_DIRECTION_OUTPUT);
     if (ret) {
        printf("init err");
        return -1;
}

    return 0;
}

static void led_blink(void)
{
    while (1) {
        csi_gpio_pin_write(&led_pin, GPIO_PIN_LOW);  
        aos_msleep(1000);
        csi_gpio_pin_write(&led_pin, GPIO_PIN_HIGH);
        aos_msleep(1000);
    }
}

int main(int argc, char *argv[])
{
    cxx_system_init();
    board_yoc_init();

    led_init();
    LOGI(TAG, "app start........\n");
    LOGI(TAG, "Led blink triggers 3 seconds interval........\n");
    led_blink();

    return 0;
}