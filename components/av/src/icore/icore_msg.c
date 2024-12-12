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

#include "av/avutil/common.h"
#include "av/icore/icore_msg.h"

/**
 * @brief  new one icore message by msdid
 * @param  [in] id
 * @param  [in] size : size of the msg actualy
 * @return NULL on error
 */
icore_msg_t *icore_msg_new(msgid_t id, size_t size)
{
    char *orip;
    icore_msg_t *msg = NULL;

    orip = av_zalloc(ICORE_ALIGN_BUFZ(size + ICORE_MSG_SIZE));
    if (orip) {
        msg           = ICORE_ALIGN(orip);
        msg->orip     = orip;
        msg->id       = id;
        msg->size     = size;
        msg->ret.code = -1;
    }

    return msg;
}

/**
 * @brief  free res by icore_msg_new
 * @param  [in] msg
 * @return
 */
void icore_msg_free(icore_msg_t *msg)
{
    if (msg && msg->orip) {
        av_free(msg->orip);
    }
}




