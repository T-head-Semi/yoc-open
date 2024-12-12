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

/*
DESCRIPTION
This file provides method to find the least/most significant bit in 32 bit
fields.
*/

#include "k_api.h"
#include "k_ffs.h"
#include "k_bitmap.h"

/* find most significant bit set */

int ffs32_msb(uint32_t bitmap)
{
    if (bitmap == 0)
        {
        return 0;
        }

    return 32 - krhino_bitmap_first(&bitmap);
}


/* find least significant bit set */

int ffs32_lsb(uint32_t bitmap)
{
    uint32_t x;
    int      lsbit;

    if (bitmap == 0) 
        {
        return 0;
        }

    x = bitmap & -bitmap;
    lsbit = krhino_bitmap_first((uint32_t *)(&x));

    return 32 - lsbit;
}

