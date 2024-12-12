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

#include <cv181x_snd.h>

#include <board.h>

#include "board_audio.h"


void board_audio_init(void)
{
    snd_card_register(NULL);

    board_audio_out_set_gain(2, AUIDO_OUT_GAIN);

    // Enable PA, because default is mute
    board_audio_amplifier_onoff(1);
}
