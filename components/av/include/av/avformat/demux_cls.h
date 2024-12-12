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

#ifndef __DEMUX_CLS_H__
#define __DEMUX_CLS_H__

#include "av/avutil/av_config.h"
#include "av/avutil/av_typedef.h"
#include "av/avutil/avpacket.h"
#include "av/stream/stream_cls.h"
#include "av/avformat/avparser_cls.h"

__BEGIN_DECLS__

typedef struct demux_cls demux_cls_t;

typedef struct avprobe_data {
#define AVPROBE_SCORE_GUESS     (50)
#define AVPROBE_SCORE_EXTENSION (60)
#define AVPROBE_SCORE_MIME      (75)
#define AVPROBE_SCORE_NAME      (80)
#define AVPROBE_SCORE_AGAIN     (85)         ///< next frame(not need sync) probe ok
#define AVPROBE_SCORE_MAX       (100)
    uint8_t                     *buf;
    int32_t                     buf_size;
    const char                  *filename;
    char                        avformat[16];
} avprobe_data_t;

struct demux_ops {
#define MAX_EXTENTSIONS (5)
    const char                  *name;
    uint8_t                     type;
    const char                  *extensions[MAX_EXTENTSIONS];

    int      (*read_probe)      (const avprobe_data_t *pd);

    int      (*open)            (demux_cls_t *o);
    int      (*read_packet)     (demux_cls_t *o, avpacket_t *pkt);
    int      (*seek)            (demux_cls_t *o, uint64_t timestamp);
    int      (*control)         (demux_cls_t *o, int cmd, void *arg, size_t *arg_size);
    int      (*close)           (demux_cls_t *o);
};

struct demux_cls {
    stream_cls_t                *s;
    sh_audio_t                  ash;
    aos_mutex_t                 lock;
    avpacket_t                  fpkt;          ///< reserved, the first packet for mp3, etc
    size_t                      id3v2size;     ///< TODO:
    uint64_t                    bps;
    size_t                      time_scale;    ///< only for audio
    uint64_t                    duration;      ///< only for audio, ms
    track_info_t                *tracks;       ///< TODO: need call tracks_info_freep when unused

    avparser_t                  *psr;
    slist_t                     list_free;     ///< free avpacket_list for psr
    slist_t                     list_ready;    ///< ready avpacket_list for psr

    void                        *priv;
    const struct demux_ops      *ops;
};

__END_DECLS__

#endif /* __DEMUX_CLS_H__ */

