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


#ifdef CONFIG_KERNEL_RHINO
extern void non_tspend_cpu_task_switch(void);
extern void non_tspend_cpu_intrpt_switch(void);
extern void non_tspend_cpu_first_task_start(void);

#ifndef CONFIG_SUPPORT_TSPEND
void cpu_task_switch(void)
{
    non_tspend_cpu_task_switch();
}

void cpu_intrpt_switch(void)
{
    non_tspend_cpu_intrpt_switch();
}

void cpu_first_task_start(void)
{
    non_tspend_cpu_first_task_start();
}
#endif /* CONFIG_SUPPORT_TSPEND */

#endif /* CONFIG_KERNEL_RHINO */
