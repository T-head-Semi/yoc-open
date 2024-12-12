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

/******************************************************************************
 * @file     linpack_timer_port.h
 * @brief    the head file for the linpack
 * @version  V1.0
 * @date     20. July 2016
 ******************************************************************************/
#ifndef CORE_SYSTIMER_H_
#define CORE_SYSTIMER_H_

void Timer_Open();
void Timer_Start();
void Timer_Stop();
void Timer_Close();
unsigned long long  clock_gettime();
long    time();

#endif /* CORE_SYSTIMER_H_ */
