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

#ifndef __NAMED_SFIFO_CLS_H__
#define __NAMED_SFIFO_CLS_H__

#include <fcntl.h>
#include "av/avutil/common.h"

__BEGIN_DECLS__

typedef struct named_sfifo {
    char                         *name;               ///< origin name
    size_t                       size;
    struct nsfifo_cls            *cls;
    aos_mutex_t                  lock;
} nsfifo_t;

#define GET_DERIVED_NSFIFO(p) (((char*)(p)) + sizeof(nsfifo_t))

struct nsfifo_ops  {
    int   (*init)                (nsfifo_t *fifo, const char *name, int mode);
    int   (*get_rpos)            (nsfifo_t *fifo, char **pos, uint32_t timeout);
    int   (*set_rpos)            (nsfifo_t* fifo, size_t count);
    int   (*get_wpos)            (nsfifo_t *fifo, char **pos, uint32_t timeout);
    int   (*set_wpos)            (nsfifo_t* fifo, size_t count);
    int   (*set_eof)             (nsfifo_t* fifo, uint8_t reof, uint8_t weof);
    int   (*get_eof)             (nsfifo_t* fifo, uint8_t *reof, uint8_t *weof);
    int   (*reset)               (nsfifo_t *fifo);
    int   (*get_len)             (nsfifo_t *fifo);
    void  (*uninit)              (nsfifo_t *fifo);
};


struct nsfifo_cls  {
    const char                   *name;
    size_t                       priv_size;
    const struct nsfifo_ops      *ops;
};

__END_DECLS__

#endif /* __NAMED_SFIFO_CLS_H__ */

