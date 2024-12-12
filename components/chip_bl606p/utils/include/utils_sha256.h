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




#ifndef _IOTX_COMMON_SHA256_H_
#define _IOTX_COMMON_SHA256_H_

#include <stdint.h>

#define SHA256_DIGEST_LENGTH            (32)
#define SHA256_BLOCK_LENGTH             (64)
#define SHA256_SHORT_BLOCK_LENGTH       (SHA256_BLOCK_LENGTH - 8)
#define SHA256_DIGEST_STRING_LENGTH     (SHA256_DIGEST_LENGTH * 2 + 1)

/**
 * \brief          SHA-256 context structure
 */
typedef struct {
    uint32_t total[2];          /*!< number of bytes processed  */
    uint32_t state[8];          /*!< intermediate digest state  */
    unsigned char buffer[64];   /*!< data block being processed */
    int is224;                  /*!< 0 => SHA-256, else SHA-224 */
} iot_sha256_context;

typedef union {
    char sptr[8];
    uint64_t lint;
} u_retLen;

/**
 * \brief          Initialize SHA-256 context
 *
 * \param ctx      SHA-256 context to be initialized
 */
void utils_sha256_init(iot_sha256_context *ctx);

/**
 * \brief          Clear SHA-256 context
 *
 * \param ctx      SHA-256 context to be cleared
 */
void utils_sha256_free(iot_sha256_context *ctx);

/**
 * \brief          Clone (the state of) a SHA-256 context
 *
 * \param dst      The destination context
 * \param src      The context to be cloned
 */
void utils_sha256_clone(iot_sha256_context *dst,
                        const iot_sha256_context *src);

/**
 * \brief          SHA-256 context setup
 *
 * \param ctx      context to be initialized
 */
void utils_sha256_starts(iot_sha256_context *ctx);

/**
 * \brief          SHA-256 process buffer
 *
 * \param ctx      SHA-256 context
 * \param input    buffer holding the  data
 * \param ilen     length of the input data
 */
void utils_sha256_update(iot_sha256_context *ctx, const unsigned char *input, uint32_t ilen);

/**
 * \brief          SHA-256 final digest
 *
 * \param ctx      SHA-256 context
 * \param output   SHA-256 checksum result
 */
void utils_sha256_finish(iot_sha256_context *ctx, uint8_t output[32]);

/* Internal use */
void utils_sha256_process(iot_sha256_context *ctx, const unsigned char data[64]);

/**
 * \brief          Output = SHA-256( input buffer )
 *
 * \param input    buffer holding the  data
 * \param ilen     length of the input data
 * \param output   SHA-256 checksum result
 */
void utils_sha256(const uint8_t *input, uint32_t ilen, uint8_t output[32]);


#endif
