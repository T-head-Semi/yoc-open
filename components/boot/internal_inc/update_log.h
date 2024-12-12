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
#ifndef UPDATE_LOG_H_
#define UPDATE_LOG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>

#undef LOG_TAG
#define LOG_TAG "[boot]"

#ifdef CONFIG_DEBUG
#if CONFIG_DEBUG == 3
#define UPD_LOGD(format, ...) printf(LOG_TAG"[D] "format"\r\n",##__VA_ARGS__)
#define UPD_LOGI(format, ...) printf(LOG_TAG"[I] "format"\r\n",##__VA_ARGS__)
#define UPD_LOGW(format, ...) printf(LOG_TAG"[W] "format"\r\n",##__VA_ARGS__)
#define UPD_LOGE(format, ...) printf(LOG_TAG"[E] "format"\r\n",##__VA_ARGS__)
#elif CONFIG_DEBUG == 2
#define UPD_LOGD(format, ...)
#define UPD_LOGI(format, ...) printf(LOG_TAG"[I] "format"\r\n",##__VA_ARGS__)
#define UPD_LOGW(format, ...)
#define UPD_LOGE(format, ...) printf(LOG_TAG"[E] "format"\r\n",##__VA_ARGS__)
#elif CONFIG_DEBUG == 1
#define UPD_LOGD(format, ...)
#define UPD_LOGI(format, ...)
#define UPD_LOGW(format, ...)
#define UPD_LOGE(format, ...) printf(LOG_TAG"[E] "format"\r\n",##__VA_ARGS__)
#else
#define UPD_LOGD(format, ...)
#define UPD_LOGI(format, ...)
#define UPD_LOGW(format, ...)
#define UPD_LOGE(format, ...)
#endif
#else
#define UPD_LOGD(format, ...)
#define UPD_LOGI(format, ...)
#define UPD_LOGW(format, ...)
#define UPD_LOGE(format, ...)
#endif

#ifdef __cplusplus
}
#endif

#endif /* UPDATE_LOG_H_ */
