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

#ifndef __NAMED_FIFO_H__
#define __NAMED_FIFO_H__

#include "lc_fifo.h"

__BEGIN_DECLS__

#define NAMED_FIFO_NAME_SIZE_MAX  (32)
#define NAMED_FIFO_SIZE_DEFAULT   (32*1024)

typedef struct named_fifo named_fifo_t;

/**
 * @brief  open or create the fifo
 * @param  [in] name : the name of fifo
 * @param  [in] fifo_size : default len is NAMED_FIFO_SIZE_DEFAULT when fifo_size = 0
 * @return
 */
named_fifo_t *named_fifo_open(const char *name, size_t fifo_size);

/**
 * @brief  write data
 * @param  [in] fifo
 * @param  [in] data
 * @param  [in] size
 * @return real size or -1 when err
 */
int named_fifo_write(named_fifo_t *fifo, const uint8_t *data, size_t size);

/**
 * @brief  read data
 * @param  [in] fifo
 * @param  [in] data
 * @param  [in] size
 * @return real size or -1 when err
 */
int named_fifo_read(named_fifo_t *fifo, uint8_t *data, size_t size);

/**
 * @brief  set read finish
 * @param  [in] fifo
 * @param  [in] eof
 * @return  0/-1
 */
int named_fifo_set_reof(named_fifo_t *fifo, int eof);

/**
 * @brief  set write finish
 * @param  [in] fifo
 * @param  [in] eof
 * @return  0/-1
 */
int named_fifo_set_weof(named_fifo_t *fifo, int eof);

/**
 * @brief  get availabe read len
 * @param  [in] fifo
 * @return
 */
int named_fifo_get_rlen(named_fifo_t *fifo);

/**
 * @brief  get availabe write len
 * @param  [in] fifo
 * @return
 */
int named_fifo_get_wlen(named_fifo_t *fifo);

/**
 * @brief  is the read finish
 * @param  [in] fifo
 * @return
 */
int named_fifo_is_reof(named_fifo_t *fifo);

/**
 * @brief  is the write finish
 * @param  [in] fifo
 * @return
 */
int named_fifo_is_weof(named_fifo_t *fifo);

/**
 * @brief  close the fifo
 * @param  [in] fifo
 * @return 0/-1
 */
int named_fifo_close(named_fifo_t *fifo);

__END_DECLS__

#endif /* __NAMED_FIFO_H__ */

