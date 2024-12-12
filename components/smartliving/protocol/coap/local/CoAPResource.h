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




#ifndef __COAP_RESOURCE_H__
#define __COAP_RESOURCE_H__

#include <stdint.h>
#include "lite-list.h"
#include "CoAPExport.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define COAP_MAX_PATH_CHECKSUM_LEN (5)


typedef struct {
    unsigned short           permission;
    CoAPRecvMsgHandler       callback;
    unsigned int             ctype;
    unsigned int             maxage;
    struct list_head         reslist;
    char                     path[COAP_MAX_PATH_CHECKSUM_LEN];
    char                     *filter_path;
    path_type_t              path_type;
} CoAPResource;

int CoAPResource_init(CoAPContext *context, int res_maxcount);

int CoAPPathMD5_sum(const char *path, int len, char outbuf[], int outlen);

int CoAPResource_register(CoAPContext *context, const char *path,
                          unsigned short permission, unsigned int ctype,
                          unsigned int maxage, CoAPRecvMsgHandler callback);
#ifdef DEVICE_MODEL_GATEWAY 
int CoAPResource_unregister(CoAPContext *context, const char *path);
#endif
CoAPResource *CoAPResourceByPath_get(CoAPContext *context, const char *path);

int CoAPResource_deinit(CoAPContext *context);

int CoAPResource_topicFilterMatch(const char *filter, const char *topic);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
