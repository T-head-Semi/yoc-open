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

#ifndef _DM_OPT_H
#define _DM_OPT_H

typedef enum {
    DM_OPT_DOWNSTREAM_PROPERTY_POST_REPLY,
    DM_OPT_DOWNSTREAM_EVENT_POST_REPLY,
    DM_OPT_UPSTREAM_PROPERTY_SET_REPLY,
    DM_OPT_UPSTREAM_EVENT_NOTIFY_REPLY
} dm_opt_t;

typedef struct {
    int prop_post_reply_opt;
    int event_post_reply_opt;
    int prop_set_reply_opt;
    int event_notify_reply_opt;
} dm_opt_ctx;

int dm_opt_set(dm_opt_t opt, void *data);
int dm_opt_get(dm_opt_t opt, void *data);

#endif
