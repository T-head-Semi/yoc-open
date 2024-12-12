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

/* This file provides implementation of common (libc) functions that is defined
 * in platform abstraction layer for AliOS Things.
 */

#if !defined(MBEDTLS_CONFIG_FILE)
#include "mbedtls/config.h"
#else
#include MBEDTLS_CONFIG_FILE
#endif

#if defined(MBEDTLS_PLATFORM_C)
#include <stdlib.h>
#include <string.h>
#include <aos/kernel.h>

#if defined(MBEDTLS_PLATFORM_MEMORY)
#if defined(XTENSA_MALLOC_IRAM)
extern void *iram_heap_malloc( size_t xWantedSize );
extern void  iram_heap_free( void *pv );
extern int   iram_heap_check_addr( void *addr );

void * aos_mbedtls_calloc( size_t n, size_t size )
{
    void *buf = NULL;

    if( ( n == 0 ) || ( size == 0 ) )
        return( NULL );

    buf = iram_heap_malloc( n * size );
    if( buf == NULL )
        buf = malloc( n * size );

    if( buf == NULL )
        return( NULL );
    else
        memset( buf, 0, n * size );

    return( buf );
}

void aos_mbedtls_free( void *ptr )
{
    if( ptr == NULL )
        return;

    if( iram_heap_check_addr( ptr ) == 1 )
        iram_heap_free( ptr );
    else
        free( ptr );
}

#else /*XTENSA_MALLOC_IRAM*/

void * aos_mbedtls_calloc( size_t n, size_t size )
{
    void *buf = NULL;

    buf = aos_malloc(n * size);
    if( buf == NULL )
        return( NULL );
    else
        memset(buf, 0, n * size);

    return( buf );
}

void aos_mbedtls_free( void *ptr )
{
    if( ptr == NULL )
        return;

    aos_free( ptr );
}
#endif /*XTENSA_MALLOC_IRAM*/
#endif /*MBEDTLS_PLATFORM_MEMORY*/
#endif /*MBEDTLS_PLATFORM_C*/
