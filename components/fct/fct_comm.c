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

#include <errno.h>
#include <string.h>
#include <aos/debug.h>
#include <aos/kernel.h>
#include <aos/list.h>
#include <uservice/uservice.h>
// #include <yoc/cli.h>
// #include <yoc/init.h>
#include <devices/uart.h>
#include "fct_comm.h"

#define MAX_CMD_NAME_LEN        32
#define MAX_CMD_ARGS_LEN        256
#define MAX_CMD_ARG_NUM         20

#define MSG_ERR_TEMP        "ERROR:%s\r\n"
#define MSG_NOT_FOUND_TEMP  "ERROR:command not found\r\n"
#define MSG_STILL_RUN_TEMP  "ERROR:last command still running\r\n"
#define MSG_RUN_FAIL_TEMP   "ERROR:command exe failed\r\n"
#define MSG_REPLY_TEMP      "+%s:%s\r\nOK\r\n"
#define MSG_TEST_TEMP       "+%s:\"%s\"\r\nOK\r\n"
#define SUCCESS_MSG         "OK\r\n"

#define CMD_NOT_FOUND   9999

typedef struct fct_command {
    const char          *name;
    const char          *help;
    int                 cmd_id;
    // cmd_function_t function;
} fct_command_t;

typedef enum {
    CMD_IDLE = 0,
    CMD_AT_1,
    CMD_AT_2,
    CMD_AND,
    CMD_NAME,
    CMD_QUERY,     // AT+<CMD>?
    CMD_EQ,
    CMD_TEST,      // AT+<CMD>=?
    CMD_ARGS,      // AT+<CMD>=xx,xx,xx
} comm_stat_t;

typedef enum {
    EXE_IDLE = 0,
    EXE_RUNNING,
    EXE_FINISHED,
} execute_stat_t;

typedef struct cmd_list {
    const char          *name;
    const char          *help;
    int                 cmd_id;
    slist_t             next;
} cmd_list_t;

static slist_t cmd_lists;
static rvm_dev_t *comm_handle = NULL;
static char *cmd_name, *cmd_args, *cmd_args_cp;
static uint16_t cmd_name_len, cmd_args_len;
static char **arg_items;
static execute_stat_t exe_stat;
static aos_task_t tsk_comm ={NULL} ;

static int ch_parse(char ch)
{
    static comm_stat_t cmd_stat;
    char err_msg[128];

    if (ch == '\r' || ch == '\n') {
        if (cmd_stat == CMD_AT_2 || cmd_stat == CMD_QUERY || cmd_stat == CMD_TEST || cmd_stat == CMD_ARGS) {
            cmd_name[cmd_name_len] = 0;
            cmd_args[cmd_args_len] = 0;
            
            int ret_stat = cmd_stat;
            cmd_stat = CMD_IDLE;
            return ret_stat;
        } else {
            cmd_stat = CMD_IDLE;
            return -1;
        }
    } else if (ch == ' ' && cmd_stat != CMD_ARGS) {     // skip the spaces
        return -1;
    }

    switch(cmd_stat) {
        case CMD_IDLE:
            if (ch == 'A') {
                cmd_stat = CMD_AT_1;
            }
            break;

        case CMD_AT_1:
            if (ch == 'T') {
                cmd_stat = CMD_AT_2;
            } else {
                cmd_stat = CMD_IDLE;
            }
            break;

        case CMD_AT_2:
            if (ch == '+') {
                cmd_name_len = 0;
                cmd_stat = CMD_AND;
            } else {
                cmd_stat = CMD_IDLE;
            }
            break;

        case CMD_AND:
            if ((ch <= 'Z' && ch >= 'A') || (ch <= '9' && ch >= '0')) {
                cmd_stat = CMD_NAME;
            } else {
                cmd_stat = CMD_IDLE;
                break;
            }

        case CMD_NAME:
            if ((ch <= 'Z' && ch >= 'A') || (ch <= '9' && ch >= '0')) {
                cmd_name[cmd_name_len++] = ch;
            } else if (ch == '=') {
                cmd_stat = CMD_EQ;
            } else if (ch == '?') {
                cmd_stat = CMD_QUERY;
            } else {
                cmd_stat = CMD_IDLE;
            }
            break;

        case CMD_EQ:
            if (ch == '?') {
                cmd_stat = CMD_TEST;
                break;
            } else {
                cmd_args_len = 0;
                cmd_stat = CMD_ARGS;
            }

        case CMD_ARGS:
            if (cmd_args_len == MAX_CMD_ARGS_LEN) {
                snprintf(err_msg, 128, MSG_ERR_TEMP, "command too long");
                rvm_hal_uart_send(comm_handle, err_msg, strlen(err_msg), AOS_WAIT_FOREVER);
            } else {
                cmd_args[cmd_args_len++] = ch;
            }
            break;

        default:
            cmd_stat = CMD_IDLE;
            break;
    }

    return -1;
}

static int cli_parse(char *cmd_name, int cmd_type, char *args)
{
    char reply_msg[256];

    // printf("cli parse %s %d %s\n", cmd_name, cmd_type, args);

    if (cmd_type == CMD_AT_2) {
        rvm_hal_uart_send(comm_handle, "OK\r\n", 4, AOS_WAIT_FOREVER);
    } else {
        cmd_list_t *node;
        int found = 0;
        slist_for_each_entry(&cmd_lists, node, cmd_list_t, next)
        {
            if (strcmp(cmd_name, node->name) == 0) {
                found = 1;
                break;
            }
        }

        if (found) {
            if (cmd_type == CMD_TEST) {
                snprintf(reply_msg, 256, MSG_TEST_TEMP, cmd_name, node->help);
                rvm_hal_uart_send(comm_handle, reply_msg, strlen(reply_msg), AOS_WAIT_FOREVER);
            } else {
                if (exe_stat == EXE_RUNNING) {
                    rvm_hal_uart_send(comm_handle, MSG_STILL_RUN_TEMP, strlen(MSG_STILL_RUN_TEMP), AOS_WAIT_FOREVER);
                    return -1;
                }

                strncpy(cmd_args_cp, args, MAX_CMD_ARGS_LEN);
                memset(arg_items, 0, MAX_CMD_ARG_NUM * sizeof(char *));
                int count = strsplit(arg_items, MAX_CMD_ARG_NUM, cmd_args_cp, ",");

                if (fct_run_test(node->cmd_id, cmd_type == CMD_QUERY, count, arg_items)) {
                    rvm_hal_uart_send(comm_handle, MSG_RUN_FAIL_TEMP, strlen(MSG_RUN_FAIL_TEMP), AOS_WAIT_FOREVER);
                    return -1;
                }

                exe_stat = EXE_RUNNING;
                return 0;
            }
        } else {
            snprintf(reply_msg, 256, MSG_NOT_FOUND_TEMP);
            rvm_hal_uart_send(comm_handle, reply_msg, strlen(reply_msg), AOS_WAIT_FOREVER);
        }
    }

    return -1;
}
static int fct_running=1;
static aos_event_t fct_comm_event;
static void tsk_fct_comm(void *arg)
{
    char ch = '\0';

    while (fct_running) {
        /* if received command from PC, process it */
        if (rvm_hal_uart_recv(comm_handle, &ch, 1, 100) > 0) {
            int_fast8_t ret;

            while (1) {
                int ret_stat = ch_parse(ch);
                if (ret_stat >= 0) {
                    ret = cli_parse(cmd_name, ret_stat, cmd_args);
                    if (ret == 0) {
                        exe_stat = EXE_RUNNING;
                    }
                }

                int len = rvm_hal_uart_recv(comm_handle, &ch, 1, 0);

                if (len <= 0)
                    break;
            }
        }

        /* if last command finished, send the reply to PC*/
        if (exe_stat == EXE_RUNNING) {
            if (fct_state() == TEST_END || fct_state() == TEST_ERROR) {
                exe_stat = EXE_FINISHED;

                char reply_msg[256];
                char *result = fct_get_result();

                if (fct_state() == TEST_END) {
                    if (strlen(result) == 0) {
                        strcpy(reply_msg, SUCCESS_MSG);
                    } else {
                        snprintf(reply_msg, 256, MSG_REPLY_TEMP, cmd_name, result);
                    }
                } else {
                    snprintf(reply_msg, 256, MSG_ERR_TEMP, result);
                }

                rvm_hal_uart_send(comm_handle, reply_msg, strlen(reply_msg), AOS_WAIT_FOREVER);
            } 
        }
    }
    aos_event_set(&fct_comm_event, 0x1, AOS_EVENT_OR);
}
int fct_comm_init(int uart_id, uint32_t baud_rate)
{
    rvm_hal_uart_config_t config;
    int ret;
    uint32_t flags = 0;
    
    if (comm_handle) {
        return -EBUSY;
    }
    char buf_n[16];
    snprintf(buf_n, sizeof(buf_n), "uart%d", uart_id);
    comm_handle = rvm_hal_uart_open(buf_n);
    CHECK_RET_WITH_RET(comm_handle != NULL, -1);
    rvm_hal_uart_config_default(&config);
    config.baud_rate = baud_rate;
    rvm_hal_uart_config(comm_handle, &config);
    rvm_hal_uart_set_type(comm_handle, UART_TYPE_ASYNC);
    // rvm_hal_uart_set_event(&fct_handle, cli_uart_event, NULL);

    cmd_name = malloc(MAX_CMD_NAME_LEN + 1);
    cmd_args = malloc(MAX_CMD_ARGS_LEN + 1);
    cmd_args_cp = malloc(MAX_CMD_ARGS_LEN + 1);
    arg_items = (char **)malloc(MAX_CMD_ARG_NUM * sizeof(char *));

    ret = aos_event_new(&fct_comm_event, flags);
    if (ret != 0) {
        printf("event create failed\n");
        return -1;
    }
    ret = aos_task_new_ext(&tsk_comm, "fcomm", tsk_fct_comm, NULL, 3 * 1024, AOS_DEFAULT_APP_PRI);
    CHECK_RET_WITH_RET(ret == 0, ret);

    return 0;
}
void fct_comm_deinit(void)
{
    uint32_t actl_flags;

    fct_running=0;
    aos_event_get(&fct_comm_event, 0x1, AOS_EVENT_OR_CLEAR, &actl_flags, AOS_WAIT_FOREVER);
    rvm_hal_uart_close(comm_handle);
    
    free(cmd_name);
    free(cmd_args);
    free(cmd_args_cp);
    free(arg_items);
}
int fct_comm_reg_cmd(const char *name, const char *help, int cmd_id)
{
    cmd_list_t *temp_cmd_node;
    slist_for_each_entry(&cmd_lists, temp_cmd_node, cmd_list_t, next)
    {
        if (strcmp(temp_cmd_node->name, name) == 0) {
            return -EINVAL;
        }
    }

    cmd_list_t *cmd_node = (cmd_list_t *)aos_malloc(sizeof(cmd_list_t));

    if (cmd_node == NULL) {
        return -1;
    }

    cmd_node->name = name;
    cmd_node->help = help;
    cmd_node->cmd_id = cmd_id;
    slist_add_tail(&cmd_node->next, &cmd_lists);

    return 0;
}

int fct_comm_unreg_cmd(const char *name)
{
    if (NULL == name) {
        return -EINVAL;
    }

    cmd_list_t *cmd_node;
    slist_for_each_entry(&cmd_lists, cmd_node, cmd_list_t, next)
    {
        if (strcmp(cmd_node->name, name) == 0) {
            slist_del(&cmd_node->next, &cmd_lists);
            aos_free(cmd_node);
            break;
        }
    }

    return 0;
}


slist_t fct_comm_get_cmd_list(void)
{
    return cmd_lists;
}
