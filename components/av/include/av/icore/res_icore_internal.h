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

#ifndef __RES_ICORE_INTERNAL_H__
#define __RES_ICORE_INTERNAL_H__

#include "av/icore/icore_msg.h"

__BEGIN_DECLS__

#ifdef CONFIG_CHIP_PANGU
#define RES_ICORE_AP_IDX          (0)
#define RES_ICORE_CP_IDX          (1)
#else
#define RES_ICORE_AP_IDX          (1)
#define RES_ICORE_CP_IDX          (2)
#endif

#define IPC_CMD_RES_ICORE         (58)
#define RES_ICORE_IPC_SERIVCE_ID  (0x13)

enum {
    ICORE_CMD_RES_INVALID,
    ICORE_CMD_RES_NEW,
    ICORE_CMD_RES_GET_OSAMPLES,
    ICORE_CMD_RES_CONVERT,
    ICORE_CMD_RES_FREE,
};

typedef struct {
    uint32_t          irate;
    uint32_t          orate;
    uint8_t           bits;
    uint8_t           channels;
    void              *r;      // resp: resx_t
} res_icore_new_t;

typedef struct {
    uint32_t          irate;
    uint32_t          orate;
    size_t            nb_isamples;
} res_icore_getosa_t;

typedef struct {
    void              *r;
    void              *in;
    void              *out;
    size_t            nb_isamples;
    size_t            nb_osamples;
} res_icore_convert_t;

typedef struct {
    void      *r;
} res_icore_free_t;

__END_DECLS__

#endif /* __RES_ICORE_INTERNAL_H__ */

