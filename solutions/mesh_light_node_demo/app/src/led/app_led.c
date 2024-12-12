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

#include <aos/aos.h>
#include <board.h>
#include <ulog/ulog.h>
#include <devices/gpiopin.h>
#include "app_main.h"
#include "drv_light.h"

#define TAG "APP_LED"

static int init_flag = 1;

#define ON  1
#define OFF 0

#if defined(BOARD_LED_NUM) && BOARD_LED_NUM
#if defined(BOARD_LED_PWM_NUM) && BOARD_LED_PWM_NUM

static pwm_dev_res_t pmw_light[3];

static pwm_port_func_t pwm_channel_config[] = {
#ifdef BOARD_LED0_PWM_CH
    {0, BOARD_LED0_PWM_CH},
#endif
#ifdef BOARD_LED1_PWM_CH
    {1, BOARD_LED1_PWM_CH},
#endif
#ifdef BOARD_LED2_PWM_CH
    {2, BOARD_LED2_PWM_CH},
#endif
};

static led_light_cfg_t led_light_config[]
    = { LED_LIGHT_MODEL(RGB_LIGHT, &pwm_channel_config[0], LOW_LIGHT, &pmw_light[0], BOARD_LED_PWM_NUM > 3? 3 : BOARD_LED_PWM_NUM) };

static void _led_init(void)
{
    if (init_flag) {
        led_light_init(led_light_config);
        init_flag = 0;
    }
}

static void _led_set(bool on, uint8_t r_s, uint8_t g_s, uint8_t b_s, uint8_t r_a, uint8_t g_a, uint8_t b_a)
{
    struct genie_rgb_op rgb_config;

    if (on) {
        rgb_config.rgb_config[0].power_switch = r_s;
        rgb_config.rgb_config[1].power_switch = g_s;
        rgb_config.rgb_config[2].power_switch = b_s;
        rgb_config.rgb_config[0].led_actual   = r_a;
        rgb_config.rgb_config[1].led_actual   = g_a;
        rgb_config.rgb_config[2].led_actual   = b_a;
    } else {
        rgb_config.rgb_config[0].power_switch = 0;
        rgb_config.rgb_config[1].power_switch = 0;
        rgb_config.rgb_config[2].power_switch = 0;
        rgb_config.rgb_config[0].led_actual   = 0;
        rgb_config.rgb_config[1].led_actual   = 0;
        rgb_config.rgb_config[2].led_actual   = 0;
    }

    led_light_control((void *)&rgb_config);
}
#elif defined(BOARD_LED_GPIO_NUM) && BOARD_LED_GPIO_NUM

static rvm_dev_t *led0;

static void _led_init(void)
{
    if (init_flag) {
        rvm_gpio_pin_drv_register(BOARD_LED0_GPIO_PIN);
        led0 = rvm_hal_gpio_pin_open_by_pin_name("gpio_pin", BOARD_LED0_GPIO_PIN);
        rvm_hal_gpio_pin_set_mode(led0, RVM_GPIO_MODE_PUSH_PULL);
        init_flag = 0;
    }
}

static void _led_set(bool on, uint8_t r_s, uint8_t g_s, uint8_t b_s, uint8_t r_a, uint8_t g_a, uint8_t b_a)
{
    (void)r_s;
    (void)g_s;
    (void)b_s,
    (void)r_a;
    (void)g_a;
    (void)b_a;
    if (on)
    {
        rvm_hal_gpio_pin_write(led0, RVM_GPIO_PIN_HIGH);
    else
    {
        rvm_hal_gpio_pin_write(led0, RVM_GPIO_PIN_LOW);
    }
}

#endif
#endif

void app_set_led_state(int state)
{
#if defined(BOARD_LED_NUM) && BOARD_LED_NUM
if(BOARD_LED_PWM_NUM == 3){
    _led_init();
    switch (state) {
        case LED_OFF:
            _led_set(OFF, OFF, OFF, OFF, 0, 0, 0);
            break;

        case LED_ON:
            _led_set(ON, ON, ON, ON, 255, 255, 255);
            break;

        case LED_ATTENTION_ON:
            _led_set(ON, ON, OFF, OFF, 255, 0, 0);
            break;

        case LED_ATTENTION_OFF:
            _led_set(OFF, OFF, OFF, OFF, 0, 0, 0);
            break;

        case LED_UNPROVED:
            _led_set(ON, OFF, ON, OFF, 0, 255, 0);
            break;

        case LED_PROVED:
            _led_set(ON, OFF, OFF, ON, 0, 0, 255);
            break;

        default:
            _led_set(OFF, OFF, OFF, OFF, 0, 0, 0);
            break;
    }
}else{
    LOGI(TAG, "LED State %s", state ? "on" : "off");
}
#else
    LOGI(TAG, "LED State %d", state);
#endif
}