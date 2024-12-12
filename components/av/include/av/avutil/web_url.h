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

#ifndef __WEB_URL_H__
#define __WEB_URL_H__

#include "av/avutil/common.h"

__BEGIN_DECLS__

#ifdef __cplusplus
extern "C" {
#endif

#define URL_USERNAME_LEN_MAX   (32)
#define URL_PASSWD_LEN_MAX     (32)

typedef struct web_url {
    char           *url;
    char           *host;
    char           *path;
    uint16_t       port;
    uint8_t        is_https;

    char           *user;
    char           *passwd;
#define URL_IS_HTTPS(u) ((u) && (u)->is_https)
} web_url_t;

/**
 * @brief  create web url, parse the url
 * @param  [in] url
 *         url format: http(s)://[[user:passwd]@]host[:port][/path][?query]
 * @return NULL on err
 */
web_url_t* web_url_new(const char *url);

/**
 * @brief  free web url
 * @param  [in] url
 * @return 0/-1
 */
int web_url_free(web_url_t *url);

__END_DECLS__


#ifdef __cplusplus
}
#endif

#endif /* __WEB_URL_H__ */

