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
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <ulog/ulog.h>

#ifndef PROJECT_SW_VERSION
#define PROJECT_SW_VERSION 0x00010000
#endif

#define TAG "OTA_VERSION"

static int version_char_to_u32(char *ver_str, unsigned int *version)
{
    int v1 = 0, v2 = 0, v3 = 0;
    if (*ver_str == 'v') {
        sscanf(ver_str, "v%d.%d.%d", &v1, &v2, &v3);
    } else {
        sscanf(ver_str, "%d.%d.%d", &v1, &v2, &v3);
    }
    *version = (v1 << 16) | (v2 << 8) | (v3);
    return 0;
}

extern char *aos_get_app_version(void);

unsigned int ota_version_appver_get(void)
{
    unsigned int version     = 0;
    int          ret         = 0;
    char *       version_str = aos_get_app_version();
    if (!version_str) {
        LOGE(TAG, "get version failed\r\n");
    }
    ret = version_char_to_u32(version_str, &version);
    if (ret < 0) {
        LOGE(TAG, "trans version failed %d\r\n", ret);
        return 0;
    }
    return version;
}
