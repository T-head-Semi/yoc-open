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

#ifndef __NAMED_STRAIGHTFIFO_H__
#define __NAMED_STRAIGHTFIFO_H__

#include <fcntl.h>
#include "straight_fifo.h"

__BEGIN_DECLS__

typedef struct named_sfifo nsfifo_t;

/**
 * @brief  open or create a named fifo
 * @param  [in] name
 * @param  [in] mode : O_CREAT/O_RDONLY
 * @param  [in] ...  : if mode == O_CREAT, params size is needed
 * @param              size : size of the straight fifo
 * @return NULL on err
 */
nsfifo_t* nsfifo_open(const char *name, int mode, ...);

/**
 * @brief  get straight read pos
 * @param  [in] fifo
 * @param  [out] pos
 * @param  [in] timeout : ms
 * @return straight read size
 */
int nsfifo_get_rpos(nsfifo_t* fifo, char **pos, uint32_t timeout);

/**
 * @brief  set the read pos after read
 * @param  [in] fifo
 * @param  [in] count
 * @return 0/-1
 */
int nsfifo_set_rpos(nsfifo_t* fifo, size_t count);

/**
 * @brief  get straight write pos
 * @param  [in] fifo
 * @param  [out] pos
 * @param  [in] timeout : ms
 * @return straight write size
 */
int nsfifo_get_wpos(nsfifo_t* fifo, char **pos, uint32_t timeout);

/**
 * @brief  set the write pos after write
 * @param  [in] fifo
 * @param  [in] count
 * @return 0/-1
 */
int nsfifo_set_wpos(nsfifo_t* fifo, size_t count);

/**
 * @brief  set eof to the fifo before destroy, may be block if don't call this fun
 * @param  [in] fifo
 * @param  [in] reof : nsfifo_get_rpos will return immediately when set
 * @param  [in] weof : nsfifo_get_wpos will return immediately when set
 * @return 0/-1
 */
int nsfifo_set_eof(nsfifo_t* fifo, uint8_t reof, uint8_t weof);

/**
 * @brief  get eof flag from the fifo
 * @param  [in] fifo
 * @param  [out] reof : read eof flag
 * @param  [out] weof : write eof flag
 * @return 0/-1
 */
int nsfifo_get_eof(nsfifo_t* fifo, uint8_t *reof, uint8_t *weof);

/**
 * @brief  reset the named fifo
 * @param  [in] fifo
 * @return 0/-1
 */
int nsfifo_reset(nsfifo_t *fifo);

/**
 * @brief  get valid data len of the named fifo
 * @param  [in] fifo
 * @return -1 on error
 */
int nsfifo_get_len(nsfifo_t *fifo);

/**
 * @brief  close the named fifo
 * @param  [in] fifo
 * @return 0/-1
 */
int nsfifo_close(nsfifo_t *fifo);

__END_DECLS__

#endif /* __NAMED_STRAIGHTFIFO_H__ */

