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
 * @file     seccrypt_aes.h
 * @brief    Header File for AES
 * @version  V1.0
 * @date     20. Jul 2020
 * @model    aes
 ******************************************************************************/
#ifndef _SC_BASE64_H_
#define _SC_BASE64_H_

#ifdef __cplusplus
extern "C" {
#endif

// Function documentation
/**
  \brief       The interface of base64 encoder.
  \param[in]   data    A pointer to the buffer that is needed to be encoded
  \param[in]   size    The data length that is needed to be encoded
  \param[out]   buf    A pointer to the output buffer
  \param[inout]   blen  The output buffer size input, it will be modified after encoding
  \return      error code \ref uint32_t
*/
uint32_t sc_base64_enc(const void *data, size_t size, char *buf, size_t *blen);

/**
  \brief       The interface of base64 decoder.
  \param[in]   data    A pointer to the buffer that is needed to be decoded
  \param[in]   size    The data length that is needed to be decoded
  \param[out]   buf    A pointer to the output buffer
  \param[inout]   blen  The output buffer size input, it will be modified after decoding
  \return      error code \ref uint32_t
*/
uint32_t sc_base64_dec(const char *data, size_t size, void *buf, size_t *blen);

/**
  \brief       The interface of getting the size after base64 encoding.
  \param[in]   size    The data length that is needed to be encoded
  \return      The size after encoding
*/
size_t sc_base64_enc_len(size_t size);

#ifdef __cplusplus
}
#endif
#endif /* _SC_BASE64_H_ */
