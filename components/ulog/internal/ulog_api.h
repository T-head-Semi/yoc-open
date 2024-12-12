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

#ifndef U_LOG_API__H
#define U_LOG_API__H
#include <stdint.h>
#include <stdbool.h>
#include "ulog_config.h"
#ifdef __cplusplus
extern "C" {
#endif

extern bool log_init;

bool log_get_mutex(void);

void log_release_mutex(void);

void log_init_mutex(void);

void on_sync_filter_level_change(const ulog_session_type_t session, const char level);
void on_filter_change(const ulog_session_type_t session, const char level);

uint8_t ulog_stop_filter_level(const ulog_session_type_t session);

char* get_sync_stop_level();

int32_t ulog_fs_init(void);
int32_t ulog_fs_deinit(void);

void on_filter_level_changes(const ulog_session_type_t session, const uint8_t level);

bool check_pass_pop_out(const ulog_session_type_t session, const uint8_t level);

void ulog_async_init();
void ulog_async_flush();

int32_t pop_out_on_udp(const char* data, const uint16_t len);

int32_t pop_out_on_fs(const char* data, const uint16_t len);

void on_show_ulog_file(void);

void update_net_cli(const char cmd, const char* param);

void fs_control_cli(const char cmd, const char* param);

void on_update_syslog_watcher_addr(const uint32_t ip_nl, const uint32_t port);
void on_tcpip_service_on(const uint32_t on, const uint32_t off);
void on_fs_record_pause(const uint32_t on, const uint32_t off);

char* trim_file_path(const char* path);
char *ulog_format_time(char *buffer, const int len);

int http_start(const char *url, const unsigned short idx);
void on_fs_upload(const uint32_t idx, const uint32_t start);

#ifdef __cplusplus
}
#endif

#endif /*U_LOG_API__H*/

