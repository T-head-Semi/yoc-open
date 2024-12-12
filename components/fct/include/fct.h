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

#ifndef _FCT_H_

#include <uservice/uservice.h>

/*测试结果最大长度*/
#define FTEST_MAX_RESULT_LEN        256

/* 测试返回结果 */
#define FTEST_RESULT_SUCCESS        0  
#define FTEST_RESULT_ERR_PARAM      -1
#define FTEST_RESULT_ERR_FAILED     -2

typedef int (*fct_test_case)(int isquery, int arg_num, char **args, char *test_result);

/**
 * 初始化产测程序
 *
 * @param[in]  uart_id 产测命令串口ID
 * @param[in]  baud_rate 串口波特率
 * @param[in]  task 产测程序运行线程
 * @return  0 成功, 其他失败.
 */
int fct_init(int uart_id, uint32_t baud_rate, utask_t *task);

/**
 * 添加按键配置
 *
 * @param[in]  name AT指令名
 * @param[in]  help AT指令帮助信息，上位机通过AT+XXX=?获取
 * @param[in]  test_function 产测程序
 * @return  0 成功, 其他失败.
 */
int fct_register_cmd(const char *name, char *help, fct_test_case test_function);

/**
 * 添加按键配置
 *
 * @param[in]  name AT指令名
 * @return  0 成功, 其他失败.
 */
int fct_unregister_cmd(const char *name);

#endif
