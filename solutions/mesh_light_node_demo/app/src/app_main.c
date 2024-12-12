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

#include "api/mesh.h"

#include "mesh_node.h"
#include "ota_version.h"
#include "mesh_ctrl.h"
#include "app_main.h"
#include "app_init.h"

#define TAG "DEMO"

static aos_sem_t sync_sem;

int main()
{
    int ret;

    board_yoc_init();

    LOGI(TAG, "Mesh light node demo %s", aos_get_app_version());

    app_set_led_state(LED_OFF);

    /* Mesh Models and Device parameter setting, include models event callback regiter */
    ret = mesh_dev_init();

    if (ret) {
        LOGE(TAG, "mesh dev init failed");
    }

    aos_sem_new(&sync_sem, 0);

    while (1) {
        aos_sem_wait(&sync_sem, AOS_WAIT_FOREVER);
    }

    return 0;
}
