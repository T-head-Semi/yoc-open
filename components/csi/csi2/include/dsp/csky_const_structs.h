/*
 * Copyright (C) 2016-2019 C-SKY Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     csky_const_structs.h
 * @brief    This file has constant structs that are initialized for
 *           user convenience.  For example, some can be given as
 *           arguments to the csky_cfft_f32() function.
 * @version  V1.0
 * @date     20. Dec 2016
 ******************************************************************************/

#ifndef _CSKY_CONST_STRUCTS_H
#define _CSKY_CONST_STRUCTS_H

#include "csky_math.h"
#include "csky_common_tables.h"

   extern const csky_cfft_instance_f32 csky_cfft_sR_f32_len16;
   extern const csky_cfft_instance_f32 csky_cfft_sR_f32_len32;
   extern const csky_cfft_instance_f32 csky_cfft_sR_f32_len64;
   extern const csky_cfft_instance_f32 csky_cfft_sR_f32_len128;
   extern const csky_cfft_instance_f32 csky_cfft_sR_f32_len256;
   extern const csky_cfft_instance_f32 csky_cfft_sR_f32_len512;
   extern const csky_cfft_instance_f32 csky_cfft_sR_f32_len1024;
   extern const csky_cfft_instance_f32 csky_cfft_sR_f32_len2048;
   extern const csky_cfft_instance_f32 csky_cfft_sR_f32_len4096;

   extern const csky_cfft_instance_q31 csky_cfft_sR_q31_len16;
   extern const csky_cfft_instance_q31 csky_cfft_sR_q31_len32;
   extern const csky_cfft_instance_q31 csky_cfft_sR_q31_len64;
   extern const csky_cfft_instance_q31 csky_cfft_sR_q31_len128;
   extern const csky_cfft_instance_q31 csky_cfft_sR_q31_len256;
   extern const csky_cfft_instance_q31 csky_cfft_sR_q31_len512;
   extern const csky_cfft_instance_q31 csky_cfft_sR_q31_len1024;
   extern const csky_cfft_instance_q31 csky_cfft_sR_q31_len2048;
   extern const csky_cfft_instance_q31 csky_cfft_sR_q31_len4096;

   extern const csky_cfft_instance_q15 csky_cfft_sR_q15_len16;
   extern const csky_cfft_instance_q15 csky_cfft_sR_q15_len32;
   extern const csky_cfft_instance_q15 csky_cfft_sR_q15_len64;
   extern const csky_cfft_instance_q15 csky_cfft_sR_q15_len128;
   extern const csky_cfft_instance_q15 csky_cfft_sR_q15_len256;
   extern const csky_cfft_instance_q15 csky_cfft_sR_q15_len512;
   extern const csky_cfft_instance_q15 csky_cfft_sR_q15_len1024;
   extern const csky_cfft_instance_q15 csky_cfft_sR_q15_len2048;
   extern const csky_cfft_instance_q15 csky_cfft_sR_q15_len4096;

   extern csky_rfft_instance_q15 csky_rfft_sR_q15_len32;
   extern csky_rfft_instance_q15 csky_rfft_sR_q15_len64;
   extern csky_rfft_instance_q15 csky_rfft_sR_q15_len128;
   extern csky_rfft_instance_q15 csky_rfft_sR_q15_len256;
   extern csky_rfft_instance_q15 csky_rfft_sR_q15_len512;
   extern csky_rfft_instance_q15 csky_rfft_sR_q15_len1024;
   extern csky_rfft_instance_q15 csky_rfft_sR_q15_len2048;
   extern csky_rfft_instance_q15 csky_rfft_sR_q15_len4096;
   extern csky_rfft_instance_q15 csky_rfft_sR_q15_len8192;


   extern csky_rfft_instance_q15 csky_inv_rfft_sR_q15_len32;
   extern csky_rfft_instance_q15 csky_inv_rfft_sR_q15_len64;
   extern csky_rfft_instance_q15 csky_inv_rfft_sR_q15_len128;
   extern csky_rfft_instance_q15 csky_inv_rfft_sR_q15_len256;
   extern csky_rfft_instance_q15 csky_inv_rfft_sR_q15_len512;
   extern csky_rfft_instance_q15 csky_inv_rfft_sR_q15_len1024;
   extern csky_rfft_instance_q15 csky_inv_rfft_sR_q15_len2048;
   extern csky_rfft_instance_q15 csky_inv_rfft_sR_q15_len4096;
   extern csky_rfft_instance_q15 csky_inv_rfft_sR_q15_len8192;


   extern csky_rfft_instance_q31 csky_rfft_sR_q31_len32;
   extern csky_rfft_instance_q31 csky_rfft_sR_q31_len64;
   extern csky_rfft_instance_q31 csky_rfft_sR_q31_len128;
   extern csky_rfft_instance_q31 csky_rfft_sR_q31_len256;
   extern csky_rfft_instance_q31 csky_rfft_sR_q31_len512;
   extern csky_rfft_instance_q31 csky_rfft_sR_q31_len1024;
   extern csky_rfft_instance_q31 csky_rfft_sR_q31_len2048;
   extern csky_rfft_instance_q31 csky_rfft_sR_q31_len4096;
   extern csky_rfft_instance_q31 csky_rfft_sR_q31_len8192;

   extern csky_rfft_instance_q31 csky_inv_rfft_sR_q31_len32;
   extern csky_rfft_instance_q31 csky_inv_rfft_sR_q31_len64;
   extern csky_rfft_instance_q31 csky_inv_rfft_sR_q31_len128;
   extern csky_rfft_instance_q31 csky_inv_rfft_sR_q31_len256;
   extern csky_rfft_instance_q31 csky_inv_rfft_sR_q31_len512;
   extern csky_rfft_instance_q31 csky_inv_rfft_sR_q31_len1024;
   extern csky_rfft_instance_q31 csky_inv_rfft_sR_q31_len2048;
   extern csky_rfft_instance_q31 csky_inv_rfft_sR_q31_len4096;
   extern csky_rfft_instance_q31 csky_inv_rfft_sR_q31_len8192;


   extern csky_rfft_fast_instance_f32 csky_rfft_sR_f32_len32;
   extern csky_rfft_fast_instance_f32 csky_rfft_sR_f32_len64;
   extern csky_rfft_fast_instance_f32 csky_rfft_sR_f32_len128;
   extern csky_rfft_fast_instance_f32 csky_rfft_sR_f32_len256;
   extern csky_rfft_fast_instance_f32 csky_rfft_sR_f32_len512;
   extern csky_rfft_fast_instance_f32 csky_rfft_sR_f32_len1024;
   extern csky_rfft_fast_instance_f32 csky_rfft_sR_f32_len2048;
   extern csky_rfft_fast_instance_f32 csky_rfft_sR_f32_len4096;
   extern csky_rfft_fast_instance_f32 csky_rfft_sR_f32_len8192;

   extern csky_dct4_instance_q15 csky_dct4_sR_q15_len128;
   extern csky_dct4_instance_q15 csky_dct4_sR_q15_len512;
   extern csky_dct4_instance_q15 csky_dct4_sR_q15_len2048;
   extern csky_dct4_instance_q15 csky_dct4_sR_q15_len8192;

   extern csky_dct4_instance_q31 csky_dct4_sR_q31_len128;
   extern csky_dct4_instance_q31 csky_dct4_sR_q31_len512;
   extern csky_dct4_instance_q31 csky_dct4_sR_q31_len2048;
   extern csky_dct4_instance_q31 csky_dct4_sR_q31_len8192;

   extern csky_dct4_instance_f32 csky_dct4_sR_f32_len128;
   extern csky_dct4_instance_f32 csky_dct4_sR_f32_len512;
   extern csky_dct4_instance_f32 csky_dct4_sR_f32_len2048;
   extern csky_dct4_instance_f32 csky_dct4_sR_f32_len8192;
#endif
