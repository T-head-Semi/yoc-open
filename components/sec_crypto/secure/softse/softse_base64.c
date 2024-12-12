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

#ifdef CONFIG_SEC_BASE64_SW
#include <crypto_base64.h>
#include "sec_mcu.h"
#include "sec_crypto_common.h"

// Function documentation

/**
  \brief       The interface of base64 encoder.
  \param[in]   data    A pointer to the buffer that is needed to be encoded
  \param[in]   size    The data length that is needed to be encoded
  \param[out]   buf    A pointer to the output buffer
  \param[inout]   blen  The output buffer size input, it will be modified after encoding
  \return      error code \ref uint32_t
*/
uint32_t sc_base64_enc(const void *data, size_t size, char *buf, size_t *blen)
{
    if (_base64_enc(data, size, buf, blen))
        return SC_OK;
    else
        return SC_FAIL;
}

/**
  \brief       The interface of base64 decoder.
  \param[in]   data    A pointer to the buffer that is needed to be decoded
  \param[in]   size    The data length that is needed to be decoded
  \param[out]   buf    A pointer to the output buffer
  \param[inout]   blen  The output buffer size input, it will be modified after decoding
  \return      error code \ref uint32_t
*/
uint32_t sc_base64_dec(const char *data, size_t size, void *buf, size_t *blen)
{
    if (_base64_dec(data, size, buf, blen))
        return SC_OK;
    else
        return SC_FAIL;
}

/**
  \brief       The interface of getting the size after base64 encoding.
  \param[in]   size    The data length that is needed to be encoded
  \return      The size after encoding
*/
size_t sc_base64_enc_len(size_t size)
{
    return _base64_enc_len(size);
}

#endif /* CONFIG_SEC_BASE64_SW */