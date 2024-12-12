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

#if defined(CONFIG_PLAYER_CX) && CONFIG_PLAYER_CX
#include "av/xplayer/xplayer_cls.h"
#include "av/cav/xplayer/cxplayer.h"

#define TAG "player_cx"

struct player_cx_priv {
    player_t         *player;
    ply_conf_t       pcnf;
    uint8_t          eq_segments;   ///< used for equalizer config
    eqfp_t           *eq_params;
};
#define GET_DERIVED_PLAYER_CX(p) ((struct player_cx_priv*)GET_DERIVED_PLAYER(p))

static void _player_event(void *user_data, uint8_t type, const void *data, uint32_t len)
{
    xplayer_t *xplayer = user_data;
    LOGD(TAG, "media(%p) evt:%d\n", xplayer, type);

    if (xplayer && xplayer->event_cb)
        xplayer->event_cb(xplayer->user_data, type, data, len);
}

static int _xplayer_cx_init(xplayer_t *xplayer)
{
    struct player_cx_priv *priv = GET_DERIVED_PLAYER_CX(xplayer);
    ply_conf_t *pcnf = &priv->pcnf;

    player_init();
    player_conf_init(pcnf);
#ifdef __linux__
    pcnf->ao_name        = "alsa_standard";
    //pcnf->ao_name        = "dummy";
#else
    pcnf->ao_name        = "alsa";
#endif
    pcnf->event_cb       = _player_event;
    pcnf->vol_en         = 1;
    pcnf->vol_index      = xplayer->vol;
    pcnf->atempo_play_en = 1;
    pcnf->user_data      = xplayer;

    return 0;
}

static void _reset_priv_conf(struct player_cx_priv *priv)
{
    ply_conf_t *pcnf = &priv->pcnf;

    pcnf->aef_conf_size = 0;
    priv->eq_segments   = 0;

    av_freep((char**)&pcnf->aef_conf);
    av_freep((char**)&priv->eq_params);
}

static int _xplayer_cx_set_config(xplayer_t *xplayer, const xplayer_cnf_t *conf)
{
    struct player_cx_priv *priv = GET_DERIVED_PLAYER_CX(xplayer);
    ply_conf_t *pcnf = &priv->pcnf;

    _reset_priv_conf(priv);
    pcnf->resample_rate         = conf->resample_rate;
    pcnf->cache_size            = conf->web_cache_size;
    pcnf->cache_start_threshold = conf->web_start_threshold;
    pcnf->period_ms             = conf->snd_period_ms;
    pcnf->period_num            = conf->snd_period_num;


    if (conf->aef_conf && conf->aef_conf_size) {
#if defined(CONFIG_AEFXER_SONA) && CONFIG_AEFXER_SONA && CONFIG_AV_AEF_DEBUG
        extern int aef_debug_init(int fs, char *conf, size_t conf_size);
        aef_debug_init(conf->resample_rate, conf->aef_conf, conf->aef_conf_size);
#else
        pcnf->aef_conf      = av_malloc(conf->aef_conf_size);
        pcnf->aef_conf_size = conf->aef_conf_size;
        memcpy(pcnf->aef_conf, conf->aef_conf, conf->aef_conf_size);
#endif
    }

    if (conf->eq_segments && conf->eq_params) {
        priv->eq_params   = av_malloc(sizeof(eqfp_t) * conf->eq_segments);
        priv->eq_segments = conf->eq_segments;
        memcpy(priv->eq_params, conf->eq_params, conf->eq_segments);
    }

    return 0;
}

static int _xplayer_cx_get_config(xplayer_t *xplayer, xplayer_cnf_t *conf)
{
    struct player_cx_priv *priv = GET_DERIVED_PLAYER_CX(xplayer);
    ply_conf_t *pcnf = &priv->pcnf;

    conf->aef_conf            = pcnf->aef_conf;
    conf->aef_conf_size       = pcnf->aef_conf_size;
    conf->resample_rate       = pcnf->resample_rate;
    conf->web_cache_size      = pcnf->cache_size;
    conf->web_start_threshold = pcnf->cache_start_threshold;
    conf->snd_period_ms       = pcnf->period_ms;
    conf->snd_period_num      = pcnf->period_num;
    conf->eq_segments         = priv->eq_segments;
    conf->eq_params           = priv->eq_params;

    return 0;
}

static int _xplayer_cx_play(xplayer_t *xplayer)
{
    int rc = -1;
    struct player_cx_priv *priv = GET_DERIVED_PLAYER_CX(xplayer);
    ply_conf_t *pcnf = &priv->pcnf;

    if (!priv->player) {
        priv->player = player_new(pcnf);
        if (!priv->player) {
            LOGE(TAG, "play new err(%s)", xplayer->url);
            return -1;
        }
    }

    if (priv->eq_segments && priv->eq_params) {
        int i;
        peq_seten_t eqen;
        peq_setpa_t eqpa;

        for (i = 0; i < priv->eq_segments; i++) {
            eqpa.segid = i;
            eqpa.param = priv->eq_params[i];
            if (priv->eq_params[i].type != EQF_TYPE_UNKNOWN) {
                player_ioctl(priv->player, PLAYER_CMD_EQ_SET_PARAM, &eqpa);
            }
        }

        eqen.enable = 1;
        player_ioctl(priv->player, PLAYER_CMD_EQ_ENABLE, &eqen);
    }

    rc = player_play(priv->player, xplayer->url, xplayer->start_time);
    if(rc < 0) {
        LOGE(TAG, "player play failed, ret %d", rc);
        return -1;
    }

    return rc;
}

static int _xplayer_cx_pause(xplayer_t *xplayer)
{
    struct player_cx_priv *priv = GET_DERIVED_PLAYER_CX(xplayer);

    return player_pause(priv->player);
}

static int _xplayer_cx_resume(xplayer_t *xplayer)
{
    struct player_cx_priv *priv = GET_DERIVED_PLAYER_CX(xplayer);

    return player_resume(priv->player);
}

static int _xplayer_cx_seek(xplayer_t *xplayer, uint64_t timestamp)
{
    struct player_cx_priv *priv = GET_DERIVED_PLAYER_CX(xplayer);

    return player_seek(priv->player, timestamp);
}

static int _xplayer_cx_stop(xplayer_t *xplayer)
{
    struct player_cx_priv *priv = GET_DERIVED_PLAYER_CX(xplayer);

    return player_stop(priv->player);
}

static void _xplayer_cx_uninit(xplayer_t *xplayer)
{
    struct player_cx_priv *priv = GET_DERIVED_PLAYER_CX(xplayer);

    _reset_priv_conf(priv);
    player_free(priv->player);
    priv->player = NULL;
    return;
}

static int _xplayer_cx_get_media_info(xplayer_t *xplayer, xmedia_info_t *minfo)
{
    struct player_cx_priv *priv = GET_DERIVED_PLAYER_CX(xplayer);

    return player_get_media_info(priv->player, minfo);
}

static int _xplayer_cx_get_time(xplayer_t *xplayer, xplay_time_t *time)
{
    struct player_cx_priv *priv = GET_DERIVED_PLAYER_CX(xplayer);

    return player_get_cur_ptime(priv->player, time);
}

static int _xplayer_cx_set_speed(xplayer_t *xplayer, float speed)
{
    struct player_cx_priv *priv = GET_DERIVED_PLAYER_CX(xplayer);

    return player_set_speed(priv->player, speed);
}

static int _xplayer_cx_set_vol(xplayer_t *xplayer, uint8_t vol)
{
    int rc = 0;
    struct player_cx_priv *priv = GET_DERIVED_PLAYER_CX(xplayer);
    ply_conf_t *pcnf = &priv->pcnf;

    if (priv->player) {
        rc = player_set_vol(priv->player, vol);
    }
    if (rc == 0) {
        pcnf->vol_index = vol;
    }

    return rc;
}

static int _xplayer_cx_set_mute(xplayer_t *xplayer, uint8_t mute)
{
    struct player_cx_priv *priv = GET_DERIVED_PLAYER_CX(xplayer);

    if (mute)
        return player_set_vol(priv->player, 0);
    else
        return player_set_vol(priv->player, xplayer->vol);
}

#if !CONFIG_AV_AUDIO_ONLY_SUPPORT
static int _xplayer_cx_switch_audio_track(xplayer_t *xplayer, uint8_t idx)
{
    //TODO:
    return -1;
}

static int _xplayer_cx_switch_subtitle_track(xplayer_t *xplayer, uint8_t idx)
{
    //TODO:
    return -1;
}

static int _xplayer_cx_set_subtitle_url(xplayer_t *xplayer, const char *url)
{
    //TODO:
    return -1;
}

static int _xplayer_cx_set_subtitle_visible(xplayer_t *xplayer, uint8_t visible)
{
    //TODO:
    return -1;
}

static int _xplayer_cx_set_video_visible(xplayer_t *xplayer, uint8_t visible)
{
    //TODO:
    return -1;
}

static int _xplayer_cx_set_video_crop(xplayer_t *xplayer, const xwindow_t *win)
{
    //TODO:
    return -1;
}

static int _xplayer_cx_set_fullscreen(xplayer_t *xplayer, uint8_t onoff)
{
    //TODO:
    return -1;
}

static int _xplayer_cx_set_display_window(xplayer_t *xplayer, const xwindow_t *win)
{
    //TODO:
    return -1;
}

static int _xplayer_cx_set_display_format(xplayer_t *xplayer, xdisplay_format_t format)
{
    //TODO:
    return -1;
}

static int _xplayer_cx_set_video_rotate(xplayer_t *xplayer, xrotate_type_t type)
{
    //TODO:
    return -1;
}

#endif

static const struct xplayer_ops xplayer_ops_cx = {
    .init                  = _xplayer_cx_init,
    .get_config            = _xplayer_cx_get_config,
    .set_config            = _xplayer_cx_set_config,
    .play                  = _xplayer_cx_play,
    .pause                 = _xplayer_cx_pause,
    .resume                = _xplayer_cx_resume,
    .seek                  = _xplayer_cx_seek,
    .stop                  = _xplayer_cx_stop,
    .uninit                = _xplayer_cx_uninit,

    .get_media_info        = _xplayer_cx_get_media_info,
    .get_time              = _xplayer_cx_get_time,
    .set_vol               = _xplayer_cx_set_vol,
    .set_speed             = _xplayer_cx_set_speed,
    .set_mute              = _xplayer_cx_set_mute,
#if !CONFIG_AV_AUDIO_ONLY_SUPPORT
    .switch_audio_track    = _xplayer_cx_switch_audio_track,
    .switch_subtitle_track = _xplayer_cx_switch_subtitle_track,
    .set_subtitle_url      = _xplayer_cx_set_subtitle_url,
    .set_subtitle_visible  = _xplayer_cx_set_subtitle_visible,
    .set_video_visible     = _xplayer_cx_set_video_visible,
    .set_video_crop        = _xplayer_cx_set_video_crop,
    .set_fullscreen        = _xplayer_cx_set_fullscreen,
    .set_display_window    = _xplayer_cx_set_display_window,
    .set_display_format    = _xplayer_cx_set_display_format,
    .set_video_rotate      = _xplayer_cx_set_video_rotate,
#endif
};

const struct xplayer_cls xplayer_cls_cx = {
    .name            = "cx",
    .priv_size       = sizeof(struct player_cx_priv),
    .ops             = &xplayer_ops_cx,
};

#endif

