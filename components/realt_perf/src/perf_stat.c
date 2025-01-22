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

#include <stdint.h>
#include <perf.h>
#include <perf_events.h>
#include <csi_core.h>
#include <drv/timer.h>
#include <drv/tick.h>
#include <memory.h>
#include <stdio.h>
#include <soc.h>
#include <stdarg.h>
#include <math.h>
#include <perf_ipc.h>

// numbers of events to schedule each time
#ifndef CONFIG_PERF_STAT_SCHEDULER_NR_EVENTS
#define CONFIG_PERF_STAT_SCHEDULER_NR_EVENTS       16
#endif

// period of schedule
#ifndef CONFIG_PMU_SCHED_PERIOD_US
#define CONFIG_PMU_SCHED_PERIOD_US  4999U
#endif

// state machine
#define PERF_STAT_STOP               0
#define PERF_STAT_CORE0_INIT         1
#define PERF_STAT_SECONDARY_STOP     2

// schedule status of events
#define EV_SCHED_IN                  0
#define EV_SCHED_OUT                 1

typedef struct perf_stat_time_st {
    uint64_t time_start;
    uint64_t time_elapse;
    double sec_elapse;
} perf_stat_time_t;
//extern perf_stat_time_t g_perf_real_time;

typedef struct perf_pmu_st {
    uint64_t time_start;
    uint64_t time_end;
    uint64_t cnt;
    struct perf_pmu_event_st* event;
} perf_pmu_t;

typedef struct perf_pmu_event_st {
    uint64_t cnt;
    uint64_t enable_time;
    uint64_t schedule_time;
    uint8_t sched_status;

    // pointer to pmu counter registed to this event
    struct perf_pmu_st *pmu;

    // index of hpm-events, this attribute is invalid for 'cycle' and 'instret'
    uint16_t ev_idx;
} perf_pmu_event_t;

typedef struct perf_pmu_list_st {
    perf_pmu_t pmus[CONFIG_PMU_COUNTERS_NR];
} perf_pmu_list_t;

typedef struct perf_pmu_evlist_st {
    uint64_t time;

    // cycle and instret
    perf_pmu_event_t ev_cycle;
    perf_pmu_event_t ev_instret;

    // number of pmu hpm-counter events
    uint32_t nr_hpm_events;

    // list of hpm-counter events
    perf_pmu_event_t *evlist_mhpmcounter;
} perf_pmu_evlist_t;

typedef struct perf_ev_cycle_st {
    uint64_t total;
    uint8_t is_display;
} perf_stat_cycle_t;

typedef struct perf_ev_instret_st {
    uint64_t total;
    uint8_t is_display;
} perf_stat_instret_t;

// statics for an hpm-counter event on all cpus
typedef struct perf_ev_hpm_st {
    uint16_t ev;
    uint64_t total;
    perf_pmu_event_t* ev_ptr[CONFIG_NR_CPUS];
    uint8_t is_display;
} perf_ev_mhp_global_t;

typedef struct perf_event_scheduler_state_st
{
    uint16_t p0;
    uint16_t p1;
    uint8_t is_running;
} perf_events_scheduler_state_t;

// log buffer
#define INITIAL_BUFFER_SIZE 256
typedef struct {
    char *data;
    uint64_t size;
    uint64_t capacity;
} Buffer;

static uint16_t ev_default[] = {PMU_HPM_Branch_Instruction, PMU_HPM_Branch_Mispred};
static uint8_t cpu_default[CONFIG_NR_CPUS];

static perf_pmu_list_t pmu_list[CONFIG_NR_CPUS];
static perf_pmu_evlist_t ev_list[CONFIG_NR_CPUS];

static perf_stat_cycle_t g_perf_cycle;
static perf_stat_instret_t g_perf_instret;
static perf_ev_mhp_global_t* g_perf_mhp = NULL;
static perf_stat_time_t g_perf_real_time;

static volatile uint8_t flag_stop[CONFIG_NR_CPUS] = {0};

static volatile uint64_t stat_finish_times[CONFIG_NR_CPUS] = {0};
static volatile int perf_stat_status = PERF_STAT_STOP;
static perf_events_scheduler_state_t sched_state[CONFIG_NR_CPUS];

perf_stat_args_t stat_config = {
    .events = NULL,
    .cpu_ids = NULL,
    .tids = NULL,
    .nr_threads = 0,
    .nr_events = 0,
    .nr_cpus = 0,
    .pmu_schedule = 0,
};

#if defined(CONFIG_PMU_EVENTS_CONFIGURABLE)
typedef struct sched_args_st {
    int n_events;
} sched_args_t;

static sched_args_t sched_args = {
    .n_events = CONFIG_PERF_STAT_SCHEDULER_NR_EVENTS,
};

static csi_timer_t pmu_scheduler_timer[CONFIG_NR_CPUS];
#endif

static void timer_cb(csi_timer_t* pmu_scheduler_timer, void* args);
static void init_buffer(Buffer *buffer);
static void append_to_buffer(Buffer *buffer, const char *format, ...);
static void print_buffer(const Buffer *buffer);
static void clear_buffer(const Buffer *buffer);
static void free_buffer(Buffer *buffer);
static uint8_t is_perf_stat_running(void);
static uint16_t ev_hash(char* ev_str, int maxsize);
static void check_args(perf_stat_args_t* args);
static void get_real_time_start(void);
static void get_real_time_end(void);
static void perf_stat_cpu_start(void);
static void perf_stat_cpu_stop(void);
static uint8_t events_create(uint16_t* mhp_events, uint32_t n_mhp_events);
static void pmu_config(void);
static void pmu_scheduler(void* args);
static void perf_stat_get_result(void);
static void perf_stat_dump_result(void);

static inline void pmu_counter_enable(void)
{
    __set_MCOUNTINHIBIT(0);
}

static inline void pmu_counter_disable(void)
{
    __set_MCOUNTINHIBIT(0xffffffff);
}

static inline void write_pmu_mhpmcounter(int idx, uint64_t value)
{
#if __riscv_xlen == 64
    __set_MHPMCOUNTER(idx, value);
#else
    __set_MHPMCOUNTER(idx, (uint32_t)(value & 0x0ffff));
    __set_MHPMCOUNTERH(idx, (uint32_t)((value >> 32) & 0x0ffff));
#endif
}

static inline uint64_t read_pmu_mhpcounter(uint16_t n)
{
    uint64_t result;
#if __riscv_xlen == 64
    result = __get_MHPMCOUNTER(n);
#else
    result = ((uint64_t)__get_MHPMCOUNTERH(n) << 32) | __get_MHPMCOUNTER(n);
#endif
    return result;
}

static inline void write_mcycle(uint64_t value)
{
#if __riscv_xlen == 64
    __set_MCYCLE(value);
#else
    __set_MCYCLE((uint32_t)(value & 0x0ffff));
    __set_MCYCLEH((uint32_t)((value >> 32) & 0x0ffff));
#endif
}

static inline uint64_t read_mcycle(void)
{
    uint64_t result;
#if __riscv_xlen == 64
    result = __get_MCYCLE();
#else
    result = ((uint64_t)__get_MCYCLEH() << 32) | __get_MCYCLE();
#endif
    return result;
}

static inline void write_minstret(uint64_t value)
{
#if __riscv_xlen == 64
    __set_MINSTRET(value);
#else
    __set_MINSTRET((uint32_t)(value & 0x0ffff));
    __set_MINSTRETH((uint32_t)((value >> 32) & 0x0ffff));
#endif
}

static inline uint64_t read_minstret(void)
{
    uint64_t result;
#if __riscv_xlen == 64
    result = __get_MINSTRET();
#else
    result = ((uint64_t)__get_MINSTRETH() << 32) | __get_MINSTRET();
#endif
    return result;
}

static void print_all_events(void)
{
    Buffer print_all_buffer;
    init_buffer(&print_all_buffer);
    for(int i = 0; i < CONFIG_NR_CPUS; i++)
    {
        int total_sched_in = 0;
        append_to_buffer(&print_all_buffer, "------------cpu:%d-------------\r\n", i);
        for(int j = 0; j < ev_list->nr_hpm_events; j++)
        {
            append_to_buffer(&print_all_buffer, "%-6s%-6s%-15s%-16s%-10s%-16s\r\n", "id", "prio", "prio-sched", "cnt", "sched", "sched-time");
            append_to_buffer(&print_all_buffer, "%-6ld%-6ld%-15ld%-16ld%-10ld%-16ld\r\n",
                ev_list[i].evlist_mhpmcounter[j].ev_idx,
                ev_list[i].evlist_mhpmcounter[j].cnt,
                ev_list[i].evlist_mhpmcounter[j].sched_status,
                ev_list[i].evlist_mhpmcounter[j].schedule_time
            );
            total_sched_in += (ev_list->evlist_mhpmcounter[j].sched_status == EV_SCHED_IN);
        }
        append_to_buffer(&print_all_buffer, "cpu %d total_sched_in: %d\r\n", i, total_sched_in);
    }
    print_buffer(&print_all_buffer);
    free_buffer(&print_all_buffer);
}

static void init_buffer(Buffer *buffer)
{
    buffer->data = (char *)perf_malloc(INITIAL_BUFFER_SIZE);
    buffer->size = 0;
    buffer->capacity = INITIAL_BUFFER_SIZE;
}

void append_to_buffer(Buffer *buffer, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    // Estimate required size
    uint64_t requiredSize = vsnprintf(NULL, 0, format, args) + 1; // +1 for null terminator

    // Reset va_list for actual formatting
    va_end(args);
    va_start(args, format);

    // Ensure buffer capacity
    while (buffer->size + requiredSize >= buffer->capacity) {
        buffer->capacity *= 2;
        buffer->data = (char *)perf_realloc(buffer->data, buffer->capacity);
        if (buffer->data == NULL) {
            perf_printf("append_to_buffer(): Memory allocation failed\n");
            va_end(args);
            return;
        }
    }

    // Append formatted content
    vsnprintf(buffer->data + buffer->size, requiredSize, format, args);
    buffer->size += requiredSize - 1; // Exclude the null terminator

    va_end(args);
}

static void print_buffer(const Buffer *buffer)
{
    perf_printf("%s", buffer->data);
}

static void free_buffer(Buffer *buffer)
{
    perf_free(buffer->data);
    buffer->size = 0;
    buffer->capacity = 0;
    buffer->data = NULL;
}

static void perf_stat_cpu_start(void)
{
    get_real_time_start();
    events_create(stat_config.events, stat_config.nr_events);
    pmu_config();
    if (stat_config.nr_threads == 0)
    {
        // if not use -t, enable counters
        pmu_counter_enable();
    }
    else
    {
        // if use -t, counters will be enabled in perf_on_task_switch()
        pmu_counter_disable();
    }
}

static void perf_stat_cpu_stop(void)
{
    pmu_counter_disable();
    get_real_time_end();
    uint8_t cpu_id = csi_get_cpu_id();
    // read PMU counters
    ev_list[cpu_id].ev_cycle.pmu->cnt = read_mcycle();
    ev_list[cpu_id].ev_instret.pmu->cnt = read_minstret();
    ev_list[cpu_id].ev_cycle.cnt = ev_list[cpu_id].ev_cycle.pmu->cnt;
    ev_list[cpu_id].ev_instret.cnt = ev_list[cpu_id].ev_instret.pmu->cnt;

    if (stat_config.pmu_schedule)
    {
        sched_state[cpu_id].p0 = 0;
        sched_state[cpu_id].p1 = CONFIG_PMU_COUNTERS_NR - 2;
        sched_state[cpu_id].is_running = 0;
    }
    else
    {
        for (int i = 0; i < ev_list[cpu_id].nr_hpm_events; i++)
        {
            ev_list[cpu_id].evlist_mhpmcounter[i].pmu->cnt = read_pmu_mhpcounter(i + 3);
            ev_list[cpu_id].evlist_mhpmcounter[i].cnt = ev_list[cpu_id].evlist_mhpmcounter[i].pmu->cnt;
        }
    }
    for (int i = 0; i < ev_list[cpu_id].nr_hpm_events; i++)
    {
        ev_list[cpu_id].evlist_mhpmcounter[i].enable_time = g_perf_real_time.time_elapse;
    }
    // get stop time
    flag_stop[cpu_id] = 1;
}

static uint8_t is_perf_stat_running(void)
{
    for (int i = 0; i < stat_config.nr_cpus; i++)
    {
        if (!flag_stop[i])
        {
            return 1;
        }
    }
    return 0;
}

static void check_args(perf_stat_args_t* args)
{
    if (!args)
    {
        return;
    }
    // check events
    if (args->nr_events == 0)
    {
        args->nr_events = sizeof(ev_default) / sizeof(uint16_t);

        args->events = (uint16_t*)perf_malloc(args->nr_events * sizeof(uint16_t));
        if (!args->events)
        {
            perf_printf("failed to malloc memory for perf stat params\r\n");
        }
        for (int i = 0; i < args->nr_events; i++)
        {
            args->events[i] = ev_default[i];
        }
    }
    // check cpus
    if (args->nr_cpus == 0)
    {
        args->nr_cpus = CONFIG_NR_CPUS;
        args->cpu_ids = (uint8_t*) perf_malloc(CONFIG_NR_CPUS);
        if (!args->cpu_ids)
        {
            perf_printf("failed to malloc memory for perf stat params\r\n");
        }
        for (int i = 0; i < args->nr_cpus; i++)
        {
            args->cpu_ids[i] = i;
        }
    }
}

static uint16_t ev_hash(char* ev_str, int maxsize)
{
    int len = strlen(ev_str);
    if (len == 0)
    {
        return 0;
    }
    for (uint16_t i = 0; i <= PMU_MHPM_EVENTS_MAX; i++)
    {
        if (strncmp(ev_str, perf_event_name[i], len) == 0)
        {
            return i;
        }
    }
    return 0;
}

// get mtime. this is the only timer of the cluster.
static void get_real_time_start(void)
{
    g_perf_real_time.time_start = __get_MTIME();
    g_perf_real_time.time_elapse = 0;
    g_perf_real_time.sec_elapse = 0;
}

static void get_real_time_end(void)
{
    g_perf_real_time.time_elapse = __get_MTIME() - g_perf_real_time.time_start;
    g_perf_real_time.sec_elapse = (float)g_perf_real_time.time_elapse / (float)soc_get_coretim_freq();
}

static uint8_t events_create(uint16_t* mhp_events, uint32_t n_mhp_events)
{
    uint8_t cpu_id = csi_get_cpu_id();

    /* reset ev_list */
    ev_list[cpu_id].time = 0;
    ev_list[cpu_id].nr_hpm_events = 0;

    /* reset cycles and instret */
    ev_list[cpu_id].ev_cycle.pmu = &pmu_list[cpu_id].pmus[0];
    ev_list[cpu_id].ev_instret.pmu = &pmu_list[cpu_id].pmus[1];

    if (ev_list[cpu_id].evlist_mhpmcounter)
    {
        perf_free(ev_list[cpu_id].evlist_mhpmcounter);
        ev_list[cpu_id].evlist_mhpmcounter = NULL;
    }
    /* initialize */
    ev_list[cpu_id].evlist_mhpmcounter = (perf_pmu_event_t*)perf_malloc(n_mhp_events * sizeof(perf_pmu_event_t));
    if (!ev_list[cpu_id].evlist_mhpmcounter)
    {
        perf_printf("events_create() failed: no enough memory.\r\n");
        return 1;
    }
    pmu_list[cpu_id].pmus[0].cnt = 0;  // cycle
    pmu_list[cpu_id].pmus[1].cnt = 0;  // instret
    for (uint32_t i = 0; i < n_mhp_events; i++)
    {
        ev_list[cpu_id].evlist_mhpmcounter[i].ev_idx = mhp_events[i];
        ev_list[cpu_id].nr_hpm_events = n_mhp_events;
        ev_list[cpu_id].evlist_mhpmcounter[i].pmu = NULL;
        ev_list[cpu_id].evlist_mhpmcounter[i].sched_status = EV_SCHED_OUT;
        ev_list[cpu_id].evlist_mhpmcounter[i].schedule_time = 0;
        ev_list[cpu_id].evlist_mhpmcounter[i].enable_time = 0;
        ev_list[cpu_id].evlist_mhpmcounter[i].cnt = 0;
        g_perf_mhp[i].ev_ptr[cpu_id] = &(ev_list[cpu_id].evlist_mhpmcounter[i]);
    }
    return 0;
}

// write event registers and reset counters
static void pmu_config(void)
{
    uint8_t cpu_id = csi_get_cpu_id();
    uint64_t current_time = __get_MTIME();
    // close all
    __set_MCOUNTINHIBIT(0xffffffff);

    // clean all and set events
    write_mcycle(0);
    write_minstret(0);
#if defined(CONFIG_PMU_EVENTS_CONFIGURABLE)
    for (int i = 3; i < CONFIG_PMU_COUNTERS_NR; i++)
    {
        pmu_list[cpu_id].pmus[i].event = NULL;
        pmu_list[cpu_id].pmus[i].cnt = 0;
        write_pmu_mhpmcounter(i, 0);
    }
    if (stat_config.pmu_schedule)
    {
        for (int i = 3; i < CONFIG_PMU_COUNTERS_NR; i++)
        {
            perf_pmu_event_t* ev_sched_in = &ev_list[cpu_id].evlist_mhpmcounter[i - 3];
            ev_sched_in->sched_status = EV_SCHED_IN;
            ev_sched_in->pmu = &pmu_list[cpu_id].pmus[i - 1];
            pmu_list[cpu_id].pmus[i - 1].event = ev_sched_in;
            pmu_list[cpu_id].pmus[i - 1].time_start = current_time;
            pmu_list[cpu_id].pmus[i - 1].time_end = current_time;
            __set_MHPMEVENT(i, ev_sched_in->ev_idx);
            write_pmu_mhpmcounter(i, 0);
        }
        sched_state[cpu_id].p0 = 0;
        sched_state[cpu_id].p1 = CONFIG_PMU_COUNTERS_NR - 3;
        sched_state[cpu_id].is_running = 1;
    }
    else
    {
        sched_state[cpu_id].is_running = 0;
        for (uint32_t i = 0; i < ev_list[cpu_id].nr_hpm_events; i++)
        {
            ev_list[cpu_id].evlist_mhpmcounter[i].pmu = &pmu_list[cpu_id].pmus[i+2];
            pmu_list[cpu_id].pmus[i+2].event = &ev_list[cpu_id].evlist_mhpmcounter[i];
            __set_MHPMEVENT(i + 3, ev_list[cpu_id].evlist_mhpmcounter[i].ev_idx);
            write_pmu_mhpmcounter(i + 3, 0);
        }
    }
#elif defined(CONFIG_PMU_EVENTS_FIXED)
    sched_state[cpu_id].is_running = 0;
    for (uint32_t i = 0; i < CONFIG_NR_HPM_EVENT_FIXED; i++)
    {
        int idx = events_fixed[i];
        ev_list[cpu_id].evlist_mhpmcounter[i].pmu = &pmu_list[cpu_id].pmus[idx + 1];
        pmu_list[cpu_id].pmus[idx + 1].event = &ev_list[cpu_id].evlist_mhpmcounter[i];
        pmu_list[cpu_id].pmus[idx + 1].time_start = current_time;
        pmu_list[cpu_id].pmus[idx + 1].time_end = current_time;
        __set_MHPMEVENT(idx + 2, idx);
        write_pmu_mhpmcounter(idx + 2, 0);
    }
#else  // CONFIG_PMU_EVENTS_NOT_SUPPORT is defined
#endif
}

void perf_on_task_switch(perf_thread_id to)
{
    if (is_perf_stat_running())
    {
        if (stat_config.nr_threads == 0)
        {
            pmu_counter_enable();
            return;
        }
        for (int i = 0; i < stat_config.nr_threads; i++)
        {
            if (stat_config.tids[i] == to)
            {
                pmu_counter_enable();
                return;
            }
        }
        pmu_counter_disable();
    }
}

// init perf-stat system
void perf_stat_init(void)
{
    // initialize pmu-list
    for (int i = 0; i < CONFIG_NR_CPUS; i++)
    {
        pmu_list[i].pmus[0].event = &ev_list[i].ev_cycle;
        pmu_list[i].pmus[1].event = &ev_list[i].ev_instret;

        // cycle event and in struction retire event
        ev_list[i].ev_cycle.pmu = &pmu_list[i].pmus[0];
        ev_list[i].ev_instret.pmu = &pmu_list[i].pmus[1];
        ev_list[i].evlist_mhpmcounter = NULL;
        ev_list[i].nr_hpm_events = 0;
        stat_finish_times[i] = 0;
    }
    g_perf_cycle.total = 0;
    g_perf_cycle.is_display = 0;
    g_perf_instret.total = 0;
    g_perf_instret.is_display = 0;
    g_perf_mhp = NULL;
    perf_stat_status = PERF_STAT_STOP;
    perf_task_switch_sethook(perf_on_task_switch);
}

// deinit perf-stat
void perf_stat_deinit(void)
{
    g_perf_cycle.total = 0;
    g_perf_cycle.is_display = 0;
    g_perf_instret.total = 0;
    g_perf_instret.is_display = 0;
    if (g_perf_mhp) {
        perf_free(g_perf_mhp);
        g_perf_mhp = NULL;
    }

    for (int i = 0; i < CONFIG_NR_CPUS; i++)
    {
        if (ev_list[i].evlist_mhpmcounter)
        {
            perf_free(ev_list[i].evlist_mhpmcounter);
            ev_list[i].nr_hpm_events = 0;
            ev_list[i].evlist_mhpmcounter = NULL;
        }
    }
}

void perf_stat_start(perf_stat_args_t* args)
{
    uint8_t cpu_id = csi_get_cpu_id();
    check_args(args);
    // cpu0: initialize global variables
    if (cpu_id == 0)
    {
        for (int i = 0; i < CONFIG_NR_CPUS; i++)
        {
            cpu_default[i] = i;
        }
        if (!args)
        {
            stat_config.nr_cpus = CONFIG_NR_CPUS;
            stat_config.nr_events = sizeof(ev_default) / sizeof(uint16_t);
            stat_config.events = ev_default;
            stat_config.cpu_ids = cpu_default;
            stat_config.nr_threads = 0;
            stat_config.tids = NULL;
        }
        else
        {
            stat_config.nr_events = args->nr_events;
            stat_config.events = args->events;
            stat_config.nr_cpus = args->nr_cpus;
            stat_config.cpu_ids = args->cpu_ids;
            stat_config.nr_threads = args->nr_threads;
            stat_config.tids = args->tids;
        }

#if defined(CONFIG_PMU_EVENTS_FIXED)
        stat_config.nr_events = CONFIG_NR_HPM_EVENT_FIXED;
        stat_config.events = events_fixed;
#else
        // if there are more events than counters, enable scheduler
        stat_config.pmu_schedule = (args->nr_events > CONFIG_PMU_COUNTERS_NR - 3);
#endif
        g_perf_mhp = (perf_ev_mhp_global_t*)perf_malloc(stat_config.nr_events * sizeof(perf_ev_mhp_global_t));
        if (!g_perf_mhp)
        {
            perf_printf("perf_stat_start(): g_perf_mhp malloc failed, size = %d\r\n", stat_config.nr_events);
        }
        g_perf_cycle.total = 0;
        g_perf_cycle.is_display = 1;
        g_perf_instret.total = 0;
        g_perf_cycle.is_display = 1;
        for (int i = 0; i < CONFIG_NR_CPUS; i++)
        {
            flag_stop[i] = 0;
        }
        for (int i = 0; i < args->nr_events; i++)
        {
            g_perf_mhp[i].ev = args->events[i];
            g_perf_mhp[i].total = 0;
            g_perf_mhp[i].is_display = 1;
        }
#if defined(CONFIG_NR_HPM_EVENT_FIXED)
        for (int i = 0; i < stat_config.nr_events; i++)
        {
            g_perf_mhp[i].is_display = 0;
            for (int j = 0; j < args->nr_events; j++)
            {
                if (stat_config.events[i] == args->events[j])
                {
                    g_perf_mhp[i].is_display = 1;
                }
            }
        }
#endif
        // initialize g_perf_hmp, g_perf_cycles and g_perf_instret
        perf_stat_status = PERF_STAT_CORE0_INIT;
    }

    // secondary cpus: wait until initialized
    else
    {
        while (perf_stat_status != PERF_STAT_CORE0_INIT)
        {
            if(perf_thread_yield() != PERF_OK)
            {
                perf_printf("perf_thread_yield() failed\r\n");
            }
        }
    }

#if defined(CONFIG_PMU_EVENTS_CONFIGURABLE)
    if (stat_config.nr_events >= CONFIG_PMU_COUNTERS_NR - 2)
    {
        stat_config.pmu_schedule = 1;
        int timer_idx = g_cpu_bind_timer[cpu_id].timer_idx;
        int ret = csi_timer_init(&pmu_scheduler_timer[cpu_id], timer_idx);
        if (ret != CSI_OK)
        {
            perf_printf("csi_timer_init() failed.\r\n");
        }
        ret = csi_timer_attach_callback(&pmu_scheduler_timer[cpu_id], timer_cb, &sched_args);
        if (ret != CSI_OK)
        {
            perf_printf("csi_timer_attach_callback() failed.\r\n");
        }
        ret = csi_timer_start(&pmu_scheduler_timer[cpu_id], CONFIG_PMU_SCHED_PERIOD_US);
        if (ret != CSI_OK)
        {
            perf_printf("csi_timer_start() failed.\n");
        }
    }
#endif
    // create events and enable pmu counters for each cpu
    perf_stat_cpu_start();
}

void perf_stat_stop(void)
{
    // stop pmus, read events of each cpu and set flag_stop[cpuid]
    perf_stat_cpu_stop();

    // wait until all cpus finish, print result and reset global parameters
    uint8_t cpu_id = csi_get_cpu_id();
    if (cpu_id == 0)
    {
        for (int i = 1; i < CONFIG_NR_CPUS; i++)
        {
            while (flag_stop[i] == 0)
            {
                if(perf_thread_yield() != PERF_OK)
                {
                    perf_printf("perf_thread_yield() failed\r\n");
                }
            }
        }
        perf_stat_status = PERF_STAT_SECONDARY_STOP;
        flag_stop[0] = 1;
        perf_stat_dump_result();
        perf_free(g_perf_mhp);
        perf_stat_status = PERF_STAT_STOP;
    }
#if CONFIG_NR_CPUS > 1
    else
    {
        while (flag_stop[0] == 0 || stat_finish_times[cpu_id] > stat_finish_times[0])
        {
            if(perf_thread_yield() != PERF_OK)
            {
                perf_printf("perf_thread_yield() failed\r\n");
            }
        }
    }
#endif  // CONFIG_NR_CPUS

#if defined(CONFIG_NR_HPM_EVENT_CONFIGURABLE)
    csi_timer_detach_callback(&pmu_scheduler_timer[cpu_id]);
    csi_timer_stop(&pmu_scheduler_timer[cpu_id]);
    csi_timer_uninit(&pmu_scheduler_timer[cpu_id]);
#endif
    stat_finish_times[cpu_id]++;
}

uint16_t get_event_id(char* ev_name)
{
    return ev_hash(ev_name, 64);
}

void perf_stat_get_result(void)
{
    // sum up
    g_perf_cycle.total = 0;
    g_perf_instret.total = 0;
    for (int i = 0; i < stat_config.nr_events; i++)
    {
        g_perf_mhp[i].total = 0;
    }
    for (int i = 0; i < stat_config.nr_cpus; i++)
    {
        int cpu_id = stat_config.cpu_ids[i];
        g_perf_cycle.total += ev_list[cpu_id].ev_cycle.cnt;
        g_perf_instret.total += ev_list[cpu_id].ev_instret.cnt;
        for (int j = 0; j < ev_list[cpu_id].nr_hpm_events; j++)
        {
            if (stat_config.pmu_schedule)
            {
                double factor = 0.0;
                if (g_perf_mhp[j].ev_ptr[cpu_id]->schedule_time > 0)
                {
                    factor = (1.0 * g_perf_mhp[j].ev_ptr[cpu_id]->enable_time)
                        / g_perf_mhp[j].ev_ptr[cpu_id]->schedule_time;
                }
                g_perf_mhp[j].total += (uint64_t) round(g_perf_mhp[j].ev_ptr[cpu_id]->cnt * factor);
            }
            else
            {
                g_perf_mhp[j].total += g_perf_mhp[j].ev_ptr[cpu_id]->cnt;
            }
        }
    }
}

void perf_list_events(void)
{
    Buffer buffer;
    init_buffer(&buffer);
    append_to_buffer(&buffer, "\r\n%-10s%-45s\r\n","index", "event-name");
    append_to_buffer(&buffer, "-------------------------------------\r\n");
#if defined(CONFIG_PMU_EVENTS_CONFIGURABLE)
    for (int i = 0; i < PMU_MHPM_EVENTS_MAX; i++)
    {
        if (perf_event_name[i] != NULL)
        {
            append_to_buffer(&buffer, "%-10d%-45s\r\n", i, perf_event_name[i]);
        }
    }
#elif defined(CONFIG_PMU_EVENTS_FIXED)
    for (int i = 0; i < CONFIG_NR_HPM_EVENT_FIXED; i++)
    {
        int idx = events_fixed[i];
        append_to_buffer(&buffer, "%-10d%-45s\r\n", idx, perf_event_name[idx]);
    }
#else // CONFIG_PMU_EVENTS_NOT_SUPPORT is defined
    append_to_buffer(&buffer, "This cpu does not support any pmu event.\r\n");
#endif
    append_to_buffer(&buffer, "-------------------------------------\r\n");
    append_to_buffer(&buffer, "This cpu may not support some of the events above, please refer to the manual.\r\n");
    print_buffer(&buffer);
    free_buffer(&buffer);
}

void perf_stat_dump_result(void)
{
    perf_stat_get_result();
    Buffer buffer;
    init_buffer(&buffer);
    append_to_buffer(&buffer, "\r\n");
    append_to_buffer(&buffer, "Performance counter stat for");
    if (stat_config.nr_cpus != 0 && stat_config.nr_cpus != CONFIG_NR_CPUS
        &&(stat_config.nr_threads != 0)
    )
    {
        append_to_buffer(&buffer, " task(s): ");
        for (int i = 0; i < stat_config.nr_threads; i++)
        {
            append_to_buffer(&buffer, "%p,", stat_config.tids[i]);
        }
        append_to_buffer(&buffer, "\r\n");
    }
    else if ((stat_config.nr_cpus != 0 && stat_config.nr_cpus != CONFIG_NR_CPUS))
    {
        append_to_buffer(&buffer, " cpu(s): ");
        for(int i = 0; i < stat_config.nr_cpus; i++)
        {
            append_to_buffer(&buffer, "%d,", stat_config.cpu_ids[i]);
        }
        append_to_buffer(&buffer, "\r\n");
    }
    else
    {
        append_to_buffer(&buffer, " system wide\r\n");
    }
    append_to_buffer(&buffer, "\r\n");

    float time = g_perf_real_time.sec_elapse;

    append_to_buffer(&buffer, "%-30lld %-32s#%-20.3f CPUs utilized\r\n",
        g_perf_cycle.total, "cycles", (1.0 * g_perf_cycle.total * soc_get_coretim_freq()) / (g_perf_real_time.time_elapse * soc_get_cpu_freq(0)));

    append_to_buffer(&buffer, "%-30lld %-32s %-20.3f/sec\r\n",
        g_perf_instret.total, "instructions-retired", 1.0f * g_perf_instret.total/time);

    for (int i = 0; i < stat_config.nr_events; i++)
    {
        if (g_perf_mhp[i].is_display == 0)
        {
            continue;
        }
        if (stat_config.events[i] != 0)
        {
            append_to_buffer(&buffer, "%-30lld %-32s %-20.3f/sec\r\n",
                g_perf_mhp[i].total, perf_event_name[stat_config.events[i]], g_perf_mhp[i].total / time);
        }
        else
        {
            append_to_buffer(&buffer, "%-30lld %-32s %-20.3f/sec\r\n",
                g_perf_mhp[i].total, "<error-event>", g_perf_mhp[i].total / time);
        }
    }
    append_to_buffer(&buffer, "\r\n");
    append_to_buffer(&buffer, "%f seconds time elapsed\r\n", time);
    print_buffer(&buffer);
    free_buffer(&buffer);
}

static void pmu_scheduler(void* args)
{
    pmu_counter_disable();
    uint8_t cpu_id = csi_get_cpu_id();
    int n = CONFIG_PMU_COUNTERS_NR - 3;
    uint64_t current_time = __get_MTIME();
    for (int i = 3; i < CONFIG_PMU_COUNTERS_NR; i++)
    {
        pmu_list[cpu_id].pmus[i-1].cnt = read_pmu_mhpcounter(i);
    }

    // switch out
    int pmu_idx = 2;
    while (sched_state[cpu_id].p0 != sched_state[cpu_id].p1)
    {
        ev_list[cpu_id].evlist_mhpmcounter[sched_state[cpu_id].p0].cnt += pmu_list[cpu_id].pmus[pmu_idx].cnt;
        ev_list[cpu_id].evlist_mhpmcounter[sched_state[cpu_id].p0].schedule_time += (current_time - pmu_list[cpu_id].pmus[pmu_idx].time_start);
        sched_state[cpu_id].p0 = (sched_state[cpu_id].p0 + 1) % (stat_config.nr_events);
        pmu_idx++;
    }
    sched_state[cpu_id].p1 = (sched_state[cpu_id].p1 + n) % stat_config.nr_events;

    // switch in
    pmu_idx = 2;
    uint64_t p00 = sched_state[cpu_id].p0;
    while (sched_state[cpu_id].p0 != sched_state[cpu_id].p1)
    {
       pmu_list[cpu_id].pmus[pmu_idx].cnt = 0;
       pmu_list[cpu_id].pmus[pmu_idx].event = &ev_list[cpu_id].evlist_mhpmcounter[sched_state[cpu_id].p0];
       pmu_list[cpu_id].pmus[pmu_idx].time_start = current_time;
       write_pmu_mhpmcounter(pmu_idx + 1, 0);
       __set_MHPMEVENT(pmu_idx + 1, pmu_list[cpu_id].pmus[pmu_idx].event->ev_idx);
        sched_state[cpu_id].p0 = (sched_state[cpu_id].p0 + 1) % stat_config.nr_events;
        pmu_idx++;
    }
    sched_state[cpu_id].p0 = p00;
    if (stat_config.nr_threads == 0)
    {
        pmu_counter_enable();
    }
}

static void timer_cb(csi_timer_t* pmu_scheduler_timer, void* args)
{
    int cpu_id = csi_get_cpu_id();
    if (sched_state[cpu_id].is_running)
    {
        pmu_scheduler(args);
    }
}
