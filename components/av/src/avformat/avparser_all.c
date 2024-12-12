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

#include "av/avformat/avparser.h"
#include "av/avformat/avparser_all.h"

/**
 * @brief  regist avparser for mp3
 * @return 0/-1
 */
int avparser_register_mp3()
{
    extern struct avparser_ops avparser_ops_mp3;
    return avparser_ops_register(&avparser_ops_mp3);
}

/**
 * @brief  regist avparser for adts
 * @return 0/-1
 */
int avparser_register_adts()
{
    extern struct avparser_ops avparser_ops_adts;
    return avparser_ops_register(&avparser_ops_adts);
}

