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

#ifndef __COAP_PLATFORM_OS_H__
#define __COAP_PLATFORM_OS_H__

#include <stdio.h>
#include "iotx_utils.h"
#include "iotx_log.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define COAP_ERR(...)           log_err("coap_local", __VA_ARGS__)
#define COAP_WRN(...)           log_warning("coap_local", __VA_ARGS__)
#define COAP_INFO(...)          log_info("coap_local", __VA_ARGS__)

#define COAP_TRC(...)           log_debug("coap_local", __VA_ARGS__)
#define COAP_DUMP(...)          log_debug("coap_local", __VA_ARGS__)
#define COAP_DEBUG(...)         log_debug("coap_local", __VA_ARGS__)
#define COAP_FLOW(...)          log_debug("coap_local", __VA_ARGS__)


#ifdef TEST_COAP_MEMORY
extern void* mymalloc(int size, char* file, int line);
extern void myfree(void* ptr, char* file, int line);
#define coap_malloc(size)  mymalloc(size,__FILE__,__LINE__) 
#define coap_free(ptr) myfree(ptr,__FILE__,__LINE__)
#else
#define coap_malloc(size)       LITE_malloc(size, MEM_MAGIC, "coap.local")
#define coap_free(ptr)          LITE_free(ptr)
#endif

int platform_is_multicast(const char *ip_str);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
