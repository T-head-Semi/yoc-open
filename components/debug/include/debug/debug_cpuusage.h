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

#ifndef DEBUG_CPUUSAGE_H
#define DEBUG_CPUUSAGE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_KERNEL_RHINO

#define CPU_USAGE_MAX_TASKNAME_LEN 32

struct cpuusage_data {
    char taskname[CPU_USAGE_MAX_TASKNAME_LEN];
    float *cpuusage;
};

void     debug_task_cpu_usage_stats(void);
uint32_t debug_task_cpu_usage_get(ktask_t *task);
uint32_t debug_total_cpu_usage_get(uint32_t cpuid);
void     debug_total_cpu_usage_show(struct cpuusage_data *cpuusage_record, int32_t record_len, int32_t index);
kstat_t  debug_task_cpu_usage_init(void);
void     debug_cpuusage_cmds_register(void);

#endif

#ifdef __cplusplus
}
#endif

#endif /* DEBUG_CPUUSAGE_H */
