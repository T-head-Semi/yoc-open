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

#include "av/avutil/av_errno.h"

static int _av_errno;

/**
 * @brief  set the global errno for av, ugly for special use(xiaoya, etc)
 * @param  [in] errno
 * @return
 */
void av_errno_set(int errno)
{
    _av_errno = errno;
}

/**
 * @brief  get the global av errno on play errno.
 * attention: this av-errno is not accurate, just for statistic-online
 * @return AV_ERRNO_XXX
 */
int av_errno_get()
{
    return _av_errno;
}


