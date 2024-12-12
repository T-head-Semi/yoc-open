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

#ifndef __ICORE_MSG_H__
#define __ICORE_MSG_H__

#include "av/avutil/common.h"

__BEGIN_DECLS__

typedef int msgid_t;

#define ICORE_ALIGNMENT  (16)
#define ICORE_ALIGN(addr)      (AV_ALIGN((addr), ICORE_ALIGNMENT))
#define ICORE_ALIGN_BUFZ(size) (AV_ALIGN_BUFZ((size), ICORE_ALIGNMENT * 2))

typedef struct icore_resp {
    int         code;       // return code
    size_t      resp_size;  // if have
    char        *resp;      // if have
} icore_resp_t;

typedef struct icore_msg {
    char        *orip;      // origin pointer of this message self for align
    msgid_t      id;
    size_t       size;
    icore_resp_t ret;
    char         msg_body[0];
} icore_msg_t;

#define ICORE_MSG_SIZE sizeof(icore_msg_t)

#define icore_get_msg(msg, type)  \
	(msg ? (((msg)->size == sizeof(type) ? (type*)((char*)(msg) + ICORE_MSG_SIZE) : NULL)) : NULL)

#define icore_resp_get(msg)  \
	(msg ? &(((icore_msg_t*)(msg))->ret) : NULL)

/**
 * @brief  new one icore message by msdid
 * @param  [in] id
 * @param  [in] size : size of the msg actualy
 * @return NULL on error
 */
icore_msg_t *icore_msg_new(msgid_t id, size_t size);

/**
 * @brief  free res by icore_msg_new
 * @param  [in] msg
 * @return
 */
void icore_msg_free(icore_msg_t *msg);


__END_DECLS__

#endif /* __ICORE_MSG_H__ */

