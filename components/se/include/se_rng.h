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
 * @file     se_rng.h
 * @brief    Header File for RNG
 * @version  V1.0
 * @date     22. May 2023
 * @model    rng
 ******************************************************************************/
#ifndef _SE_RNG_H_
#define _SE_RNG_H_


#include <stdint.h>
#include "se_device.h"


#ifdef __cplusplus
extern "C" {
#endif

/**
  \brief       Get data from the TRNG engine
  \param[out]  data  Pointer to buffer with data get from TRNG
  \param[in]   blen  Byte length of data items,uinit in uint32
  \return      error code
*/
int se_rng_get_bytes(uint8_t *data, uint32_t blen);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_TRNG_H_ */
