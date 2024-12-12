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
#ifndef __DUT_HAL_BLE_H_
#define __DUT_HAL_BLE_H_


int dut_hal_freqoff_get(int32_t *freqoff);

int dut_hal_freqoff_store(int32_t freqoff);

int dut_hal_xtalcap_get(uint32_t *xtalcap);

int dut_hal_xtalcap_store(uint32_t xtalcap);

/* API for ble test */
/**************************************************************************************
 * @fn          dut_hal_ble_tx_single_tone
 *
 * @brief       This function process for rf phy direct test
 *
 * input parameters
 *
 * @param 
 *              phy_fmt      :   PHY Format
 *              rf_chn_idx   :   rf channel = 2402+(rf_chn_idx<<1)
 *              xtalcap      :   xtal cap
 *              txpower      :   rf tx power
 *
 * output parameters
 *
 * @param       none
 *
 * @return      Success:0 ; Fail: < 0
 */
int dut_hal_ble_tx_single_tone(uint8_t phy_fmt, uint8_t rf_chn_idx, uint32_t xtalcap, uint8_t txpower);

/**************************************************************************************
 * @fn          dut_hal_ble_tx_mod_burst
 *
 * @brief       This function process for rf phy direct test
 *
 * input parameters
 *
 * @param
 *              phy_fmt      :   PHY Format
 *              rf_chn_idx   :   rf channel = 2402+(rf_chn_idx<<1)
 *              xtalcap      :   xtal cap
 *              txpower      :   rf tx power
 *              pkt_type     :   modulaiton data type, 0: prbs9, 1: 1111000: 2 10101010
 *
 * output parameters
 *
 * @param       none
 *
 * @return      Success:0 ; Fail: < 0
 */
int dut_hal_ble_tx_mod_burst(uint8_t phy_fmt, uint8_t rf_chn_idx, uint32_t xtalcap, uint8_t txpower, uint8_t pkt_type);

/**************************************************************************************
 * @fn          dut_hal_ble_rx_demod_burst
 *
 * @brief       This function process for rf phy direct test
 *
 * input parameters
 *
 * @param
 *              phy_fmt          :   PHY Format
 *              rf_chn_idx        :   rf channel = 2402+(rf_chn_idx<<1)
 *              xtalcap         :   xtal cap
 *
 * output parameters
 *
 * @param       rx_freq_off       :   rx demod estimated frequency offset
 *              rx_rssi       :   rx demod estimated rssi
 *              rx_carr_sens   :   rx demod estimated carrier sense
 *              rx_pkt_num        :   rx demod received pkt number
 *
 * @return      Success:0 ; Fail: < 0
 */
int dut_hal_ble_rx_demod_burst(uint8_t phy_fmt, uint8_t rf_chn_idx, uint32_t xtalcap, int16_t *rx_freq_off, uint8_t *rx_rssi, uint8_t *rx_carr_sens, uint16_t *rx_pkt_num);

/**************************************************************************************
 * @fn          dut_hal_ble_transmit_stop
 *
 * @brief       This function process for stop transmit
 *
 * input parameters
 *
 * @param       none
 *
 * output parameters
 *
 * @param       none
 *
 * @return      Success:0 ; Fail: < 0
 */
int dut_hal_ble_transmit_stop(void);

#endif
