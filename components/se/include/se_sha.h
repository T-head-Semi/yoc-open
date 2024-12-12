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
 * @file     se_sha.h
 * @brief    Header File for SHA
 * @version  V1.0
 * @date     22. May 2023
 * @model    sha
 ******************************************************************************/
#ifndef _SE_SHA_H_
#define _SE_SHA_H_


#include <stdint.h>
#include "se_device.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    SE_SHA_MODE_1 = 1U,  ///< SHA_1 mode
    SE_SHA_MODE_256,     ///< SHA_256 mode
    SE_SHA_MODE_224,     ///< SHA_224 mode
    SE_SHA_MODE_512,     ///< SHA_512 mode
    SE_SHA_MODE_384,     ///< SHA_384 mode
    SE_SHA_MODE_512_256, ///< SHA_512_256 mode
    SE_SHA_MODE_512_224  ///< SHA_512_224 mode
} se_sha_mode_t;

typedef struct{
    aos_mutex_t mutex;
    void      *ctx;
} se_sha_t;

/**
  \brief       Initialize SHA Interface. Initializes the resources needed for the SHA interface
  \param[in]   se_sha  operate handle.
  \return      0 success, Non-zero failure
*/
int se_sha_init(se_sha_t *se_sha);

/**
  \brief       De-initialize SHA Interface. stops operation and releases the software resources used by the interface
  \param[in]   se_sha  sha handle to operate.
  \return      none
*/
void se_sha_uninit(se_sha_t *se_sha);

/**
  \brief       start the engine
  \param[in]   se_sha  sha handle to operate.
  \param[in]   mode    sha mode \ref sc_sha_mode_t
  \return      0 success, Non-zero failure
*/
int se_sha_start(se_sha_t *se_sha, se_sha_mode_t mode);

/**
  \brief       update the engine
  \param[in]   se_sha  sha handle to operate.
  \param[in]   input   Pointer to the Source data
  \param[in]   size    the data size
  \return      0 success, Non-zero failure
*/
int se_sha_update(se_sha_t *se_sha, const void *input, uint32_t size);

/**
  \brief       finish the engine
  \param[in]   se_sha   sha handle to operate.
  \param[out]  output   Pointer to the result data
  \param[out]  out_size Pointer to the result data size(bytes)
  \return      0 success, Non-zero failure
*/
int se_sha_finish(se_sha_t *se_sha, void *output, uint32_t *out_size);

#ifdef __cplusplus
}
#endif

#endif /* _DRV_SHA_H_ */
