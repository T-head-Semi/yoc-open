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
/* c_adapter_ext.h
 *
 * Internal Configuration File
 *
 * Extensions for the Security-IP-28 hardware.
 * This file is included from c_adapter.h
 */



// ensure inclusion from c_adapter.h only
#ifndef INCLUDE_GUARD_C_ADAPTER_EXT_H

// Physical interrupt source number used by Adapter
// for EIP-28 Data Ready interrupt
#ifndef ADAPTER_PHY_EIP28_READY_IRQ
#define ADAPTER_PHY_EIP28_READY_IRQ             1
#endif

// Logical interrupt number used by Adapter for EIP-28 Data Ready interrupt
#ifndef ADAPTER_EIP28_READY_IRQ
#define ADAPTER_EIP28_READY_IRQ                 1
#endif

// Name used by Adapter for EIP-28 Data Ready interrupt
#ifndef ADAPTER_EIP28_READY_INT_NAME
#define ADAPTER_EIP28_READY_INT_NAME            "EIP28_READY"
#endif

//#define ADAPTER_EIP28_INTERRUPT_ENABLE

#endif /* Include Guard */


/* end of file c_adapter_ext.h */
