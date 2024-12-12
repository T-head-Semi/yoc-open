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

#ifndef YOC_AT_PARSER_H
#define YOC_AT_PARSER_H

#include <stdarg.h>

#include <aos/aos.h>
#include <uservice/uservice.h>
#include <devices/uart.h>
#include <yoc/at_port.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BUF_MIN_SIZE (1024*4)
#define BUF_MAX_SIZE (1024*4)
#define BUF_STEP_SIZE (32)

typedef struct oob_data {
    int time_stamp;
    char *buf;
    int len;
    int used_len;
} oob_data_t;

typedef struct atparser_uservice atparser_uservice_t;
typedef int (*oob_callback)(atparser_uservice_t *at, void *pive, oob_data_t *oob_data);

atparser_uservice_t *atparser_init(utask_t *task, const char *name, void *config);
atparser_uservice_t *atparser_channel_init(utask_t *task, const char *name, void *config, at_channel_t *channel);
int  atparser_oob_create(atparser_uservice_t *at, const char *prefix, oob_callback cb, void *context);
int  atparser_oob_delete(atparser_uservice_t *at, const char *prefix);
void atparser_set_terminator(atparser_uservice_t *at, const char *terminator);
void atparser_set_timeout(atparser_uservice_t *at, int timeout);
int  atparser_send(atparser_uservice_t *at, const char *format, ...);
int  atparser_recv(atparser_uservice_t *at, const char *response, ...);
void atparser_clr_buf(atparser_uservice_t *at);
void atparser_cmd_exit(atparser_uservice_t *at);
int atparser_write(atparser_uservice_t *at, const void *data, int size);
void atparser_debug_control(atparser_uservice_t *at, int flag);
int atparser_recv_str(atparser_uservice_t *at, const char *str);

#ifdef __cplusplus
}
#endif

#endif
