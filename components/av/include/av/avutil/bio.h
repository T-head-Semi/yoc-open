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

#ifndef __BIO_H__
#define __BIO_H__

#include "av/avutil/byte_rw.h"

__BEGIN_DECLS__

typedef struct buf_io {
    size_t                            pos;
    uint8_t                           *buf;
    size_t                            size;
} bio_t;

int bio_init(bio_t *bio, uint8_t *buf, size_t size);

int bio_reset(bio_t *bio);

int bio_read(bio_t *bio, uint8_t *buf, size_t count);

int bio_skip(bio_t *bio, int32_t offset);

int bio_tell(bio_t *bio);

uint8_t bio_r8(bio_t *bio);

uint16_t bio_r16be(bio_t *bio);

uint32_t bio_r24be(bio_t *bio);

uint32_t bio_r32be(bio_t *bio);

uint64_t bio_r64be(bio_t *bio);

uint16_t bio_r16le(bio_t *bio);

uint32_t bio_r24le(bio_t *bio);

uint32_t bio_r32le(bio_t *bio);

uint64_t bio_r64le(bio_t *bio);

__END_DECLS__

#endif /* __BIO_H__ */

