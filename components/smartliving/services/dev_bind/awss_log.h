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

#ifndef __AWSS_LOG_H__
#define __AWSS_LOG_H__

#include "iotx_log.h"
#include <ulog/ulog.h>

#if 0
#define awss_flow(...)      log_flow("awss", __VA_ARGS__)
#define awss_debug(...)     log_debug("awss", __VA_ARGS__)
#define awss_info(...)      log_info("awss", __VA_ARGS__)
#define awss_warn(...)      log_warning("awss", __VA_ARGS__)
#define awss_err(...)       log_err("awss", __VA_ARGS__)
#define awss_crit(...)      log_crit("awss", __VA_ARGS__)
#define awss_emerg(...)     log_emerg("awss", __VA_ARGS__)
#define awss_trace(...)     log_crit("awss", __VA_ARGS__)
#endif


#if (CONFIG_BLDTIME_MUTE_DBGLOG)
#define awss_flow(...)
#define awss_info(...)
#define awss_debug(...)
#else
#define awss_flow(...)      ulog(AOS_LL_DEBUG, "awss", ULOG_TAG, __VA_ARGS__)
#define awss_debug(...)     ulog(AOS_LL_DEBUG, "awss", ULOG_TAG, __VA_ARGS__)
#define awss_info(...)      ulog(AOS_LL_INFO, "awss", ULOG_TAG, __VA_ARGS__)
#endif
#define awss_warn(...)      ulog(AOS_LL_WARN, "awss", ULOG_TAG, __VA_ARGS__)
#define awss_err(...)       ulog(AOS_LL_ERROR, "awss", ULOG_TAG, __VA_ARGS__)
#define awss_crit(...)      ulog(AOS_LL_FATAL, "awss", ULOG_TAG, __VA_ARGS__)
#define awss_emerg(...)     ulog(AOS_LL_FATAL, "awss", ULOG_TAG, __VA_ARGS__)
#define awss_trace(...)     ulog(AOS_LL_INFO, "awss", ULOG_TAG, __VA_ARGS__)


#endif
