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
#ifndef _BAORD_AUDIO_H_
#define _BAORD_AUDIO_H_

/* 音频参数配置 */
//#define AUIDO_IN_GAIN_MIC 27 /*db*/
//#define AUIDO_IN_GAIN_REF 6  /*db*/
//#define AUIDO_OUT_GAIN    0  /*db*/

//#define AUIDO_PA_MUTE_PIN 41

/**
 * 获取算法处理核的CPUID号
 */
int board_get_alg_cpuid(void);

/**
 * 音频系统初始化
 */
void board_audio_init(void);

/**
 * 采集增益配置
 *
 * @param[in]  id  通道id,0为起始值
 * @return  0:执行成功，其他值为失败
 */
int board_audio_in_set_gain(int id, int gain);

/**
 * 获取采集增益配置
 *
 * @param[in]  id  通道id,0为起始值
 * @return  获取当前配置值
 */
int board_audio_in_get_gain(int id);

/**
 * 播放增益配置
 *
 * @param[in]  id  通道,0为起始值
 *                 播放一般只有一路，可忽略该参数，直接传递0
 * @return  0:执行成功，其他值为失败
 */

int board_audio_out_set_gain(int id, int gain);

/**
 * 获取播放增益配置
 *
 * @param[in]  id  通道id,0为起始值
 * @return  获取当前配置值
 */
int board_audio_out_get_gain(int id);

#ifdef CONFIG_SMART_AUDIO
#include <smart_audio.h>
/**
 * 获取音量曲线配置
 *
 * @return 返回音量曲线配置结构体指针
 */
audio_vol_config_t *board_audio_out_get_vol_config(void);

/*EQ参数配置*/
#define EQ_TYPE_NONE     0
#define EQ_TYPE_HARDWARE 1
#define EQ_TYPE_SOFTWARE 2
uint8_t *board_eq_get_param(size_t *byte);
int      board_eq_set_param(void *data, int byte);
int      board_eq_show_param(void);
int      board_eq_get_type(void);
int      board_drc_set_param(void *data, int byte);
#endif /*CONFIG_SMART_AUDIO*/

/**
 * 获取PA控制引脚号
 */
int board_audio_get_pa_mute_pin(void);

#endif
