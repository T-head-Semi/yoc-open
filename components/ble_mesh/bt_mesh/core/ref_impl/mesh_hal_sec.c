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

#include <errno.h>
#include <stddef.h>
#include <bluetooth/bluetooth.h>
#include <port/mesh_hal_sec.h>

#ifndef CONFIG_BT_MESH_STACK_ALONE
#include <crypto.h>
#include <tinycrypt/constants.h>
#include <tinycrypt/utils.h>
#include <tinycrypt/aes.h>
#include <tinycrypt/cmac_mode.h>
#include <tinycrypt/ccm_mode.h>

int bt_mesh_rand(void *buf, size_t len)
{
    return bt_rand(buf, len);
}

int bt_mesh_aes_encrypt(const uint8_t key[16], const uint8_t plaintext[16],
                        uint8_t enc_data[16])
{
    return bt_encrypt_be(key, plaintext, enc_data);
}

int bt_mesh_aes_decrypt(const uint8_t key[16], const uint8_t enc_data[16],
                        uint8_t dec_data[16])
{
    return bt_decrypt_be(key, enc_data, dec_data);
}

#endif
