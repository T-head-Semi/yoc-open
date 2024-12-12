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
#include <string.h>
#include "av/avutil/path.h"

/**
 * @brief  get the file extension
 * @param  [in] filename
 * @return NULL when err
 */
const char *get_extension(const char *filename)
{
    const char *ext;

    if (filename) {
        ext = filename + strlen(filename) - 1;
        while (ext >= filename && *ext != '/') {
            if (*ext == '.') {
                ext++;
                return ext;
            }
            ext--;
        }
    }

    return NULL;
}

/**
 * @brief  get basename from the path
 * @param  [in] path
 * @return NULL when err
 */
const char *path_basename(const char *path)
{
    if (path) {
        const char *f;

        f = strrchr(path, '/');

        return f ? f + 1 : path;
    }

    return NULL;
}


