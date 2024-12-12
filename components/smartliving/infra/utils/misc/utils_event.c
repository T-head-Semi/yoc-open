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




#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static void *g_event_monitor = NULL;

int iotx_event_regist_cb(void (*monitor_cb)(int event))
{
    g_event_monitor = monitor_cb;
    return 0;
}

int iotx_event_post(int event)
{
    if (g_event_monitor == NULL)
        return -1;
    ((void (*)(int))g_event_monitor)(event);
    return 0;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
