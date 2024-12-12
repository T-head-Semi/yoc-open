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

#ifndef __MP3_RW_H__
#define __MP3_RW_H__

#include "av/avutil/sf.h"
#include "av/avutil/av_typedef.h"

__BEGIN_DECLS__

#define MP3_HDR_LEN           (4)

struct mp3_hdr_info {
    uint8_t                   layer;
    uint8_t                   lsf;
    int                       spf; //sample per frame
    int                       bitrate;
    int                       framesize;
    sf_t                      sf;
};

/**
 * @brief  get mp3 header info
 * @param  [in] buf
 * @param  [in] hinfo
 * @return 0/-1
 */
int mp3_hdr_get(const uint8_t* buf, struct mp3_hdr_info *hinfo);

/**
 * @brief  sync the mp3
 * @param  [in] rcb        : read byte callback
 * @param  [in] opaque     : in param of the callback
 * @param  [in] sync_max   : max of the sync count
 * @param  [in/out] hdr[4] : hdr of the mp3
 * @param  [in/out] hinfo
 * @return -1 on error or read byte count for sync
 */
int mp3_sync(read_bytes_t rcb, void *opaque, size_t sync_max, uint8_t hdr[4], struct mp3_hdr_info *hinfo);

__END_DECLS__

#endif /* __MP3_RW_H__ */

