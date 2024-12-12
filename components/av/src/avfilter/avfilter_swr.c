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

#include "av/avfilter/avfilter_swr.h"
#include "av/swresample/swresample.h"

#define TAG                   "filter_swr"

struct avfilter_swr {
    struct avfilter           f;

    sf_t                      isf;
    sf_t                      osf;
    swr_t                     *s;
};

static int _avf_swr_control(avfilter_t *avf, int cmd, void *arg, size_t *arg_size)
{
    //TODO
    return 0;
}

static int _avf_swr_filter_frame(avfilter_t *avf, const avframe_t *in, avframe_t *out)
{
    int rc = -1;
    struct avfilter_swr *dobj = (struct avfilter_swr*)avf;
    swr_t *s                  = dobj->s;

    if (dobj->s && (in->sf == dobj->isf)) {
        rc = swr_convert_frame(s, in, out);
        if (rc <= 0) {
            LOGD(TAG, "swr convert frame may be failed, rc = %d", rc);
            return rc;
        }

        rc = out->nb_samples;
    }

    return rc;
}

static int _avf_swr_uninit(avfilter_t *avf)
{
    struct avfilter_swr *dobj = (struct avfilter_swr*)avf;

    swr_free(dobj->s);
    return 0;
}

const struct avfilter_ops avf_ops_swr = {
    .name            = "swr",
    .type            = AVMEDIA_TYPE_AUDIO,

    .control         = _avf_swr_control,
    .filter_frame    = _avf_swr_filter_frame,
    .uninit          = _avf_swr_uninit,
};

/**
 * @brief  open swr avfilter
 * @param  [in] inst_name : the name of avfilter_t instance
 * @param  [in] swrp
 * @return NULL on error
 */
avfilter_t *avf_swr_open(const char *inst_name, const swr_avfp_t *swrp)
{
    int rc;
    swr_t *s;
    struct avfilter *f        = NULL;
    struct avfilter_swr *dobj = NULL;

    CHECK_PARAM(inst_name && swrp, NULL);
    CHECK_PARAM(swrp->isf != swrp->osf, NULL);
    dobj = av_zalloc(sizeof(struct avfilter_swr));
    f       = (avfilter_t*)dobj;
    f->ops  = &avf_ops_swr;
    f->dobj = dobj;

    avf_init(inst_name, f);

    rc = f->ops->init ? f->ops->init((avfilter_t*)dobj) : 0;
    CHECK_RET_TAG_WITH_GOTO(rc == 0, err);

    s  = swr_new(swrp->isf, swrp->osf);
    CHECK_RET_TAG_WITH_GOTO(s, err);
    dobj->s   = s;
    dobj->isf = swrp->isf;
    dobj->osf = swrp->osf;
    LOGD(TAG, "open a avfilter, name = %s", f->ops->name);

    return (avfilter_t*)dobj;
err:
    avf_uninit(f);
    av_free(dobj);
    return NULL;
}



