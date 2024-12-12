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

#ifndef __FFT_ICORE_H__
#define __FFT_ICORE_H__

#include <aos/types.h>
#include <aos/aos.h>

__BEGIN_DECLS__

typedef struct fft_icore fft_icore_t;

/**
 * @brief  init the icore inter-core fft
 * @return 0/-1
 */
int fft_icore_init();

/**
 * @brief  alloc a inter-core fft
 * @param  [in] size : N of the fft
 * @return NULL on error
 */
fft_icore_t* fft_icore_new(size_t size);

/**
 * @brief  fft forward
 * @param  [in] hdl
 * @param  [in] in
 * @param  [in] out
 * @return 0/-1
 */
int fft_icore_forward(fft_icore_t *hdl, const int16_t *in, int16_t *out);

/**
 * @brief  fft backward
 * @param  [in] hdl
 * @param  [in] in
 * @param  [in] out
 * @return 0/-1
 */
int fft_icore_backward(fft_icore_t *hdl, const int16_t *in, int16_t *out);

/**
 * @brief  free the inter-core fft
 * @param  [in] hdl
 * @return 0/-1
 */
int fft_icore_free(fft_icore_t *hdl);

__END_DECLS__

#endif /* __FFT_ICORE_H__ */

