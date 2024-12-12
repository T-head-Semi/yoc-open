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

#ifndef __HTTP_H__
#define __HTTP_H__

#include "util/network.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct http {
    char *path;
    char *host;
    uint8_t *buffer;
    int buffer_offset;
    char *url;
    int port;
    network_t net;
} http_t;

// char *json_getvalue(char *body, char *key, int *len);

http_t *http_init(const char *path);
int http_head_sets(http_t *http, const char *key, const char *value);
int http_head_seti(http_t *http, const char *key, int value);
int http_post(http_t *http, char *playload, int timeoutms);
int http_get(http_t *http, int timeoutms);
int http_wait_resp(http_t *http, char **head_end, int timeoutms);
char *http_head_get(http_t *http, char *key, int *length);
char *http_read_data(http_t *http);
int http_deinit(http_t *http);
#ifdef __cplusplus
}
#endif

#endif
