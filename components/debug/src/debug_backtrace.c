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
#include "k_api.h"

/* follow functions should defined by arch\...\backtrace.c */
extern int backtrace_now(int (*print_func)(const char *fmt, ...));
extern int backtrace_task(void *task, int (*print_func)(const char *fmt, ...));

void debug_backtrace_now(int32_t (*print_func)(const char *fmt, ...))
{
    backtrace_now(print_func);
}

void debug_backtrace_task(char *taskname, int32_t (*print_func)(const char *fmt, ...))
{
#if (RHINO_CONFIG_KOBJ_LIST > 0)
    klist_t *listnode;
    ktask_t *task;

    for (listnode = g_kobj_list.task_head.next;
         listnode != &g_kobj_list.task_head; listnode = listnode->next) {
        task = krhino_list_entry(listnode, ktask_t, task_stats_item);
        if (taskname) {
            if (0 == strcmp(taskname, "all")) {
                print_func("task name \"%s\" \r\n",
                       ((ktask_t *)task)->task_name ? ((ktask_t *)task)->task_name : "anonym");
                backtrace_task(task, print_func);
            } else {
                if (0 == strcmp(taskname, task->task_name)) {
                    backtrace_task(task, print_func);
                }
            }
        }
    }
#endif
}

void backtrace_handle(char *PC, int *SP, char *LR, int (*print_func)(const char *fmt, ...));
void debug_panic_backtrace(char *PC, int *SP, char *LR,
                           int (*print_func)(const char *fmt, ...))
{
    backtrace_handle(PC, SP, LR, print_func);
}

