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
#ifndef __BOOTABLOG_H__
#define __BOOTABLOG_H__

#ifdef AOS_COMP_ULOG
#include <ulog/ulog.h>

#define TAG "[BOOTAB]"
#define BABLOGE(fmt, args...)  LOGE(TAG, fmt, ##args)

#define BABLOGI(fmt, args...)  LOGI(TAG, fmt, ##args)

#define BABLOGD(fmt, args...)  LOGD(TAG, fmt, ##args)

#define BABLOGW(fmt, args...)  LOGW(TAG, fmt, ##args)

#else

#include <stdio.h>

#define LOG_TAG "[BOOTAB]"
#ifdef CONFIG_DEBUG
#if CONFIG_DEBUG == 3
#define BABLOGD(format, ...) printf(LOG_TAG"[D] " "[%s:%d]" format "\r\n", __func__, __LINE__, ##__VA_ARGS__)
#define BABLOGI(format, ...) printf(LOG_TAG"[I] " "[%s:%d]" format "\r\n", __func__, __LINE__, ##__VA_ARGS__)
#define BABLOGW(format, ...) printf(LOG_TAG"[W] " "[%s:%d]" format "\r\n", __func__, __LINE__, ##__VA_ARGS__)
#define BABLOGE(format, ...) printf(LOG_TAG"[E] " "[%s:%d]" format "\r\n", __func__, __LINE__, ##__VA_ARGS__)
#elif CONFIG_DEBUG == 2
#define BABLOGD(format, ...)
#define BABLOGI(format, ...) printf(LOG_TAG"[I] " "[%s:%d]" format "\r\n", __func__, __LINE__, ##__VA_ARGS__)
#define BABLOGW(format, ...)
#define BABLOGE(format, ...) printf(LOG_TAG"[E] " "[%s:%d]" format "\r\n", __func__, __LINE__, ##__VA_ARGS__)
#elif CONFIG_DEBUG == 1
#define BABLOGD(format, ...)
#define BABLOGI(format, ...)
#define BABLOGW(format, ...)
#define BABLOGE(format, ...) printf(LOG_TAG"[E] " "[%s:%d]" format "\r\n", __func__, __LINE__, ##__VA_ARGS__)
#else
#define BABLOGD(format, ...)
#define BABLOGI(format, ...)
#define BABLOGW(format, ...)
#define BABLOGE(format, ...)
#endif
#else
#define BABLOGD(format, ...)
#define BABLOGI(format, ...)
#define BABLOGW(format, ...)
#define BABLOGE(format, ...)
#endif

#endif /*AOS_COMP_ULOG*/

#endif
