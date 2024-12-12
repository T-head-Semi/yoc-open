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

#ifndef DEBUG_PANIC_H
#define DEBUG_PANIC_H

#ifdef __cplusplus
extern "C" {
#endif

#define DEBUG_PANIC_STEP_MAX 32
#define OS_PANIC_BY_NMI      0x31415926
#define OS_PANIC_NOT_REBOOT  0x21314916

/* how many steps has finished when crash */
extern volatile uint32_t g_crash_steps;
/* crash status */
extern volatile uint32_t g_crash_by_NMI;
extern volatile uint32_t g_crash_not_reboot;

/* fault/exception entry
 * notice: this function maybe reentried by double exception
 */
void panicHandler(void *context);
void panicNmiFlagSet();
int  panicNmiFlagCheck();
void debug_set_panic_cli_enable(int enable);
void debug_init(void);
void debug_cpu_stop(void);
uint32_t debug_cpu_in_crash(void);
void fiqafterpanicHandler(void *context);
void debug_fatal_error(int err, char *file, int line);

#ifdef __cplusplus
}
#endif

#endif /* DEBUG_PANIC_H */
