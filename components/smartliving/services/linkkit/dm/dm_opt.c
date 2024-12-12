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

#include "iotx_dm_internal.h"

static dm_opt_ctx g_dm_opt = {
    0, 0, 1
};

int dm_opt_set(dm_opt_t opt, void *data)
{
    int res = SUCCESS_RETURN;

    if (data == NULL) {
        return FAIL_RETURN;
    }

    switch (opt) {
        case DM_OPT_DOWNSTREAM_PROPERTY_POST_REPLY: {
            int opt = *(int *)(data);
            g_dm_opt.prop_post_reply_opt = opt;
        }
        break;
        case DM_OPT_DOWNSTREAM_EVENT_POST_REPLY: {
            int opt = *(int *)(data);
            g_dm_opt.event_post_reply_opt = opt;
        }
        break;
        case DM_OPT_UPSTREAM_PROPERTY_SET_REPLY: {
            int opt = *(int *)(data);
            g_dm_opt.prop_set_reply_opt = opt;
        }
        break;
        case DM_OPT_UPSTREAM_EVENT_NOTIFY_REPLY: {
            int opt = *(int *)(data);
            g_dm_opt.event_notify_reply_opt = opt;
        }
        break;
        default: {
            res = FAIL_RETURN;
        }
        break;
    }

    return res;
}

int dm_opt_get(dm_opt_t opt, void *data)
{
    int res = SUCCESS_RETURN;

    if (data == NULL) {
        return FAIL_RETURN;
    }

    switch (opt) {
        case DM_OPT_DOWNSTREAM_PROPERTY_POST_REPLY: {
            *(int *)(data) = g_dm_opt.prop_post_reply_opt;
        }
        break;
        case DM_OPT_DOWNSTREAM_EVENT_POST_REPLY: {
            *(int *)(data) = g_dm_opt.event_post_reply_opt;
        }
        break;
        case DM_OPT_UPSTREAM_PROPERTY_SET_REPLY: {
            *(int *)(data) = g_dm_opt.prop_set_reply_opt;
        }
        break;
        case DM_OPT_UPSTREAM_EVENT_NOTIFY_REPLY: {
            *(int *)(data) = g_dm_opt.event_notify_reply_opt;
        }
        break;
        default: {
            res = FAIL_RETURN;
        }
        break;
    }

    return res;
}
