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

#ifndef __M4A_RW_H__
#define __M4A_RW_H__

#include "av/avutil/common.h"
#include "av/avutil/av_typedef.h"

__BEGIN_DECLS__

typedef enum {
    AOT_NULL,
    AOT_AAC_MAIN,              ///< Main
    AOT_AAC_LC,                ///< Low Complexity
    AOT_AAC_SSR,               ///< Scalable Sample Rate
    AOT_AAC_LTP,               ///< Long Term Prediction
    AOT_SBR,                   ///< Spectral Band Replication
    AOT_AAC_SCALABLE,          ///< Scalable
    AOT_TWINVQ,                ///< Twin Vector Quantizer
    AOT_CELP,                  ///< Code Excited Linear Prediction
    AOT_HVXC,                  ///< Harmonic Vector eXcitation Coding
    AOT_RESERVED1,             ///<
    AOT_RESERVED2,             ///<
    AOT_TTSI,                  ///< Text-To-Speech Interface
    AOT_MAINSYNTH,             ///< Main Synthesis
    AOT_WAVESYNTH,             ///< Wavetable Synthesis
    AOT_MIDI,                  ///< General MIDI
    AOT_SAFX,                  ///< Algorithmic Synthesis and Audio Effects
    AOT_ER_AAC_LC,             ///< Error Resilient Low Complexity
    AOT_RESERVED3,             ///<
    AOT_ER_AAC_LTP,            ///< Error Resilient Long Term Prediction
    AOT_ER_AAC_SCALABLE,       ///< Error Resilient Scalable
    AOT_ER_TWINVQ,             ///< Error Resilient Twin Vector Quantizer
    AOT_ER_BSAC,               ///< Error Resilient Bit-Sliced Arithmetic Coding
    AOT_ER_AAC_LD,             ///< Error Resilient Low Delay
    AOT_ER_CELP,               ///< Error Resilient Code Excited Linear Prediction
    AOT_ER_HVXC,               ///< Error Resilient Harmonic Vector eXcitation Coding
    AOT_ER_HILN,               ///< Error Resilient Harmonic and Individual Lines plus Noise
    AOT_ER_PARAM,              ///< Error Resilient Parametric
    AOT_SSC,                   ///< SinuSoidal Coding
    AOT_PS,                    ///< Parametric Stereo
    AOT_SURROUND,              ///< MPEG Surround
    AOT_ESCAPE,                ///< Escape Value
    AOT_L1,                    ///< Layer 1
    AOT_L2,                    ///< Layer 2
    AOT_L3,                    ///< Layer 3
    AOT_DST,                   ///< Direct Stream Transfer
    AOT_ALS,                   ///< Audio LosslesS
    AOT_SLS,                   ///< Scalable LosslesS
    AOT_SLS_NON_CORE,          ///< Scalable LosslesS (non core)
    AOT_ER_AAC_ELD,            ///< Error Resilient Enhanced Low Delay
    AOT_SMR_SIMPLE,            ///< Symbolic Music Representation Simple
    AOT_SMR_MAIN,              ///< Symbolic Music Representation Main
    AOT_USAC_NOSBR,            ///< Unified Speech and Audio Coding (no SBR)
    AOT_SAOC,                  ///< Spatial Audio Object Coding
    AOT_LD_SURROUND,           ///< Low Delay MPEG Surround
    AOT_USAC,                  ///< Unified Speech and Audio Coding
} m4a_aot_t;

typedef struct {
    uint8_t     object_type;
    uint8_t     sample_idx;
    uint8_t     ch_conf;
    uint8_t     channels;
    uint8_t     ps;
    uint8_t     sbr;
    uint8_t     ext_object_type;
    uint8_t     ext_sample_idx;
    uint8_t     ext_ch_conf;
    int         rate;
    int         ext_rate;
} m4a_cnf_t;

/**
* @brief  decode the Audio Specific Config
* @param  [in] m4ac
* @param  [in] asc : extradata, Audio Specific Config
* @param  [in] size
* @return 0/-1
*/
int m4a_decode_asc(m4a_cnf_t *m4ac, const uint8_t *asc, size_t size);

__END_DECLS__

#endif /* __M4A_RW_H__ */

