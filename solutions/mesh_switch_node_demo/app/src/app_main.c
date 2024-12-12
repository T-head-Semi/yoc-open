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

#include <aos/aos.h>
#include <app_main.h>
#include <app_init.h>
#include "mesh_node.h"
#include <api/mesh.h>
#include "mesh_ctrl.h"
#include "cli_mesh_ctrl.h"

#define TAG "DEMO"

struct {
    uint8_t   button1_press : 1;
    uint8_t   button2_press : 1;
    uint8_t   on_off        : 1;
    aos_sem_t sync_sem;
} switch_state = { 0 };

void prepare_onoff_state(uint8_t onoff)
{
    switch_state.on_off = onoff;
}

int main()
{
    int ret;

    /* Board Hardware and yoc modules init */
    board_yoc_init();

    LOGI(TAG, "Mesh Switch node demo %s", aos_get_app_version());

    app_set_led_state(LED_OFF);

    /* Mesh Models and Device parameter setting, include models event callback regiter */
    ret = mesh_dev_init();

    if (ret) {
        LOGE(TAG, "mesh dev init failed");
    }

    /* Mesh CLI command handle register */
    cli_reg_cmd_switch_ctrl();

    aos_sem_new(&switch_state.sync_sem, 0);

    /* Wait for button signal to publish on/off command to default group */
    while (1) {
        aos_sem_wait(&switch_state.sync_sem, AOS_WAIT_FOREVER);

        if (switch_state.button1_press) {
            switch_state.button1_press = 0;
            ret                        = gen_onoff_set(switch_state.on_off, false);

            if (ret) {
                LOGE(TAG, "send unack msg LED failed");
            } else {
                LOGI(TAG, "send unack msg LED %s", switch_state.on_off ? "ON" : "OFF");
            }

            prepare_onoff_state(!switch_state.on_off);
        }

        if (switch_state.button2_press) {
            switch_state.button2_press = 0;
            ret                        = gen_onoff_set(switch_state.on_off, true);

            if (ret) {
                LOGE(TAG, "send ack msg LED failed");
            } else {
                LOGI(TAG, "send ack msg LED %s", switch_state.on_off ? "ON" : "OFF");
            }
        }
    }

    return 0;
}
