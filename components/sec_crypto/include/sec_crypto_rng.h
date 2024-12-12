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
 * @file     seccrypt_rng.h
 * @brief    Header File for RNG
 * @version  V1.0
 * @date     20. Jul 2020
 * @model    rng
 ******************************************************************************/
#ifndef _SC_RNG_H_
#define _SC_RNG_H_


#include <stdint.h>
#include <sec_crypto_errcode.h>


#ifdef __cplusplus
extern "C" {
#endif

/**
  \brief       Get data from the TRNG engine
  \param[out]  data  Pointer to buffer with data get from TRNG
  \param[in]   num   Number of data items,uinit in uint32
  \return      error code
*/
uint32_t sc_rng_get_multi_word(uint32_t *data, uint32_t num);

/**
  \brief       Get data from the TRNG engine
  \return      error code
*/
uint32_t sc_rng_get_single_word(uint32_t *data);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_TRNG_H_ */
