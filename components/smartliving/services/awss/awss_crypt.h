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

#ifndef __AWSS_CRYPT_H__
#define __AWSS_CRYPT_H__

enum {
    SEC_LVL_OPEN = 0,       // open
    SEC_LVL_AES256,         // AES256
    SEC_LVL_AES128_DEFAULT, // AES128 with default key
    SEC_LVL_AES128_PRODUCT, // AES128 with key from product_sec
    SEC_LVL_AES128_DEVICE,  // AES128 with key from device_sec
    SEC_LVL_AES128_MANU,    // AES128 with key from manufacturer_sec
};

int aes_decrypt_string(char *cipher, char *plain, int len, int cipher_hex, int sec_lvl, char cbc, const char *rand);

#endif
