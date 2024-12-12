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

#ifndef KEY_MGR_PARSER_H_
#define KEY_MGR_PARSER_H_

#include <ctype.h>
#include <stdint.h>
#include <string.h>
#include <key_mgr.h>

#define TRUST_BOOT_PUBKEY_N_SIZE    128
#define TRUST_BOOT_PUBKEY_E_SIZE    128

#define KP_OK             0
#define KP_ERR_MAGIC_NUM -1
#define KP_ERR_NOT_FOUND -2
#define KP_ERR_VERSION   -3
#define KP_ERR_NULL      -4
#define KP_ERR_POS_TYPE  -5
#define KP_ERR_KEY_SIZE  -6
#define KP_ERR_KEY_TYPE  -7



uint32_t parser_init(void);

/**
  \brief       Update KP infomation .
  \param[in]   kp_info  A pointer to the kp information buffer
  \param[in]   key_size  The size of kp information
*/
uint32_t parser_update_kp(uint8_t *kp_info, size_t size);

/**
  \brief       Get KP raw data .
  \param[in]   kp_in  A pointer to the kp information buffer
  \param[in]   kp_in_size  The size of kp information
  \param[out]   key_out  A pointer to the kp raw data buffer
  \param[out]   key_size A pointer to the size of kp raw data
*/
uint32_t parser_get_kp_raw_data(uint8_t *kp_in, uint32_t kp_in_size, uint8_t *key_out, uint32_t *key_out_size);

/**
  \brief       TEE get key from kp
  \param[in]   key_type  key type,see \ref key_type_e
  \param[out]  key     Pointer to key
  \return      return key size if > 0, else error code
*/
uint32_t parser_get_key(km_key_type_e key_type, key_handle *key, uint32_t *key_size);

/**
  \brief       TEE get kp version
  \return      return kp version if > 0, else error code
*/
int parser_version();

/**
  \brief       TEE get manifest address
  \param[out]  addr  manifest address
  \return      return KP_OK if success, else error code
*/
int parser_get_manifest_addr(uint32_t *addr);


#endif
