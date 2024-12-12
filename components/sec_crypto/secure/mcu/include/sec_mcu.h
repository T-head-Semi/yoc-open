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


#ifndef __SC_SEC_MCU_H_
#define __SC_SEC_MCU_H_

#include <sec_crypto_platform.h>
#include <sec_crypto_memprot.h>
#include <sec_crypto_aes.h>
#include <sec_crypto_sha.h>
#include <sec_crypto_rsa.h>


int sc_mpu_set_memory_attr(uint32_t region_addr, int region_size, enum region_access_perm rap);

#endif