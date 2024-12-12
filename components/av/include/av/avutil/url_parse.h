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

#ifndef __URL_PARSE_H__
#define __URL_PARSE_H__

#include "av/avutil/common.h"

__BEGIN_DECLS__

/**
 * @brief  get item value from a url
 * @param  [in] url
 * @param  [in] item : name of the item
 * @param  [out] value
 * @param  [in] len  : length of the value
 * @return 0/-1
 */
int url_get_item_value(const char *url, const char *item, char *value, size_t len);

/**
 * @brief  get item int value from a url
 * @param  [in] url
 * @param  [in] item : name of the item
 * @param  [out] value
 * @return 0/-1
 */
int url_get_item_value_int(const char *url, const char *item, int *value);

/**
 * @brief  get item long value from a url
 * @param  [in] url
 * @param  [in] item : name of the item
 * @param  [out] value
 * @return 0/-1
 */
int url_get_item_value_long(const char *url, const char *item, long *value);

__END_DECLS__

#endif /* __URL_PARSE_H__ */

