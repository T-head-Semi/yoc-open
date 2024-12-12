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

#include "av/avutil/av_inner_config.h"
#include "av/avutil/av_config.h"

static struct {
    int ao_diff_out;
    int ao_channel_num;
} g_av_configs = {
    CONFIG_AO_DIFF_SUPPORT,
    CONFIG_AV_AO_CHANNEL_NUM
};

/**
 * @brief  get number of audio output
 * @return
 */
int av_get_ao_channel_num()
{
    return g_av_configs.ao_channel_num;
}

/**
 * @brief  set number of audio output
 * @param  [in] num
 * @return
 */
void av_set_ao_channel_num(int num)
{
    g_av_configs.ao_channel_num = num;
}

/**
 * @brief  get whether audio diff-output
 * @return
 */
int av_ao_diff_is_enable()
{
    return g_av_configs.ao_diff_out;
}

/**
 * @brief  enable/disable audio diff-output
 * @param  [in] enable
 * @return
 */
void av_ao_diff_enable(int enable)
{
    g_av_configs.ao_diff_out = enable;
}


