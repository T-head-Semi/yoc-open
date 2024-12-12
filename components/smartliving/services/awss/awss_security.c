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

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "os.h"
#include "awss_utils.h"
#include "sha256.h"
#include "passwd.h"
#include "awss_wifimgr.h"

#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

int softap_decrypt_password(const char *cipher, const uint8_t *random, char *passwd)
{
    uint8_t cipher_hex[PLATFORM_MAX_PASSWD_LEN] = {0};
    uint8_t aes_key[SHA256_DIGEST_SIZE + 1] = {0};
    uint8_t iv[AES128_KEY_LEN] = {0};
    p_aes128_t aes_ctx = NULL;

    if (strlen(cipher) == 0) //Passwd is empty
    {
        passwd = "";
        return 0;
    }

    /* get cipher hex */
    utils_str_to_hex((char *)cipher, PLATFORM_MAX_PASSWD_LEN * 2, cipher_hex, PLATFORM_MAX_PASSWD_LEN);

    /* setup iv */
    utils_str_to_hex((char *)random, RANDOM_MAX_LEN * 2, iv, RANDOM_MAX_LEN);

    /* generate aes key */
    utils_sha256(random, RANDOM_MAX_LEN * 2, aes_key);

    /* aes decryption with cbc mode */
    aes_ctx = os_aes128_init((const uint8_t *)aes_key, iv, PLATFORM_AES_DECRYPTION);
    os_aes128_cbc_decrypt(aes_ctx, cipher_hex, sizeof(cipher_hex) / AES128_KEY_LEN, passwd);
    os_aes128_destroy(aes_ctx);

    return 0;
}

#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
}
#endif
