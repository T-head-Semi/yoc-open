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
#ifndef _RTC_ALARM_H_
#define _RTC_ALARM_H_

#include <aos/aos.h>

/**
 * 初始化rtc
 *
 * @param[in]  无
 *
 * @return  无.
 */
void rtc_init(void);

/**
 * 系统时间同步到rtc
 *
 * @param[in]  无
 *
 * @return  无.
 */
void rtc_from_system(void);

/**
 * rtc时间同步到系统
 *
 * @param[in]  无
 *
 * @return  无.
 */
void rtc_to_system(void);

/**
 * 获取rtc的绝对时间
 *
 * @param[in]  无
 *
 * @return  rtc绝对时间.
 */
time_t rtc_get_time(void);

/**
 * 设置rtc的绝对时间
 *
 * @param[in]  tm_set
 *
 * @return  无.
 */
void rtc_set_time(struct tm *tm_set);

/**
 * 设置及使能rtc
 *
 * @param[in]  tm_set
 * 
 *
 * @return  无.
 */
void rtc_set_alarm(struct tm *tm_set);

#endif
