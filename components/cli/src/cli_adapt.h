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

#ifndef CLI_ADAPT_H
#define CLI_ADAPT_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Create a task
 *
 * @param[in] name name of the task
 * @param[in] fn   the entry function of task
 * @param[in] arg  the parameter of task entry function
 * @param[in] stack the size of task stack
 *
 * @return 0 on success, otherwise failed
 */

int32_t cli_task_create(const char *name, void (*fn)(void *), void *arg,
                        uint32_t stack, uint32_t priority);

/**
 * @brief Task exit.
 *
 * @return none
 */
void cli_task_exit(void);

/**
 * @brief Get character from uart
 *
 * @param[out] inbuf pointer to the buffer storing the character
 *
 * @return the number of the character
 *
 */
int32_t cli_getchar(char *inbuf);

/**
 * @brief Put the message via uart
 *
 * @param[in] msg pointer to the message
 *
 * @return 0 on success, otherwise failed
 *
 */
int32_t cli_putstr(char *msg);

/**
 * @brief wrapper of MM allocation
 *
 * @param[in]  size size of the mem to alloc
 *
 * @return NULL is error, other is memory address
 *
 */
void *cli_malloc(uint32_t size);

/**
 * @brief wrapper of MM free
 *
 * @param[in] ptr address point of the mem
 *
 */
void cli_free(void *ptr);


#ifdef __cplusplus
}
#endif

#endif /* CLI_ADAPT_H */
