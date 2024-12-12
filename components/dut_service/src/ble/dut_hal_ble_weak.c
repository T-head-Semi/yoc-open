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
#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
#include <string.h>
#include "dut/hal/ble.h"

int __attribute__((weak)) dut_hal_factorydata_read(uint32_t offset, uint8_t *buffer, uint32_t length)
{
    return 0;
}

int __attribute__((weak)) dut_hal_factorydata_store(uint32_t offset, uint8_t *buffer, uint32_t length)
{
    return 0;
}

int __attribute__((weak)) dut_hal_ble_tx_single_tone(uint8_t phy_fmt, uint8_t rf_chn_idx, uint32_t xtalcap, uint8_t txpower)
{
    return 0;
}

int __attribute__((weak)) dut_hal_ble_tx_mod_burst(uint8_t phy_fmt, uint8_t rf_chn_idx,uint32_t xtalcap, uint8_t txpower, uint8_t pkt_type)
{
    return 0;
}

int __attribute__((weak)) dut_hal_ble_rx_demod_burst(uint8_t phy_fmt, uint8_t rf_chn_idx, uint32_t xtalcap, int16_t *rx_freq_off, uint8_t *rx_rssi, uint8_t *rx_carr_sens, uint16_t *rx_pkt_num)
{
    return 0;
}

int __attribute__((weak)) dut_hal_mac_get(uint8_t addr[6])
{
    return 0;
}

int __attribute__((weak)) dut_hal_mac_store(uint8_t addr[6])
{
    return 0;
}

int __attribute__((weak)) dut_hal_sleep(uint8_t mode)
{
    return 0;
}

int __attribute__((weak)) dut_hal_xtalcap_get(uint32_t *xtalcap)
{
    return 0;
}

int __attribute__((weak)) dut_hal_xtalcap_store(uint32_t xtalcap)
{
    return 0;
}

int __attribute__((weak)) dut_hal_freqoff_get(int32_t *freqoff)
{
    return 0;
}

int __attribute__((weak)) dut_hal_freqoff_store(int32_t freqoff)
{
    return 0;
}

int __attribute__((weak)) dut_hal_ble_transmit_stop(void)
{
    return 0;
}

