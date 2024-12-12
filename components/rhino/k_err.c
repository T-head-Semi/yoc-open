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

#include "k_api.h"

#if defined (AOS_COMP_DEBUG) && AOS_COMP_DEBUG
#include "debug/dbg.h"
#endif

void k_err_proc_debug(kstat_t err, char *file, int line)
{
#if defined (AOS_COMP_DEBUG) && AOS_COMP_DEBUG
    aos_debug_fatal_error(err, file, line);
#endif

    if (g_err_proc != NULL) {
        g_err_proc(err);
    }
}
