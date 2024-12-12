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

#ifndef __AWSS_CONNECT_AP_H__
#define __AWSS_CONNECT_AP_H__

#include "awss_log.h"
#include "passwd.h"

#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif
#define AWSS_TOKEN_LEN       (16)

int awss_complete_token(char passwd[HAL_MAX_PASSWD_LEN], uint8_t *bssid, uint8_t bssid_len, 
                        uint8_t *token_in, uint8_t token_len, uint8_t token_out[AWSS_TOKEN_LEN]);
/**
 * @brief do AP diagnosis, to find out AP connection fail details
 * 
 * @param [in] p_ap_ssid: AP ssid to diagnosis
 *
 * @retval  0 : diagnosis done
 * @note
 *        after awss_connect invoked and AP connect fail, should invoke
 *        this function to do AP diagnosis
 */
int awss_ap_diagnosis(char *p_ap_ssid);

int awss_connect(char ssid[HAL_MAX_SSID_LEN], char passwd[HAL_MAX_PASSWD_LEN], uint8_t *bssid, uint8_t bssid_len, 
                uint8_t *token, uint8_t token_len, bind_token_type_t token_type);

#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
}
#endif

#endif
