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

#ifndef __OGG_RW_H__
#define __OGG_RW_H__

#include "av/avutil/sf.h"
#include "av/avutil/av_typedef.h"

__BEGIN_DECLS__

#define OGG_HDR_LEN            (27)
#define OGG_NB_SEG_MAX         (255)

/* page type */
#define IS_SAME_PAGE(type)     ((type) == 0x1)
#define IS_FIRST_PAGE(type)    ((type) == 0x2)
#define IS_LAST_PAGE(type)     ((type) == 0x4)

struct page_hdr {
    uint8_t                    version;
    uint8_t                    type;
    uint64_t                   granule;
    uint32_t                   serial_nb;
    uint32_t                   seq_nb;
    uint32_t                   crc;
    uint8_t                    nb_segs;
};

/**
 * @brief  find codec support for ogg-format now
 * @param  [in] buf
 * @param  [in] size
 * @return AVCODEC_ID_UNKNOWN on error
 */
avcodec_id_t ogg_find_codec(const uint8_t *buf, size_t size);

/**
 * @brief  get ogg header info
 * @param  [in] buf
 * @param  [in] hinfo
 * @return 0/-1
 */
int page_hdr_get(const uint8_t buf[OGG_HDR_LEN], struct page_hdr *hinfo);

/**
 * @brief  sync the ogg
 * @param  [in] rcb        : read byte callback
 * @param  [in] opaque     : in param of the callback * @param  [in] sync_max   : max of the sync count
 * @param  [in/out] hdr[OGG_HDR_LEN] : hdr of the ogg
 * @param  [in/out] hinfo
 * @return -1 on error or read byte count for sync
 */
int ogg_page_sync(read_bytes_t rcb, void *opaque, size_t sync_max, uint8_t hdr[OGG_HDR_LEN], struct page_hdr *hinfo);

__END_DECLS__

#endif /* __OGG_RW_H__ */

