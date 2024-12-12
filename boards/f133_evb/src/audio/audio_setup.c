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

#include <stdint.h>

#include <drv/codec.h>
#include "board_audio.h"

/* 默认采集增益 */


/*采集增益配置*/
int board_audio_in_set_gain(int id, int gain)
{
    return 0;
}

int board_audio_in_get_gain(int id)
{
    return 0;
}

/*播放增益配置*/
extern int auo_digtal_gain(void *context, float val);
int board_audio_out_set_gain(int id, int gain)
{
    return 0;
}

int board_audio_out_get_gain(int id)
{
    return 0;
}

#ifdef CONFIG_SMART_AUDIO
#include <smart_audio.h>
extern audio_vol_config_t g_vol_config;

audio_vol_config_t *board_audio_out_get_vol_config()
{
    return &g_vol_config;
}

/*EQ参数配置*/
int board_eq_set_param(void *data, int byte)
{
    if (data == NULL) {
        /*设置默认参数*/
       //TODO
        return 0;
    }
    return 0;
}

int board_eq_show_param(void)
{
    return 0;
}

int board_eq_get_type(void)
{
    return EQ_TYPE_NONE;
}

uint8_t *board_eq_get_param(size_t *byte)
{
    /*硬件EQ无需实现*/
    return NULL;
}

int board_drc_set_param(void *data, int byte)
{
    if (data == NULL) {
        /*设置默认参数*/
        //TODO
        return 0;
    }

    return 0;
}
#endif /*CONFIG_SMART_AUDIO*/

/*PA控制引脚*/
int board_audio_get_pa_mute_pin(void)
{
    return PB4;
}
