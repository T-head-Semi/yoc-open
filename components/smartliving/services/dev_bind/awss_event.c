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

#include "iot_import.h"
#include "iot_export.h"
#include "sdk-impl_internal.h"

#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

int awss_event_post(int event)
{
    int ret = 0;
    void *cb = NULL;

    ret = iotx_event_post(event);

    cb = (void *)iotx_event_callback(ITE_AWSS_STATUS);
    if (cb)
        ret = ((int (*)(int))cb)(event);

    return ret;
}

#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
}
#endif
