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
/* cs_eip28_ext.h
 *
 * EIP-28 hardware specific EIP-28 Driver Library configuration parameters:
 * EIP-28 hardware in the FPGA host HW platform
 *
 */



#ifndef INCLUDE_GUARD_CS_EIP28_EXT_H
#define INCLUDE_GUARD_CS_EIP28_EXT_H

/* Use this option to remove the capability register check.
   This register is present in this EIP-28 hardware */
//#define EIP28_REMOVE_EIPNR_CHECK

/* Use this to remove firmware download.
   Some EIP-28 hardware versions have firmware in ROM. */
//#define EIP28_REMOVE_FIRMWARE_DOWNLOAD


#endif /* Include Guard */


/* end of file cs_eip28_ext.h */
