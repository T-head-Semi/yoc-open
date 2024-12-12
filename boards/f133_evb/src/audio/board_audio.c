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

#if defined(BOARD_AUDIO_SUPPORT) && BOARD_AUDIO_SUPPORT > 0
#include <stdlib.h>
#include <stdio.h>
#include <drv/codec.h>
#include <drv/pin.h>

void board_audio_init(void)
{
    csi_pin_set_mux(PD19, PD19_DMIC_DATA0);
    csi_pin_set_mux(PD20, PD20_DMIC_CLK);

    // Audio PA Enable
	csi_pin_set_mux(PB4, PIN_FUNC_GPIO);

    csi_codec_t codec;
    csi_codec_init(&codec, 0);
}
#endif
