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

#include "smart_audio.h"
#include "ulog/ulog.h"
#include <aos/kv.h>

#define TAG "smtaudio_ctrl_online_music"

static int online_music_init(void);
static int online_music_deinit(void);
static int online_music_start(const char *url, uint64_t seek_time, int resume);
static int online_music_pause(void);
static int online_music_stop(void);
static int online_music_resume(void);

smtaudio_ops_node_t ctrl_online_music = {
    .name     = "online_music",
    .url      = NULL,
    .prio     = 2,
    .id       = SMTAUDIO_ONLINE_MUSIC,
    .status   = SMTAUDIO_STATE_STOP,
    .init     = online_music_init,
    .deinit   = online_music_deinit,
    .start    = online_music_start,
    .pause    = online_music_pause,
    .stop     = online_music_stop,
    .resume   = online_music_resume,
    .vol_get  = NULL, /* use system volume */
    .vol_set  = NULL, /* use system volume */
    .vol_up   = NULL, /* use system volume */
    .vol_down = NULL, /* use system volume */
};

static int online_music_init(void)
{
    return 0;
}

static int online_music_deinit(void)
{
    return 0;
}

static int online_music_start(const char *url, uint64_t seek_time, int resume)
{
    int ret = -1;
    if (url) {
        ret = aui_player_seek_play(SMTAUDIO_ONLINE_MUSIC, url, seek_time, resume);
    } else {
        LOGD(TAG, "%s url invalid", __func__);
    }
    return ret;
}

static int online_music_pause(void)
{
    ctrl_online_music.status = SMTAUDIO_STATE_PAUSE;

    int vol_bak = aui_player_vol_get(SMTAUDIO_ONLINE_MUSIC);

    aui_player_vol_set(SMTAUDIO_TYPE_ALL, vol_bak / 3 * 2);
    aos_msleep(50);
    aui_player_vol_set(SMTAUDIO_TYPE_ALL, vol_bak / 3);
    aos_msleep(50);
    aui_player_vol_set(SMTAUDIO_TYPE_ALL, 0);
    aos_msleep(100);
    int ret = aui_player_pause(SMTAUDIO_ONLINE_MUSIC);
    aui_player_vol_set(SMTAUDIO_TYPE_ALL, vol_bak);

    if (ctrl_online_music.callback) {
        ctrl_online_music.callback(SMTAUDIO_ONLINE_MUSIC, SMTAUDIO_PLAYER_EVENT_PAUSE);
    }
    return ret;
}

static int online_music_stop(void)
{
    ctrl_online_music.status = SMTAUDIO_STATE_STOP;
    int ret = aui_player_stop(SMTAUDIO_ONLINE_MUSIC);
    if (ctrl_online_music.callback) {
        ctrl_online_music.callback(SMTAUDIO_ONLINE_MUSIC, SMTAUDIO_PLAYER_EVENT_STOP);
    }
    return ret;
}

static int online_music_resume(void)
{
    return aui_player_resume(SMTAUDIO_ONLINE_MUSIC);
}

int8_t smtaudio_register_online_music(uint8_t min_vol, uint8_t *aef_conf, size_t aef_conf_size, float speed, int resample)
{
    int8_t ret;

    ret = smtaudio_ops_register(&ctrl_online_music);
    ctrl_online_music.init();

    return ret;
}
