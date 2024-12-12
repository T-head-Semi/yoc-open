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

/******************************************************************************
 * @file     softse_trng.c
 * @brief    trng
 * @version  V1.0
 * @date     21. May 2020
 * @model    sse
 ******************************************************************************/
#ifdef CONFIG_SEC_CRYPTO_RNG_SW
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sec_crypto_rng.h>
#include <sec_crypto_errcode.h>

#include "sec_crypto_common.h"

// Function documentation

static uint32_t g_random = 0x3C6EF35F;
/**
  \brief       Get data from the TRNG engine
  \param[out]  data  Pointer to buffer with data get from TRNG
  \param[in]   num   Number of data items,uinit in uint32
  \return      error code
*/
uint32_t sc_rng_get_multi_word(uint32_t *data, uint32_t num)
{
    SC_lOG("===%s, %d\n", __FUNCTION__, __LINE__);
    int i;
    for (i = 0; i < num; i++) {
        g_random = g_random * 0x41C64E6D + 0x3039;
        data[i]  = g_random;
    }

    return SC_OK;
}

/**
  \brief       Get data from the TRNG engine
  \return      error code
*/
uint32_t sc_rng_get_single_word(uint32_t *data)
{
    SC_lOG("===%s, %d\n", __FUNCTION__, __LINE__);
    g_random = g_random * 0x41C64E6D + 0x3039;
    *data    = g_random;

    return SC_OK;
}

#endif
