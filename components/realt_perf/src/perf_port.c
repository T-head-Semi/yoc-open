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
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "perf.h"

__attribute__((weak)) cpu_bind_timer_t g_cpu_bind_timer[PERF_MAX_CPUS] = {
	{0, 0},
	{1, 1},
	{2, 2},
	{3, 3}
};

__attribute__((weak)) int perf_printf(const char *fmt, ...)
{
    int ret;
    va_list args;

    va_start(args, fmt);
    ret = vprintf(fmt, args);
    va_end(args);

    return ret;
}

__attribute__((weak)) void *perf_malloc(size_t size)
{
    return (malloc(size));
}

__attribute__((weak)) void *perf_realloc(void *ptr, size_t size)
{
    return (realloc(ptr, size));
}

__attribute__((weak)) void perf_free(void* ptr)
{
    if(ptr)
        free(ptr);
}

__attribute__((weak)) unsigned long *perf_record_alloc_data_buf(void)
{
    unsigned long *p = (unsigned long *)malloc(CONFIG_PROFILING_PERF_PER_CORE_BUFFER_SIZE);
    if (p == NULL) {
        perf_printf("perf data buf malloc failed.\n");
        return NULL;
    }
    return p;
}

__attribute__((weak)) void perf_record_free_data_buf(unsigned long *buf)
{
    if (buf)
        free(buf);
}