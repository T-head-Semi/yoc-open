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

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include "k_api.h"
#include "aos/debug.h"

/* part of ktask_t */
typedef struct
{
    void *task_stack;
} ktask_t_shadow;

//#define OS_BACKTRACE_DEBUG

extern char *__etext;
extern char *__stext;

#define BT_CHK_PC_AVAIL(pc)   ((uintptr_t)(pc) < (uintptr_t)(&__etext) \
                              && (uintptr_t)(pc) > (uintptr_t)(&__stext))

#define BT_PC2ADDR(pc)        ((char *)(((uintptr_t)(pc))))

#define BT_FUNC_LIMIT   0x2000
#define BT_LVL_LIMIT    64

extern void krhino_task_deathbed(void);
extern ktask_t_shadow *debug_task_find(char *name);
extern int debug_task_is_running(ktask_t_shadow *task);
extern void *debug_task_stack_bottom(ktask_t_shadow *task);
extern char *k_int2str(int num, char *str);
extern void _interrupt_return_address(void);

void backtrace_handle(char *PC, int *SP, char *LR, int (*print_func)(const char *fmt, ...));

/* get framesize from c ins */
static int riscv_backtrace_framesize_get(unsigned short inst)
{
    return -1;
}

/* get ra position in the stach */
static int riscv_backtrace_ra_offset_get(unsigned short inst)
{
    return -1;
}

/* get the offset between the jump instruction and the return address */
static int backtraceFindLROffset(char *LR, int (*print_func)(const char *fmt, ...))
{
    return 0;
}

/* find current function caller, update PC and SP
   returns: 0  success
            1  success and find buttom
            -1 fail */
static int riscv_backtraceFromStack(long **pSP, char **pPC,
                                  int (*print_func)(const char *fmt, ...))
{
    return -1;
}

static int backtraceFromStack(long **pSP, char **pPC,
                              int (*print_func)(const char *fmt, ...))
{
    return -1;
}

/* printf call stack
   return levels of call stack */
int backtrace_now(int (*print_func)(const char *fmt, ...))
{
    return -1;
}

/* printf call stack for task
   return levels of call stack */
void backtrace_task(void *task, int (*print_func)(const char *fmt, ...))
{

}

/* backtrace start with PC and SP, find LR from stack memory
   return levels of call stack */
int backtrace_caller(char *PC, int *SP,
                     int (*print_func)(const char *fmt, ...))
{
    return 0;
}

/* backtrace start with PC SP and LR
   return levels of call stack */
int backtrace_callee(char *PC, int *SP, char *LR,
                     int (*print_func)(const char *fmt, ...))
{
    return 0;
}


/**
 Get call stack, return levels of call stack
 trace[] output buffer
 size    buffer size
 offset  which lvl start
 */
int backtrace_now_get(void *trace[], int size, int offset)
{
    return -1;
}

void backtrace_handle(char *PC, int *SP, char *LR,
                      int (*print_func)(const char *fmt, ...))
{
    return;
}

