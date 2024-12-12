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

#ifndef __CMCA_H__
#define __CMCA_H__

#include "av/mca/mca.h"

__BEGIN_DECLS__

/**
 * Configures IIR filter with 32-bit input/ouput and 32-bit coefficients.
 *
 * Note:
 *   # coeff is 32-bit (Q1.7.24), with size of 5.
 *   # Input/output are 32-bit (Q1.31.0).
 * @return -1/0
 */
int cmca_iir_fxp32_coeff32_config(const fxp32_t *coeff);

/**
 * IIR filter with 32-bit input/output.
 *
 * Note:
 *   # input is 32-bit (Q1.31.0), output also 32-bit but its precision is
 *     determined by configuration.
 *   # input_size must be greater than order, and size of output is
 *     (input_size - 2).
 *   # yn1 and yn2 are the 1st and 2nd samples from the last output.
 * @return -1/0
 */
int cmca_iir_fxp32(const fxp32_t *input, size_t input_size, fxp32_t yn1, fxp32_t yn2,
                   fxp32_t *output);

__END_DECLS__

#endif /* __CMCA_H__ */

