/*
 * Copyright (c) 2022, Commonwealth Scientific and Industrial Research
 * Organisation (CSIRO) ABN 41 687 119 230.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "semihost2/semihost.h"

#if 0
#ifndef __aligned
#define __aligned(x)          __attribute__((__aligned__(x)))
#endif

/*
 * QEMU requires that the semihosting trap instruction sequence, consisting of
 * three uncompressed instructions, lie in the same page, and refuses to
 * interpret the trap sequence if these instructions are placed across two
 * different pages.
 *
 * The `semihost_exec` function, which occupies 12 bytes, is aligned at a
 * 16-byte boundary to ensure that the three trap sequence instructions are
 * never placed across two different pages.
 */
/* FIXME: the ebreak instuction seq is not support on XT DebugServer */
long __aligned(16) semihost_exec(enum semihost_instr instr, void *args)
{
	register unsigned long a0 __asm__ ("a0") = instr;
	register void *a1 __asm__ ("a1") = args;
	register long ret __asm__ ("a0");

	__asm__ volatile (
		".option push\n\t"
		".option norvc\n\t"
		"slli zero, zero, 0x1f\n\t"
		"ebreak\n\t"
		"srai zero, zero, 0x7\n\t"
		".option pop"
		: "=r" (ret) : "r" (a0), "r" (a1) : "memory");

	return ret;
}
#else
long semihost_exec(enum semihost_instr instr, void *args)
{
  register long a0 asm ("a0") = instr;
  register long a1 asm ("a1") = (long) args;

  /* RISC-V semihosting trap sequence.  Must be uncompressed and must not
     cross page boundary.  */
  asm volatile (
    ".balign 16             \n"
    ".option push           \n"
    ".option norvc          \n"
    "slli zero, zero, 0x1f  \n"
    "ebreak                 \n"
    "srai zero, zero, 0x7   \n"
    ".option pop            \n"
      : "+r"(a0) : "r"(a1) : "memory");

  return a0;
}
#endif

