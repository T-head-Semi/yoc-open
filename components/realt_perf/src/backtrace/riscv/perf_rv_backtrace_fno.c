/*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 */
#if CONFIG_PERF_BACKTRACE_USE_FP
#include <csi_core.h>
#include "perf_rv_backtrace.h"

ssize_t perf_rv_backtrace_fno(unsigned long *buf, size_t size, int (*print_func)(const char *fmt, ...))
{
	size_t use_buf_len = 0;
	unsigned long ss0;
	unsigned long mscratch;
	unsigned long fp, pc;
	struct stackframe *frame;
	unsigned int ins32;

	mscratch = __get_MSCRATCH();
	ss0 = *(unsigned long *)mscratch; // need store s0 when come irq first
	fp = ss0;
#if !CONFIG_SUPPORT_IRQ_NESTED
	pc = __get_MEPC();
#else
	unsigned long *ppc = (unsigned long *)mscratch;
	pc = *(++ppc);
#endif
	if (!rv_in_text_region(pc)) {
		if (print_func) {
			print_func("pc[0x%016lx] is not in txt region.\n", pc);
		}
		return -1;
	}
	buf[use_buf_len++] = pc;
	if (print_func) {
		print_func("Stack interval, fp: 0x%016lx, pc: 0x%016lx\n", fp, pc);
	}
	while (1) {
		if (use_buf_len >= size) {
			if (print_func) {
				print_func("use_buf_len: %ld, size: %ld\n", use_buf_len, size);
			}
			return use_buf_len;
		}
		if (fp <= BACKTRACE_LEN) break;
		frame = (struct stackframe *)(fp - BACKTRACE_LEN);
		if (frame->s_fp && !rv_valid_stack(frame->s_fp)) {
			if (print_func) {
				print_func("frame->s_fp[0x%016lx] is not in stack region. break\n", frame->s_fp);
			}
			break;
		}
		if (frame->s_ra < 5) break;
		pc = frame->s_ra - 4;
		ins32 = *(unsigned int *)pc;
		if ((ins32 & 0x3) != 0x3) {
			pc = frame->s_ra - 2;
		}
		if (!rv_in_text_region(pc)) {
			if (print_func) {
				print_func("pc[0x%016lx](frame->s_ra:0x%016lx,frame->s_fp:0x%016lx) is not in txt region. break\n", pc, frame->s_ra, frame->s_fp);
			}
			break;
		}
		fp = frame->s_fp;
		buf[use_buf_len++] = pc;

		if (print_func) {
			print_func("Stack interval, fp: 0x%016lx, pc: 0x%016lx\n", fp, pc);
		}
	}
	if (print_func) {
		print_func("use_buf_len: %ld\n", use_buf_len);
	}
	return use_buf_len;
}
#endif