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

#ifndef __BOARD_H__
#define __BOARD_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************/

/**
 * @brief  init the vendor cv params
 * @return
 */
void cv_params_init();

/**
 * @brief  get the chixiao board configuration
 * @return configuration char string
 */
const char *get_cx_board_config();

/**
 * @brief  get the chixiao service configuration
 * @return configuration char string
 */
const char *get_cx_service_config();

/**
 * @brief  get the chixiao input channel configuration
 * @return configuration char string
 */
const char *get_cx_input_channel_config();


/****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __BOARD_H__ */

