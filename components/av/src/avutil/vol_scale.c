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

#include <math.h>
#include "av/avutil/vol_scale.h"

#define TAG                   "volscale"

static int32_t _factor_scale[FACTOR_N];

/**
 * @brief  init factor of the vol scale, divided into FACTOR_N(256) equal parts. once only
 * @param  [in] mindb
 * @param  [in] maxdb
 * @return
 */
void vol_scale_init(int mindb, int maxdb)
{
    static int init;

    if (!init) {
        int i;
        double db;

        for (i = 0; i < FACTOR_N; i++) {
            db               = mindb + 1.0 * (maxdb - mindb) * i / FACTOR_N;
            _factor_scale[i] = pow(10.0, db / 20.0) * (1 << 14);
        }
        //FIXME:
        _factor_scale[0] = 0;
        init = 1;
    }
}

/**
 * @brief  vol scale
 * @param  [in] in
 * @param  [in] nb_samples
 * @param  [in] out
 * @param  [in] scale index : 0~255
 * @return 0/-1
 */
int vol_scale(const int16_t *in, size_t nb_samples, int16_t *out, uint8_t scale_index)
{
    int factor;

    factor = _factor_scale[scale_index];
    if (factor > (1 << 14)) {
        int64_t v;

        while (nb_samples--) {
            v      = (*in++ * factor) >> 14;
            v      = v < 0x7fff ? v : 0x7fff;
            v      = v > -0x7fff ? v : -0x7fff;
            *out++ = (int16_t)v;
        }
    } else {
        while (nb_samples--) {
            *out++ = (*in++ * factor) >> 14;
        }
    }

    return 0;
}

#if 0
int main(int argc, char *argv[])
{
    int index;
    int nb_samples = _test_bin_len / 2;

    if (argc < 2) {
        printf("param err\n");
        return -1;
    }

    index = atoi(argv[1]);
    vol_scale((const int16_t*)_test_bin, nb_samples, (int16_t*)_test_bin, index);

    return 0;
}
#endif


