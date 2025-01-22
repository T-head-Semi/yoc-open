/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-23     WangShun     the first version
 */
#include <csi_core.h>
#include "perf.h"
#include "perf_backtrace.h"
#include "perf_rv_backtrace.h"

ssize_t perf_rv_backtrace(unsigned long *buf, size_t size, int (*print_func)(const char *fmt, ...))
{
#if CONFIG_PERF_BACKTRACE_USE_FP
	return perf_rv_backtrace_fno(buf, size, print_func);
#else
	return perf_rv_backtrace_fomit(buf, size, print_func);
#endif /* CONFIG_PERF_BACKTRACE_USE_FP */
}

bool rv_in_text_region(unsigned long addr)
{
	extern unsigned long __stext, __etext;

	return (addr >= (unsigned long)&__stext) && (addr < (unsigned long)&__etext);
}

#ifdef CONFIG_KERNEL_NONE
extern unsigned long g_base_mainstack;
bool rv_valid_stack(unsigned long addr)
{
	int cpuid = csi_get_cpu_id();
	if ((addr >= (unsigned long)&g_base_mainstack + cpuid * CONFIG_ARCH_MAINSTACK && addr <= (unsigned long)&g_base_mainstack + (cpuid + 1) * CONFIG_ARCH_MAINSTACK)) {
		return true;
	}
	return false;
}
#elif defined(CONFIG_KERNEL_FREERTOS)
#error "Not support kernel."
#elif defined(CONFIG_KERNEL_RTTHREAD)
#include <rtthread.h>
bool rv_valid_stack(unsigned long addr)
{
	rt_thread_t thread = rt_thread_self();
	if ((addr >= (unsigned long)thread->stack_addr && addr <= (unsigned long)thread->stack_addr + thread->stack_size)) {
		return true;
	}
	return false;
}
#else
#error "Not support kernel."
#endif
