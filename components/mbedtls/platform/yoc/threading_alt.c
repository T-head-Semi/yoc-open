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

/* This file provides threading mutex implementation for AliOS Things. */

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#if defined(MBEDTLS_THREADING_ALT)
#include <aos/kernel.h>

#include "mbedtls/threading.h"

void threading_mutex_init( mbedtls_threading_mutex_t *mutex )
{
    if( mutex == NULL || mutex->is_valid )
        return;

    mutex->is_valid = ( aos_mutex_new( &mutex->mutex ) == 0 );
}

void threading_mutex_free( mbedtls_threading_mutex_t *mutex )
{
    if( mutex == NULL || !mutex->is_valid )
        return;

    aos_mutex_free( &mutex->mutex );
    mutex->is_valid = 0;
}

int threading_mutex_lock( mbedtls_threading_mutex_t *mutex )
{
    if( mutex == NULL || !mutex->is_valid )
        return( MBEDTLS_ERR_THREADING_BAD_INPUT_DATA );

    if( aos_mutex_lock( &mutex->mutex, AOS_WAIT_FOREVER ) != 0 )
        return( MBEDTLS_ERR_THREADING_MUTEX_ERROR );

    return( 0 );
}

int threading_mutex_unlock( mbedtls_threading_mutex_t *mutex )
{
    if( mutex == NULL || ! mutex->is_valid )
        return( MBEDTLS_ERR_THREADING_BAD_INPUT_DATA );

    if( aos_mutex_unlock( &mutex->mutex ) != 0 )
        return( MBEDTLS_ERR_THREADING_MUTEX_ERROR );

    return( 0 );
}
#endif /* MBEDTLS_THREADING_ALT */

