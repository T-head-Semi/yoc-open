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

#ifndef __PATH_H__
#define __PATH_H__

#include "av/avutil/common.h"

__BEGIN_DECLS__

/**
 * @brief  get the file extension
 * @param  [in] filename
 * @return NULL when err
 */
const char *get_extension(const char *filename);

/**
 * @brief  get basename from the path
 * @param  [in] path
 * @return NULL when err
 */
const char *path_basename(const char *path);

__END_DECLS__

#endif
