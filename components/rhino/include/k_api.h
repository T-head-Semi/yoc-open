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

#ifndef K_API_H
#define K_API_H

/** @addtogroup rhino API
 *  All rhino header files.
 *
 *  @{
 */

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

#include "k_config.h"
#include "k_default_config.h"

#include "k_types.h"
#include "k_err.h"
#include "k_sys.h"
#include "k_critical.h"
#include "k_spin_lock.h"
#include "k_list.h"
#if (RHINO_CONFIG_SCHED_CFS > 0)
#include "k_cfs.h"
#endif
#include "k_obj.h"
#include "k_sched.h"
#include "k_task.h"
#include "k_ringbuf.h"
#include "k_queue.h"
#include "k_buf_queue.h"
#include "k_sem.h"
#include "k_task_sem.h"
#include "k_mutex.h"
#include "k_timer.h"
#include "k_time.h"
#include "k_event.h"
#include "k_stats.h"
#if RHINO_CONFIG_MM_DEBUG
#include "k_mm_debug.h"
#endif
#include "k_mm_blk.h"
#include "k_mm_region.h"
#include "k_mm.h"
#include "k_workqueue.h"

#include "k_internal.h"
#include "k_trace.h"
#include "k_soc.h"
#include "k_hook.h"
#include "k_bitmap.h"

#include "port.h"

/** @} */

#endif /* K_API_H */

