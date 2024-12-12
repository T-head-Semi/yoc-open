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

#ifndef CONFIG_SEC_CRYPTO_MAC_SW
#include <sec_crypto_errcode.h>
#include <sec_crypto_mac.h>
#include <se_hmac.h>
#include "sec_crypto_common.h"

/**
  \brief       Initialize SHA Interface. Initializes the resources needed for the SHA interface
*/
uint32_t sc_mac_init(sc_mac_t *mac, uint32_t idx)
{
    int ret;

    ret = se_hmac_init(&mac->se_hmac);
    if (ret) {
        return SC_DRV_FAILED;
    }

    return SC_OK;
}

/**
  \brief       De-initialize SHA Interface. stops operation and releases the software resources used by the interface
*/
void sc_mac_uninit(sc_mac_t *mac)
{
    if (mac) {
		se_hmac_uninit(&mac->se_hmac);
        memset(mac, 0, sizeof(sc_sha_t));
    }
}

/**
  \brief       MAC      set key function.
*/
uint32_t sc_mac_set_key(sc_mac_t *mac, uint8_t *key, uint32_t key_len)
{
    int ret;

	ret = se_hmac_set_key(&mac->se_hmac, key, key_len);
    if (ret) {
        return SC_DRV_FAILED;
    }

    return SC_OK;

}
/**
  \brief       MAC operation function.
*/
uint32_t sc_mac_calc(sc_mac_t *mac, sc_sha_mode_t mode, uint8_t *msg,
		     uint32_t msg_len, uint8_t *out, uint32_t *out_len)
{
    int ret;

	ret = se_hmac_calc(&mac->se_hmac, mode, msg,
             msg_len, out, out_len);
    if (ret) {
        return SC_DRV_FAILED;
    }

    return SC_OK;
}


/**
  \brief       MAC start operation function.
*/
uint32_t sc_mac_start(sc_mac_t *mac, sc_mac_context_t *context, sc_sha_mode_t mode)
{
	return SC_NOT_SUPPORT;
}

/**
  \brief       MAC start operation function.
*/
uint32_t sc_mac_update(sc_mac_t *mac, sc_mac_context_t *context, uint8_t *msg, uint32_t msg_len)
{
	return SC_NOT_SUPPORT;
}

/**
  \brief       MAC start operation function.
*/
uint32_t sc_mac_finish(sc_mac_t *mac, sc_mac_context_t *context, uint8_t *out, uint32_t *out_len)
{
	return SC_NOT_SUPPORT;
}

#endif