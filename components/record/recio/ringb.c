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

#include <stdio.h>
#include <string.h>
#include <aos/aos.h>
#include <aos/ringbuffer.h>
#include "recio.h"
#include "uri_parse.h"

#define TAG "rec-ringb"

typedef struct _ringb_conf {
    dev_ringbuf_t *handle;
} ringb_conf_t;

static int ringb_open(recio_t *io, const char *path)
{
    int value;

    ringb_conf_t *priv = aos_zalloc_check(sizeof(ringb_conf_t));
    if (priv == NULL) {
        LOGE(TAG, "mem open e,mem out");
        return -1;
    }

    if (uri_get_item_value_int(path, "handle", &value) == 0) {
        priv->handle = (dev_ringbuf_t *)((long)value);
    } else {
        goto err;
    }
    // LOGD(TAG, "priv->handle: 0x%x", priv->handle);
    io->private = (void *)priv;
    return 0;    
err:
    aos_free(priv);
    return -1;
}

static int ringb_close(recio_t *io)
{
    if (io->private) {
        aos_free(io->private);
    }
    return 0;
}

static int ringb_read(recio_t *io, uint8_t *buffer, int length, int timeoutms)
{
    ringb_conf_t *priv = (ringb_conf_t *)io->private;

    int ret = ringbuffer_read(priv->handle, buffer, length);
    // LOGD(TAG, "22ringb r len:%d, ret:%d", length, ret);
    return ret;
}

static int ringb_write(recio_t *io, uint8_t *buffer, int length, int timeoutms)
{
    ringb_conf_t *priv = (ringb_conf_t *)io->private;

    return ringbuffer_write(priv->handle, buffer, length);
}

static int ringb_seek(recio_t *io, size_t offset, int whence)
{
    return 0;
}

const recio_cls_t ringb = {
    .name = "ringbuffer",
    .open = ringb_open,
    .close = ringb_close,
    .write = ringb_write,
    .read = ringb_read,
    .seek = ringb_seek,
};

int recio_register_ringb(const char *path)
{
    // LOGD(TAG, "%s, %d, path:%s", __func__, __LINE__, path);

    return recio_register(&ringb, path);
}