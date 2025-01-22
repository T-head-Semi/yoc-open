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
#ifndef __PERF_H__
#define __PERF_H__

#include <stdint.h>
#include <stdlib.h>
#include <perf_events.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CONFIG_PROFILING_PERF_PER_CORE_BUFFER_SIZE
#define CONFIG_PROFILING_PERF_PER_CORE_BUFFER_SIZE 8192U
#endif

#ifndef CONFIG_NR_CPUS
#define CONFIG_NR_CPUS 1
#endif

typedef struct {
#define PERF_MAX_CPUS 4
    uint16_t cpu_id;
    uint16_t timer_idx;
} cpu_bind_timer_t;

typedef enum {
    PERF_ERROR = 0,
    PERF_OK = 1,
} perf_err_t;

typedef void *perf_thread_id;

// arguments of perf_stat_start()
typedef struct perf_stat_args_st {
    uint16_t* events;
    uint8_t *cpu_ids;
    perf_thread_id* tids;
    uint32_t nr_threads;
    uint16_t nr_events;
    uint8_t nr_cpus;
    uint8_t pmu_schedule;
} perf_stat_args_t;

/**
 * set timers for perf record, timer0 for core0, timer1 for core1... as default
 * user can implement by themselves
 * weak
 */
extern cpu_bind_timer_t g_cpu_bind_timer[PERF_MAX_CPUS];

/**
 * start perf record with call-graph recording
 *
 * @param[in]  duration_ms    the expected record time, milliseconds
 * @param[in]  frequency      the record frequency
 *
 * @return  0: success. otherwise failed
 */
int perf_record_start(uint32_t duration_ms, uint32_t frequency);

/**
 * stop perf record by manual
 *
 * @return  0: success. otherwise failed
 */
int perf_record_stop(void);

/**
 * dump record data, user can implement by themselves
 * weak
 * 
 * @return  0: success. otherwise failed
 */
int perf_record_dump(void);

/**
 * printf for perf perf component, user can implement by themselves
 * weak
 *
 * @param[in]  fmt    the format string
 *
 * @return  0: success. otherwise failed
 */
int perf_printf(const char *fmt, ...);

/**
 * malloc for perf perf component, user can implement by themselves
 * weak
 *
 * @param[in]  size    size to malloc
 *
 * @return  if success, return the allocated address, if failed, return 0
 */
void *perf_malloc(size_t size);

/**
 * malloc for perf component, user can implement by themselves
 * weak
 *
 * @param[in]  ptr     pointer to realloc
 * @param[in]  size    size to malloc
 *
 * @return  if success, return the allocated address, if failed, return 0
 */
void *perf_realloc(void *ptr, size_t size);

/**
 * 
 * free for perf component, user can implement by themself
 *
 * @param[in]  ptr     pointer to free
 *
 * @return  if success, return the allocated address, if failed, return 0
 */
void perf_free(void* ptr);

/**
 * alloc the mem addr for record data, user can implement by themselves
 * weak
 * 
 * @return  perf data buf address. null when failed
 */
unsigned long *perf_record_alloc_data_buf(void);

/**
 * free the perf data mem address, user can implement by themselves
 * weak
 * 
 * @param[in]  buf    the perf data buf address
 * 
 */
void perf_record_free_data_buf(unsigned long *buf);

/**
 * initialize perf-stat module, this function should be execute at the init of the system.
 * in multi-core cases, this functions should be execute once.
 */
void perf_stat_init(void);

/**
 * unregist perf-stat module, this function should be execute at system shutdown.
 * in multi-core cases, this functions should be execute once.
 */
void perf_stat_deinit(void);

/**
 * specify events to record and enable PMU counters.
 * cycles and instruction-retired will be recorded by default.
 * in multi-core cases, this function should run on every cpu
 * @param[in]   hpm_events     list of hpm counter events
 * @param[in]   n_hpm_events   lengt of hpm_events
 *
*/
void perf_stat_start(perf_stat_args_t* args);

/**
 * stop PMU counters and copy data from PMU counters to memroy
 * in multi-core cases, this function should run on every cpu after perf_stat_start()
*/
void perf_stat_stop(void);

/**
 *  get event id from its name.
 *  @param[in]  ev_name    name of the event
 */
uint16_t get_event_id(char* ev_name);

/**
 *  list all events
 */
void perf_list_events(void);

#ifdef __cplusplus
}
#endif
#endif
