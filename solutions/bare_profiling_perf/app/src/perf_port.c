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
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <csi_core.h>
#include <perf.h>
#include "app_init.h"

cpu_bind_timer_t g_cpu_bind_timer[PERF_MAX_CPUS] = {
	{0, 0},
	{1, 1},
	{2, 2},
	{3, 3}
};

spinlock_t g_print_spinlock;
spinlock_t g_alloc_bufdata_spinlock;

void perf_spinlock_init(void)
{
	spin_lock_init(&g_print_spinlock);
	spin_lock_init(&g_alloc_bufdata_spinlock);
}

int perf_printf(const char *fmt, ...)
{
    int ret;
    va_list args;

	unsigned long level = csi_irq_save();
	spin_lock(&g_print_spinlock);
	printf("cpuid[%d] ", csi_get_cpu_id());
    va_start(args, fmt);
    ret = vprintf(fmt, args);
    va_end(args);
	spin_unlock(&g_print_spinlock);
	csi_irq_restore(level);

    return ret;
}

void *perf_malloc(size_t size)
{
    spin_lock(&g_alloc_bufdata_spinlock);
    unsigned long *p = (unsigned long *)malloc(size);
    if (p == NULL) {
        perf_printf("perf data buf malloc failed. cpu:%d\n", csi_get_cpu_id());
        spin_unlock(&g_alloc_bufdata_spinlock);
        return NULL;
    }
    spin_unlock(&g_alloc_bufdata_spinlock);
    return p;
}

void *perf_realloc(void *ptr, size_t size)
{
    spin_lock(&g_alloc_bufdata_spinlock);
    unsigned long *p = (unsigned long *)realloc(ptr, size);
    if (p == NULL) {
        perf_printf("perf data buf malloc failed. cpu:%d\n", csi_get_cpu_id());
        spin_unlock(&g_alloc_bufdata_spinlock);
        return NULL;
    }
    spin_unlock(&g_alloc_bufdata_spinlock);
    return p;
}

void perf_free(void* ptr)
{
    if (ptr) {
        spin_lock(&g_alloc_bufdata_spinlock);
        free(ptr);
        spin_unlock(&g_alloc_bufdata_spinlock);
    }
}

unsigned long *perf_record_alloc_data_buf(void)
{
	spin_lock(&g_alloc_bufdata_spinlock);
	unsigned long *p = (unsigned long *)malloc(CONFIG_PROFILING_PERF_PER_CORE_BUFFER_SIZE);
	if (p == NULL) {
		perf_printf("perf data buf malloc failed. cpu:%d\n", csi_get_cpu_id());
		spin_unlock(&g_alloc_bufdata_spinlock);
		return NULL;
	}
	spin_unlock(&g_alloc_bufdata_spinlock);
	return p;
}

void perf_record_free_data_buf(unsigned long *buf)
{
	if (buf) {
		spin_lock(&g_alloc_bufdata_spinlock);
		perf_printf("will free databuf[0x%lx]\n", (unsigned long)buf);
		free(buf);
		perf_printf("free databuf[0x%lx] ok\n", (unsigned long)buf);
		spin_unlock(&g_alloc_bufdata_spinlock);
	}
}