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
#include <update.h>
#include "update_diff.h"

int diff_test_fun(uint32_t oimg_addr, uint32_t oimg_size , uint32_t oimg_max_size, uint32_t diff_img_addr, uint32_t diff_img_size)
{

    SFB_LOG_I("test write\n");

    if (diff_updata_img(oimg_addr, oimg_size, oimg_max_size, diff_img_addr, diff_img_size))
        //if(diff_updata_img(0x1000bc00, 98972, 130000, 0x10031400, 29388))
    {
        SFB_LOG_I("e diff patch\n");
        return -1;
    } else {
        SFB_LOG_I("succ patch\n");
        return 0;
    }

}
