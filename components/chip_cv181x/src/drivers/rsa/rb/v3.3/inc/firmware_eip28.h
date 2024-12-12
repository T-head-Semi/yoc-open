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


#include "stdint.h"
#include "cs_eip28.h"

typedef struct firmware_eip28 {
    uint32_t Version_MaMiPa;
    uint32_t *Image_p;
    uint32_t WordCount;
} Firmware_EIP28_t;


/*----------------------------------------------------------------------------
 * Firmware_EIP28_GetReferences
 *
 * This function returns references to the firmware images required by
 * EIP28 Driver Library.
 */
void
Firmware_EIP28_GetReferences(
        Firmware_EIP28_t * const FW_p);