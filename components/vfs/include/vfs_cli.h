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

#ifndef __VFS_CLI_H__
#define __VFS_CLI_H__

#include <aos/aos.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief command for cat
 * @return
 */
void cli_reg_cmd_cat(void);

/**
 * @brief command for ls
 * @return
 */
void cli_reg_cmd_ls(void);

/**
 * @brief command for mkdir
 * @return
 */
void cli_reg_cmd_mkdir(void);

/**
 * @brief command for mv
 * @return
 */
void cli_reg_cmd_mv(void);

/**
 * @brief command for rm
 * @return
 */
void cli_reg_cmd_rm(void);

/**
 * @brief command for df
 * @return
 */
void cli_reg_cmd_df(void);

/**
 * @brief command for cp
 * @return
 */
void cli_reg_cmd_cp(void);

/**
 * @brief command for diff
 * @return
 */
void cli_reg_cmd_diff(void);

/**
 * @brief command for echo
 * @return
 */
void cli_reg_cmd_echo(void);

#ifdef __cplusplus
}
#endif

#endif /* __VFS_CLI_H__ */

