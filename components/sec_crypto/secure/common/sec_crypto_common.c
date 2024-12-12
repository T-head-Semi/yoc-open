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

#include <stdint.h>
#include <sec_crypto_errcode.h>
#include "sec_crypto_common.h"
#include "sec_crypto_rsa.h"

void sc_common_set_key_bits(sc_rsa_t *rsa, sc_rsa_context_t *context)
{
        switch (rsa->bits) {
                case SC_RSA_KEY_BITS_1024:
                        context->key_bits = 1024;
                        break;
                case SC_RSA_KEY_BITS_2048:
                        context->key_bits = 2048;
                        break;
                /* set later */
                case 0:
                        break;
                default:
                        context->key_bits = 0;
                        return;
        }
}