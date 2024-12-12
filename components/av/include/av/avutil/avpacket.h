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

#ifndef __AV_PACKET_H__
#define __AV_PACKET_H__

#include "av/avutil/common.h"
#ifdef __linux__
#include "aos_port/list.h"
#endif

__BEGIN_DECLS__

typedef struct avpacket {
    uint8_t                           *data;
    int32_t                           size;      ///< total capcity
    int32_t                           len;       ///< length of avilable data
    int64_t                           pts;
    slist_t                           node;
} avpacket_t;

/**
 * @brief  init the packet
 * @param  [in] pkt
 * @return 0/-1
 */
int avpacket_init(avpacket_t *pkt);

/**
 * @brief  malloc resource of the packet
 * @param  [in] pkt
 * @param  [in] size
 * @return 0/-1
 */
int avpacket_new(avpacket_t *pkt, size_t size);

/**
 * @brief  grow the packet data size
 * @param  [in] pkt
 * @param  [in] size
 * @return 0/-1
 */
int avpacket_grow(avpacket_t *pkt, size_t size);

/**
 * @brief  copy the src pkt to dsp pkt
 * @param  [in] spkt : src pkt
 * @param  [in] dpkt : dst pkt
 * @return 0/-1
 */
int avpacket_copy(const avpacket_t *spkt, avpacket_t *dpkt);

/**
 * @brief  free resource of the packet
 * @param  [in] pkt
 * @return
 */
int avpacket_free(avpacket_t *pkt);

__END_DECLS__

#endif /* __AV_PACKET_H__ */

