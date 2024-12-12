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

#ifndef __MEM_BLOCK_H__
#define __MEM_BLOCK_H__

#include "av/avutil/common.h"

__BEGIN_DECLS__

typedef struct {
    void            *data;
    void            *data_orip; ///< original pointer

    size_t          size;       ///< total capcity
    size_t          used;       ///< length of avilable data
    size_t          align;      ///< address of the data is align when addr_align != 0
} mblock_t;

/**
 * @brief  new a mem block
 * @param  [in] size
 * @param  [in] align : address of the data is align when addr_align != 0
 * @return 0/-1
 */
mblock_t* mblock_new(size_t size, size_t align);

/**
 * @brief  grow the mem block data size
 * @param  [in] mb
 * @param  [in] size
 * @return 0/-1
 */
int mblock_grow(mblock_t *mb, size_t size);

/**
 * @brief  free resource of the mem block
 * @param  [in] mb
 * @return
 */
int mblock_free(mblock_t *mb);

__END_DECLS__

#endif /* __MEM_BLOCK_H__ */

