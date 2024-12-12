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
 * @file     se_rng.c
 * @brief    rng
 * @version  V1.0
 * @date     26. May 2023
 * @model    sse
 ******************************************************************************/
#ifndef CONFIG_SEC_CRYPTO_RNG_SW
#include <stdint.h>
#include <sec_crypto_rng.h>
#include <sec_crypto_errcode.h>
#include <se_rng.h>

/**
  \brief       Get data from the TRNG engine
  \param[out]  data  Pointer to buffer with data get from TRNG
  \param[in]   num   Number of data items,uinit in uint32
  \return      error code
*/
uint32_t sc_rng_get_multi_word(uint32_t *data, uint32_t num)
{
	int ret;

	ret = se_rng_get_bytes((uint8_t *)data, num * 4);
	if (!ret)
		return SC_OK;
	else
		return SC_RNG_FAILED;
}

/**
  \brief       Get data from the TRNG engine
  \return      error code
*/
uint32_t sc_rng_get_single_word(uint32_t *data)
{
	int ret;

	ret = se_rng_get_bytes((uint8_t *)data, 4);
	if (!ret)
		return SC_OK;
	else
		return SC_RNG_FAILED;
}
#endif
