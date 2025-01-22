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
#include <errno.h>
#include <stdint.h>
#include <stdbool.h>
#include <csi_core.h>
#include <drv/timer.h>
#include <drv/tick.h>
#include "perf.h"
#include "perf_backtrace.h"

#define RECORD_STATE_BUF_FULL 			1
#define RECORD_STATE_TRACE_FINISH 		2
#define RECORD_STATE_TRACING 			3
#define RECORD_STATE_FORCE_STOP 		4
#define RECORD_STATE_BUF_DUMP 			5
#define RECORD_STATE_BUF_DUMP_END 		6
typedef struct {
#define PERF_DATA_HEAD_MAGIC 0x434F5950
	uint32_t magic;
	uint32_t duration_ms;
	uint32_t frequency;
	uint16_t cpu;
	uint16_t rsv;
	uint32_t elapsed_ms;
	uint32_t rsv2[11];
	unsigned long buf[];
} perf_buf_head_t;

typedef struct perf_data {
	uint32_t tick;
	uint32_t duration_ms;
	uint32_t frequency;
	volatile uint32_t state;
	size_t buf_idx;
	unsigned long *buf;
	csi_timer_t timer;
} perf_data_t;

static perf_data_t g_perf_data[CONFIG_NR_CPUS];

static void perf_tracer_finish(csi_timer_t *timer, perf_data_t *pdata)
{
	perf_buf_head_t *bufhead = (perf_buf_head_t *)pdata->buf;

	bufhead->elapsed_ms = pdata->tick * 1000 / pdata->frequency;
	csi_timer_detach_callback(timer);
	csi_timer_stop(timer);
	csi_timer_uninit(timer);

	// TODO: dump data
	perf_record_dump();
	perf_record_free_data_buf(pdata->buf);
	pdata->state = RECORD_STATE_TRACE_FINISH;
}

static void perf_tracer(csi_timer_t *timer, void *arg)
{
	const size_t buf_size = CONFIG_PROFILING_PERF_PER_CORE_BUFFER_SIZE / sizeof(unsigned long);
	perf_data_t *pdata = (perf_data_t *)arg;

	++pdata->tick;

	if ((uint64_t)pdata->tick * 1000U / pdata->frequency > pdata->duration_ms || pdata->state == RECORD_STATE_FORCE_STOP) {
		if (pdata->state != RECORD_STATE_FORCE_STOP) {
			perf_printf("time up.\n");
		}
		perf_printf("stop record, pdata->tick: %u\n", pdata->tick);
		perf_tracer_finish(timer, pdata);
		return;
	}
	ssize_t trace_length = 0;
	if (++pdata->buf_idx < buf_size) {
		trace_length = perf_backtrace(pdata->buf + pdata->buf_idx, buf_size - pdata->buf_idx);
	} else {
		--pdata->buf_idx;
		pdata->state = RECORD_STATE_BUF_FULL;
		perf_printf("buffer is full, will stop.\n");
		perf_tracer_finish(timer, pdata);
		return;
	}

	if (trace_length > 0) {
		pdata->buf[pdata->buf_idx - 1] = trace_length;
		pdata->buf_idx += trace_length;
	} else if (trace_length == 0) {
	} else {
		--pdata->buf_idx;
		perf_printf("trace_length:%d\n", trace_length);
	}
}

int perf_record_start(uint32_t duration_ms, uint32_t frequency)
{
    int ret;
	csi_timer_t *timer;
	perf_buf_head_t datahead;
	unsigned long *databuf_addr;

	if (!(duration_ms > 0) && (frequency > 0)) {
		return -EINVAL;
	}

	int cpu_id = csi_get_cpu_id();
	int timer_idx = g_cpu_bind_timer[cpu_id].timer_idx;

	if (g_perf_data[cpu_id].state != RECORD_STATE_TRACE_FINISH && g_perf_data[cpu_id].state != 0) {
		perf_printf("perf record is running in core[%d].\n", cpu_id);
		return -EBUSY;
	}
	memset(&g_perf_data[cpu_id], 0, sizeof(perf_data_t));
	g_perf_data[cpu_id].state = RECORD_STATE_TRACING;
	databuf_addr = perf_record_alloc_data_buf();
	if (!databuf_addr) {
		g_perf_data[cpu_id].state = RECORD_STATE_TRACE_FINISH;
		return -ENOMEM;
	}
	perf_printf("alloc databuf: 0x%lx\n", databuf_addr);
	g_perf_data[cpu_id].buf = databuf_addr;
	memset(g_perf_data[cpu_id].buf, 0, CONFIG_PROFILING_PERF_PER_CORE_BUFFER_SIZE);
	timer = &g_perf_data[cpu_id].timer;
	g_perf_data[cpu_id].duration_ms = duration_ms;
	g_perf_data[cpu_id].frequency = frequency;

	memset(&datahead, 0, sizeof(datahead));
	datahead.magic = PERF_DATA_HEAD_MAGIC;
	datahead.duration_ms = duration_ms;
	datahead.frequency = frequency;
	datahead.cpu = cpu_id;
	memcpy(g_perf_data[cpu_id].buf, &datahead, sizeof(perf_buf_head_t));
	g_perf_data[cpu_id].buf_idx = sizeof(perf_buf_head_t) / sizeof(unsigned long);
	ret = csi_timer_init(timer, timer_idx);
    if (ret == CSI_OK) {
        ret = csi_timer_attach_callback(timer, perf_tracer, &g_perf_data[cpu_id]);
        if (ret == CSI_OK) {
            ret = csi_timer_start(timer, (1000000U / frequency));
			if (ret == CSI_OK) {
				return 0;
			} else {
				perf_printf("perf record timer[%d] start failed.\n", timer_idx);
			}
        }
    }
	csi_timer_detach_callback(timer);
	csi_timer_stop(timer);
	csi_timer_uninit(timer);
	perf_record_free_data_buf(databuf_addr);
	perf_printf("perf record start failed.\n");
	g_perf_data[cpu_id].state = RECORD_STATE_TRACE_FINISH;
	return ret;
}

int perf_record_stop(void)
{
	int cpu_id = csi_get_cpu_id();

	if (g_perf_data[cpu_id].state != RECORD_STATE_TRACE_FINISH)
		g_perf_data[cpu_id].state = RECORD_STATE_FORCE_STOP;
	perf_printf("come to perf_record_stop manual.\n");
	return 0;
}

#if CONFIG_PERF_DATA_SEMIHOST2_DUMP
#include <semihost2/semihost.h>
#ifndef SEMI_CHECK_RET_WITH_GOTO
#define SEMI_CHECK_RET_WITH_GOTO(x, label) \
	do { \
		if (!(x)) { \
			perf_printf("func[%s], line[%d] fail.\r\n", __FUNCTION__, __LINE__); \
			goto label; \
		}\
	} while (0)
#endif
#endif

static volatile int g_dump_flag;
__attribute__((weak)) int perf_record_dump(void)
{
	int cpu_id = csi_get_cpu_id();

	if (g_perf_data[cpu_id].buf_idx == 0) {
		perf_printf("there is no data, do not need dump.\n");
		return 0;
	}
	g_perf_data[cpu_id].state = RECORD_STATE_BUF_DUMP;

#if defined(CONFIG_SMP) && CONFIG_SMP
	while(1) {
		int i;
		for (i = 0; i < CONFIG_NR_CPUS; i++) {
			if (g_perf_data[i].state != RECORD_STATE_BUF_DUMP && g_perf_data[i].buf_idx) {
				break;
			}
		}
		if (i == CONFIG_NR_CPUS)
			break;
		mdelay(20);
	}
	if (cpu_id != 0) {
		while(g_perf_data[cpu_id].state != RECORD_STATE_BUF_DUMP_END) {}
		perf_printf("no need dump.\n");
		return 0;
	}
#endif

#if CONFIG_PERF_DATA_GDB_MANUAL_DUMP
	perf_printf("please use riscv64-unknown-elf-gdb to dump data:\n");
	for (int i = 0; i < CONFIG_NR_CPUS; i++) {
		if (g_perf_data[i].buf_idx) {
			perf_printf("dump memory perf_rtos_%d.data 0x%lx 0x%lx+%ld \n", i,
						(unsigned long)g_perf_data[i].buf, (unsigned long)g_perf_data[i].buf, g_perf_data[i].buf_idx * sizeof(unsigned long));
		}
	}
	g_dump_flag = 0;
	perf_printf("when finish dump, please input set g_dump_flag=1 to continue\n");
	while(!g_dump_flag) {}
	for (int i = 0; i < CONFIG_NR_CPUS; i++)
		g_perf_data[i].state = RECORD_STATE_BUF_DUMP_END;
	perf_printf("all dump finish.\n");
#endif

#if CONFIG_PERF_DATA_SEMIHOST2_DUMP
	// TODO: cpu0 to dump data
	long fd, rc;
	char filename[32];
	void *databuf;
	long data_len;

	for (int i = 0; i < CONFIG_NR_CPUS; i++) {
		if (g_perf_data[i].buf_idx == 0)
			continue;
		databuf = g_perf_data[i].buf;
		data_len = g_perf_data[i].buf_idx * sizeof(unsigned long);
		snprintf(filename, sizeof(filename), "perf_rtos_%d.data", i);
		perf_printf("start to dump [%s] perf data[len: %ld] with semihost.[start: %u ms]\n", filename, data_len, csi_tick_get_ms());
		semihost_printf("start to dump [%s] perf data[len: %ld] with semihost.[start: %u ms]\n", filename, data_len, csi_tick_get_ms());

		/* Open in write mode */
		fd = semihost_open(filename, SEMIHOST_OPEN_WB);
		SEMI_CHECK_RET_WITH_GOTO(fd > 0, error);
		rc = semihost_flen(fd);
		if (rc) {
			perf_printf("File may be not empty, rc = %d\r\n", (int)rc);
			goto error;
		}

		/* Write some data */
		rc = semihost_write(fd, databuf, data_len);
		SEMI_CHECK_RET_WITH_GOTO(rc == 0, error);
		rc = semihost_flen(fd);
		SEMI_CHECK_RET_WITH_GOTO(rc == data_len, error);

		/* Close the file */
		rc = semihost_close(fd);
		SEMI_CHECK_RET_WITH_GOTO(rc == 0, error);
		semihost_printf("success dump %s with semihost.[end: %u ms]\n", filename, csi_tick_get_ms());
		perf_printf("success dump %s with semihost.[end: %u ms]\n", filename, csi_tick_get_ms());
	}
	for (int i = 0; i < CONFIG_NR_CPUS; i++)
		g_perf_data[i].state = RECORD_STATE_BUF_DUMP_END;
	return 0;
error:
	perf_printf("failed dump perf data with semihost.\n");
	for (int i = 0; i < CONFIG_NR_CPUS; i++)
		g_perf_data[i].state = RECORD_STATE_BUF_DUMP_END;
	return -1;
#endif
	return 0;
}
