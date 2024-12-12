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

#ifndef __FFT_CLS_H__
#define __FFT_CLS_H__

#include "av/avutil/common.h"

__BEGIN_DECLS__

typedef struct fftx           fftx_t;
typedef struct fftx_ops       fftx_ops_t;

struct fftx {
    size_t                    size;      // N

    void                      *priv;
    const struct fftx_ops     *ops;
    aos_mutex_t               lock;
};

struct fftx_ops {
    const char                *name;

    int      (*init)          (fftx_t *fft, size_t size);
    int      (*forward)       (fftx_t *fft, const int16_t *in, int16_t *out);
    int      (*backward)      (fftx_t *fft, const int16_t *in, int16_t *out);
    int      (*uninit)        (fftx_t *fft);
};

__END_DECLS__

#endif /* __FFT_CLS_H__ */

