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


#ifndef __SEC_CRYPTO_COMMON_H__
#define __SEC_CRYPTO_COMMON_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sec_crypto_rsa.h"

#define SC_lOG(...)

#ifndef CHECK_PARAM
#define CHECK_PARAM(x, ret) \
	do { \
		if (!(x)) { \
			return ret; \
		}\
	} while (0)

#endif /* CHECK_PARAM */

#ifndef CHECK_RET_WITH_RET
#define CHECK_RET_WITH_RET(x, ret) \
	do { \
		if (!(x)) { \
			return ret; \
		}\
	} while (0)
#endif /* CHECK_RET_WITH_RET */


void sc_common_set_key_bits(sc_rsa_t *rsa, sc_rsa_context_t *context);
#endif /* __SEC_CRYPTO_COMMON_H__ */