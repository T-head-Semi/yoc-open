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

#include "av/tfft/fft.h"
#include "av/tfft/fft_all.h"

/**
 * @brief  regist fft for speex
 * @return 0/-1
 */
int fftx_register_speex()
{
    extern struct fftx_ops fftx_ops_speex;
    return fftx_ops_register(&fftx_ops_speex);
}

/**
 * @brief  regist fft for ipc
 * @return 0/-1
 */
int fftx_register_ipc()
{
    extern struct fftx_ops fftx_ops_ipc;
    return fftx_ops_register(&fftx_ops_ipc);
}


