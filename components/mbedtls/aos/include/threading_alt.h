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

#ifndef MBEDTLS_THREADING_ALT_H
#define MBEDTLS_THREADING_ALT_H

#include <stdlib.h>
#include <aos/kernel.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
    aos_mutex_t mutex;
    char is_valid;
} mbedtls_threading_mutex_t;

void threading_mutex_init( mbedtls_threading_mutex_t *mutex );
void threading_mutex_free( mbedtls_threading_mutex_t *mutex );
int threading_mutex_lock( mbedtls_threading_mutex_t *mutex );
int threading_mutex_unlock( mbedtls_threading_mutex_t *mutex );

#ifdef __cplusplus
}
#endif

#endif /* MBEDTLS_THREADING_ALT_H */
