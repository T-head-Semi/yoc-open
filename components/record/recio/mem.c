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
#include "recio.h"
#include "uri_parse.h"

#define TAG "rec-mem"

typedef struct _mem_conf {
    uint32_t    address;
    int         size;
    int         wpos;
} mem_conf_t;

static int mem_open(recio_t *io, const char *path)
{
    int value;

    mem_conf_t *priv = aos_zalloc_check(sizeof(mem_conf_t));
    if (priv == NULL) {
        LOGE(TAG, "mem open e,mem out");
        return -1;
    }

    if (uri_get_item_value_int(path, "size", &value) == 0) {
        priv->size = value;
    } else {
        goto err;
    }
    if (uri_get_item_value_int(path, "address", &value) == 0) {
        priv->address = value;
    } else {
        goto err;
    }
    LOGD(TAG, "priv->address: 0x%x, %d", priv->address, priv->size);
    io->private = (void *)priv;
    return 0;    
err:
    aos_free(priv);
    return -1;
}

static int mem_close(recio_t *io)
{
    if (io->private) {
        aos_free(io->private);
    }
    return 0;
}

static int mem_read(recio_t *io, uint8_t *buffer, int length, int timeoutms)
{
    mem_conf_t *priv = (mem_conf_t *)io->private;

    memcpy(buffer, (void *)((unsigned long)priv->address), priv->size);
    LOGD(TAG, "mem read:0x%x, %d", priv->address, priv->size);
    return priv->size;
}

static int mem_write(recio_t *io, uint8_t *buffer, int length, int timeoutms)
{
    mem_conf_t *priv = (mem_conf_t *)io->private;

    uint8_t * wbuf = (void *)((unsigned long)priv->address);

    if (priv->wpos + length <= priv->size) {
        memcpy(&wbuf[priv->wpos], buffer, length);
        priv->wpos += length;
        return length;
    }

    return -1;
}

static int mem_seek(recio_t *io, size_t offset, int whence)
{
    return 0;
}

const recio_cls_t mem = {
    .name = "mem",
    .open = mem_open,
    .close = mem_close,
    .write = mem_write,
    .read = mem_read,
    .seek = mem_seek,
};

int recio_register_mem(const char *path)
{
    LOGD(TAG, "%s, %d, path:%s", __func__, __LINE__, path);

    return recio_register(&mem, path);
}