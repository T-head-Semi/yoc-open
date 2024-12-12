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

#include <vector>
#include "tmedia_backend_cvitek/cvi_vi/vi_cvi.h"

vi_cvi_fastconverge_param g_vi_cvi_converge_params;

extern "C" {
void cv_params_init();
}

extern unsigned char gc2053_ir_gc2093_rgb_cvi_isp_default_param[];
extern unsigned int gc2053_ir_gc2093_rgb_cvi_isp_default_param_len;

unsigned char *cvi_isp_param = NULL;
uint32_t cvi_isp_param_len = 0;

void cv_params_init(void)
{
    vi_cvi_fastconverge_param::param ir_param = {
        .luma   = {68, 80, 127, 349, 538},
        .bv     = {-100, 105, 232, 878, 933},
    };

    vi_cvi_fastconverge_param::param rgb_param = {
        .luma   = {63, 109, 374, 774, 1023},
        .bv     = {269, 702, 970, 1077, 1160},
    };

    g_vi_cvi_converge_params.params.push_back(ir_param);
    g_vi_cvi_converge_params.params.push_back(rgb_param);

    cvi_isp_param = gc2053_ir_gc2093_rgb_cvi_isp_default_param;
    cvi_isp_param_len = gc2053_ir_gc2093_rgb_cvi_isp_default_param_len;
}