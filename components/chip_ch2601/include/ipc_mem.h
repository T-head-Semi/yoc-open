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
 * @file     ipc_mem.h
 * @brief    header file for the ipc mem
 * @version  V1.0
 * @date     07. Aug 2019
 * @vendor   csky
 * @chip     pangu
 ******************************************************************************/
#ifndef _IPC_MEM_H_
#define _IPC_MEM_H_
#ifdef __cplusplus
extern "C" {
#endif
void drv_ipc_mem_init(void);
void *drv_ipc_mem_alloc(int *len);
void drv_ipc_mem_free(void *p);
int drv_ipc_mem_use_cache(void);
#ifdef __cplusplus
}
#endif
#endif /* _IPC_MEM_H_ */