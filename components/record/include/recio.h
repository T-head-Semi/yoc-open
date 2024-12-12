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

#ifndef __RECIO_H__
#define __RECIO_H__

#include <aos/aos.h>

typedef struct recio_cls recio_cls_t;

typedef struct {
    const recio_cls_t *cls;
    void *private;
} recio_t;

struct recio_cls {
    const char *name;
    int (*open)(recio_t *io, const char *path);
    int (*close)(recio_t *io);

    int (*read)(recio_t *io, uint8_t *buffer, int length, int timeoutms);
    int (*write)(recio_t *io, uint8_t *buffer, int length, int timeoutms);
    int (*remove)(recio_t *io);
    int (*seek)(recio_t *io, size_t offset, int whence);
};

int recio_register(const recio_cls_t *cls, const char *path);
int recio_unregister(const char *path);

int recio_register_ws(const char *path);
int recio_register_mem(const char *path);
int recio_register_ringb(const char *path);
int recio_register_sdbuf(const char *path);
int recio_register_usb(const char *path);

recio_t *recio_open(const char *path);
int recio_close(recio_t *io);
int recio_read(recio_t *io, uint8_t *buffer, size_t lenght, int timeoutms);
int recio_write(recio_t *io, uint8_t *buffer, size_t lenght, int timeoutms);
int recio_seek(recio_t *io, size_t offset, int whence);



#endif
