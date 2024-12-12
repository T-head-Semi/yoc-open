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
#ifndef _FCT_COMM_H_

#include <stdio.h>

typedef enum {
    TEST_IDLE = 0,
    TEST_RUNNING,
    TEST_END,
    TEST_ERROR,
} fct_test_stat_t;

int fct_comm_init(int uart_id, uint32_t baud_rate);
int fct_comm_unreg_cmd(const char *name);
int fct_comm_reg_cmd(const char *name, const char *help, int cmd_id);

int fct_state();
char *fct_get_result(void);
int fct_run_test(int cmd_id, int isquery, int argc, char **argv);
#endif
