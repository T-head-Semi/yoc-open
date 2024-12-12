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


#ifndef CONFIG_SEC_CRYPTO_RNG_SW
#ifdef CONFIG_CSI_V1

#include "sec_mcu.h"
#include "drv/trng.h"

/**
  \brief       Get data from the TRNG engine
*/
uint32_t sc_rng_get_multi_word(uint32_t *data, uint32_t num)
{
    trng_handle_t trng;

    trng = csi_trng_initialize(0, NULL);

    return csi_trng_get_data(trng, (uint8_t *)data, num * sizeof(uint32_t));
}

/**
  \brief       Get data from the TRNG engine
*/
uint32_t sc_rng_get_single_word(uint32_t *data)
{
    trng_handle_t trng;

    trng = csi_trng_initialize(0, NULL);

    return csi_trng_get_data(trng, (uint8_t *)data, sizeof(uint32_t));
}

#endif
#endif
