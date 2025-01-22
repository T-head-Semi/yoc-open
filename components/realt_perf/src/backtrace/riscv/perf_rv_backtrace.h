/*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 */
#ifndef __PERF_RV_BACKTRANCE_H__
#define __PERF_RV_BACKTRANCE_H__

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#if __riscv_xlen == 64
#define BACKTRACE_LEN 16
#elif __riscv_xlen == 32
#define BACKTRACE_LEN 8
#else
#error "__riscv_xlen not support."
#endif

struct stackframe
{
	unsigned long s_fp;
	unsigned long s_ra;
};

ssize_t perf_rv_backtrace(unsigned long *buf, size_t size, int (*print_func)(const char *fmt, ...));
ssize_t perf_rv_backtrace_fno(unsigned long *buf, size_t size, int (*print_func)(const char *fmt, ...));
ssize_t perf_rv_backtrace_fomit(unsigned long *buf, size_t size, int (*print_func)(const char *fmt, ...));

bool rv_valid_stack(unsigned long addr);
bool rv_in_text_region(unsigned long addr);

#ifdef __cplusplus
}
#endif

#endif /* __RV_BACKTRANCE_H__ */
