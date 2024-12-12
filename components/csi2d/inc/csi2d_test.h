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

#ifndef _CSI_2D_TEST_H_
#define _CSI_2D_TEST_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <time.h>
#include <stdint.h>

void test_fill_color(int time, int max_row);

void test_alpha_blend(int time, int max_row);

void test_mask_blending(int time, int max_row);

void test_transform_bilinear(int time, int max_row);

void test_gen_x(int time, int max_row);

#ifdef __linux__
static inline uint64_t csi_2d_get_us()
{
    struct timespec tsSturct;
    clock_gettime(CLOCK_MONOTONIC, &tsSturct);

    return tsSturct.tv_sec * 1000000 + tsSturct.tv_nsec / 1000;
}
#else
#include <drv/tick.h>
static inline uint64_t csi_2d_get_us()
{
    return csi_tick_get_us();
}
#endif

#ifdef __cplusplus
}
#endif

#endif