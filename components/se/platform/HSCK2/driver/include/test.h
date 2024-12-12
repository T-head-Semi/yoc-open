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
/******************************************************************************
 * @file     test.h
 * @brief    Header File for RNG
 * @version  V1.0
 * @date     22. May 2023
 * @model    test
 ******************************************************************************/
#ifndef _TEST_H_
#define _TEST_H_


#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

/************/

//更新固件示例
void example_hs_UpdateFirmware(void);
//获取任意长度随机数示例,测试通过
void example_hs_rng_get_bytes(void);
//获取APP版本号示例,测试通过
void example_hs_GetAppVersion(void);
//通道测试示例,测试通过
void example_hs_SpiChannelTest(void);
//外部认证示例,测试通过
void example_hs_ExternalAuth(void);
//导入根密钥示例,测试通过
void example_hs_Import_rootkey(void);
//导入密钥加密密钥示例,测试通过
void example_hs_Import_key_encrypting_key(void);
//导入ECC密钥示例,测试通过
void example_hs_Import_ECCKey(void);
//ECC加密解密示例,测试通过
void example_hs_ECC_Decrypt_and_Encrypt(void);
//ECC签名验签示例,测试通过
void example_hs_ECC_Sign_and_Verify();
//导入RSA1024密钥示例
void example_hs_Import_RSA1024Key(void);
//RSA1024加密解密示例,测试通过
void example_hs_RSA1024_Decrypt_and_Encrypt(void);
//RSA1024签名验签示例,测试通过
void example_hs_RSA1024_Sign_and_Verify();
//导入RSA2048密钥示例
void example_hs_Import_RSA2048Key(void);
//导入AES密钥示例
void example_hs_Import_AESKey(void);





/************/

#ifdef __cplusplus
}
#endif

#endif /* _DRV_TEST_H_ */
