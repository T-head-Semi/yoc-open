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

#ifndef __AD_ICORE_INTERNAL_H__
#define __AD_ICORE_INTERNAL_H__

#include "av/avutil/sf.h"
#include "av/avutil/avframe.h"
#include "av/avutil/avpacket.h"
#include "av/icore/icore_msg.h"
#include "ad_icore_typedef.h"

__BEGIN_DECLS__

#ifdef CONFIG_CHIP_PANGU
#define AD_ICORE_AP_IDX          (0)
#define AD_ICORE_CP_IDX          (1)
#else
#define AD_ICORE_AP_IDX          (1)
#define AD_ICORE_CP_IDX          (2)
#endif
#define IPC_CMD_AD_ICORE  (55)
#define AD_ICORE_IPC_SERIVCE_ID 0x10

enum {
    ICORE_CMD_AD_INVALID,
    ICORE_CMD_AD_OPEN,
    ICORE_CMD_AD_DECODE,
    ICORE_CMD_AD_RESET,
    ICORE_CMD_AD_CLOSE,
};

typedef struct {
    avcodec_id_t  id;
    adi_conf_t    adi_cnf;      // req

    void          *ad;          // resp: ad_cls_t
    sf_t          sf;           // resp:
} ad_icore_open_t;

typedef struct {
    void          *ad;          // ad_cls_t
} ad_icore_reset_t;

typedef struct {
    void          *ad;          // ad_cls_t
} ad_icore_close_t;

typedef struct {
    void              *ad;      // ad_cls_t
    uint8_t           *es_data;
    int32_t           es_len;
    avframe_t         frame;
    int               got_frame;
} ad_icore_decode_t;

__END_DECLS__

#endif /* __AD_ICORE_INTERNAL_H__ */

