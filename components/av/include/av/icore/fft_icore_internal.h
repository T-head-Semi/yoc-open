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

#ifndef __FFT_ICORE_INTERNAL_H__
#define __FFT_ICORE_INTERNAL_H__

#include "av/icore/icore_msg.h"
#include "av/tfft/fft_cls.h"

__BEGIN_DECLS__

#ifdef CONFIG_CHIP_PANGU
#define FFT_ICORE_AP_IDX          (0)
#define FFT_ICORE_CP_IDX          (1)
#else
#define FFT_ICORE_AP_IDX          (1)
#define FFT_ICORE_CP_IDX          (2)
#endif

#define IPC_CMD_FFT_ICORE         (60)
#define FFT_ICORE_IPC_SERIVCE_ID  (0x15)

enum {
    ICORE_CMD_FFT_INVALID,
    ICORE_CMD_FFT_NEW,
    ICORE_CMD_FFT_FORWARD,
    ICORE_CMD_FFT_BACKWARD,
    ICORE_CMD_FFT_FREE,
};

typedef struct {
    size_t            size;      // N
    void              *fft;      // resp: fftx_t
} fft_icore_new_t;

typedef struct {
    void              *fft;
    int16_t           *in;
    int16_t           *out;
} fft_icore_forward_t;

typedef struct {
    void              *fft;
    int16_t           *in;
    int16_t           *out;
} fft_icore_backward_t;

typedef struct {
    void      *fft;
} fft_icore_free_t;

__END_DECLS__

#endif /* __FFT_ICORE_INTERNAL_H__ */

