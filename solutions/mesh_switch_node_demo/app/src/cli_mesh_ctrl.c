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
#include <app_init.h>
#include <aos/cli.h>
#include <api/mesh.h>
#include "mesh_ctrl.h"

static const char *TAG = "Mesh CLI";

#define MESH_NODE_APP_CLICMD_COUNT 2

void cmd_mesh_control_func(char *wbuf, int wbuf_len, int argc, char **argv)
{
    uint8_t ack, onoff;
    int ret;

    if (argc < 3) {
        LOGE(TAG, "usage: meshonoff onoff ack\n");
        return ;
    }

    onoff = atoi(argv[1]);
    ack = atoi(argv[2]);

    if (ack == 0) {
        ret = gen_onoff_set(onoff, false);

        if (ret) {
            LOGE(TAG, "send unack msg LED failed");
        }
    } else if (ack == 1) {
        ret = gen_onoff_set(onoff, true);

        if (ret) {
            LOGE(TAG, "send ack msg LED failed");
        }
    }
}

void cmd_mesh_reset_func(char *wbuf, int wbuf_len, int argc, char **argv)
{
    LOGD(TAG, "Mesh Node Reset");
    bt_mesh_reset();
}

void cli_reg_cmd_switch_ctrl(void)
{
    static const struct cli_command cmd_info[MESH_NODE_APP_CLICMD_COUNT] = {
        {
            "meshonoff",
            "meshonoff <onoff 0,1> <ack 0,1>",
            cmd_mesh_control_func,
        },
        {
            "meshrst",
            "mesh reset",
            cmd_mesh_reset_func,
        },
    };

    aos_cli_register_commands(cmd_info, MESH_NODE_APP_CLICMD_COUNT);
}

