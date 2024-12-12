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

#ifndef DEBUG_LASTWORD_H
#define DEBUG_LASTWORD_H

#ifdef __cplusplus
extern "C" {
#endif

#define DEBUG_PANIC_HEADER_MAGIC 0xdeba5a5aa5a5abed
#define DEBUG_PANIC_LOG_MAGIC    0xdeba5a5aa5a5abed
#define DEFAULT_REBOOT_REASON    UND_STATIS_DEV_REPOWER_REASON

#define RUNTIME_COUNT 20

typedef struct {
    uint64_t header_magic;
    uint32_t reboot_reason_id;
    uint32_t reboot_sum_count;
    uint32_t reboot_reason;
    uint32_t panic_count;       /* record info of runtime before panic */
    uint32_t runtime_record_id;
    int64_t  runtime_before_painc[RUNTIME_COUNT];
    uint64_t log_magic;
    uint16_t crc16;
} debug_panic_info_head_t;

int  print_str(const char *fmt, ...);
int  vprint_str(const char *fmt, va_list ap);

void         debug_lastword_init(void);
void         debug_reboot_reason_update(unsigned int reason);
unsigned int debug_reboot_reason_get(void);
int64_t      debug_get_painc_runtime(int panic_count, int *real_panic_count);

#ifdef __cplusplus
}
#endif

#endif /* DEBUG_LASTWORD_H */

