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



#include <stdlib.h>
#include "os.h"
#include "awss_timer.h"

#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

int awss_stop_timer(void *timer)
{
    if (timer == NULL)
        return 0;
    HAL_Timer_Stop(timer);
    HAL_Timer_Delete(timer);
    return 0;
}
#if 0
int awss_start_timer(void **timer, const char *name, void *func, void *user_data, int ms)
{
    if (timer == NULL)
        return -1;
    *timer = HAL_Timer_Create(name, (void (*)(void *))func, user_data);
    if (*timer == NULL)
        return -1;
    HAL_Timer_Stop(*timer);
    HAL_Timer_Start(*timer, ms);
    return 0;
}
#endif
#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
}
#endif
