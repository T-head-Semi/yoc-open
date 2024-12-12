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

#ifndef DBG_API_H
#define DBG_API_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "debug_infoget.h"
#include "debug_overview.h"
#include "debug_panic.h"
#include "debug_backtrace.h"
#include "debug_print.h"
#include "debug_test.h"
#include "debug_cli_cmd.h"
#include "debug_dumpsys.h"
#include "debug_cpuusage.h"

#ifdef CONFIG_KERNEL_RHINO
#include "k_api.h"
#endif

#if DEBUG_LAST_WORD_ENABLE
#include "debug_lastword.h"
#endif

/* system reboot reason description */
#define DEBUG_REBOOT_REASON_WD_RST    0x01 /**< Watchdog reset */
#define DEBUG_REBOOT_REASON_PANIC     0x02 /**< System panic */
#define DEBUG_REBOOT_REASON_REPOWER   0x03 /**< System repower */
#define DEBUG_REBOOT_REASON_FATAL_ERR 0x04 /**< System fatal error */
#define DEBUG_REBOOT_CMD_REASON       0x05 /**< Reboot cmd */
#define DEBUG_REBOOT_UNKNOWN_REASON   0x06 /**< unknown reason */

#ifdef __cplusplus
}
#endif

#endif /* DBG_API_H */
