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

#ifndef __FFT_H__
#define __FFT_H__

#include "av/tfft/fft_cls.h"

__BEGIN_DECLS__

/**
 * @brief  regist fft ops
 * @param  [in] ops
 * @return 0/-1
 */
int fftx_ops_register(const struct fftx_ops *ops);

/**
 * @brief  alloc a fft
 * @param  [in] size : N
 * @return NULL on error
 */
fftx_t* fftx_new(size_t size);

/**
 * @brief  fft forward
 * @param  [in] fft
 * @param  [in] in
 * @param  [in] out
 * @return 0/-1
 */
int fftx_forward(fftx_t *fft, const int16_t *in, int16_t *out);

/**
 * @brief  fft backward
 * @param  [in] fft
 * @param  [in] in
 * @param  [in] out
 * @return 0/-1
 */
int fftx_backward(fftx_t *fft, const int16_t *in, int16_t *out);

/**
 * @brief  free the fft
 * @param  [in] fft
 * @return 0/-1
 */
int fftx_free(fftx_t *fft);

__END_DECLS__

#endif /* __FFT_H__ */

