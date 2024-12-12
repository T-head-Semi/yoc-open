/*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef __DUT_CMD_BLE_H_
#define __DUT_CMD_BLE_H_

#include "dut_service.h"

typedef enum {
    //gpio config
    AUTO_MODE = 0,
    WRITE_MODE = 1,
    READ_MODE = 2,
} dut_gpio_cfg_e;
int dut_cmd_tx_single_tone(dut_cmd_type_e type, int argc, char *argv[]);

int dut_cmd_tx_mod_burst(dut_cmd_type_e type, int argc, char *argv[]);

int dut_cmd_rx_demod_burst(dut_cmd_type_e type, int argc, char *argv[]);

int dut_cmd_sleep(dut_cmd_type_e type, int argc, char *argv[]);

int dut_cmd_opt_mac(dut_cmd_type_e type, int argc, char *argv[]);

int dut_cmd_xtal_cap(dut_cmd_type_e type, int argc, char *argv[]);

int dut_cmd_transmit_stop(dut_cmd_type_e type, int argc, char *argv[]);

int dut_cmd_rx_current_test(dut_cmd_type_e type, int argc, char *argv[]);

int dut_cmd_freqoff(dut_cmd_type_e type, int argc, char *argv[]);

int dut_cmd_gpio_test(dut_cmd_type_e type, int argc, char *argv[]);
#endif
