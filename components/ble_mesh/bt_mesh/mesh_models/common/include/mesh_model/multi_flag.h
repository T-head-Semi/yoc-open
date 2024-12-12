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

#ifndef _MULTI_FLAG_H_
#define _MULTI_FLAG_H_

int  set_all_flags(uint8_t *set_octets_flags, uint16_t set_octets_number, uint16_t actual_number);
int  clear_all_flags(uint8_t *set_octets_flags, uint16_t set_octets_number, uint16_t actual_number);
int  clear_flag(uint8_t *set_octets_flags, uint16_t set_octets_number, uint16_t set_bit);
int  set_flag(uint8_t *set_octets_flags, uint16_t set_octets_number, uint16_t set_bit);
int  get_and_clear_flag(uint8_t *set_octets_flags, uint16_t set_octets_number, uint16_t actual_number,
                        uint16_t *set_bit);
bool is_flag_set(uint8_t *set_octets_flags, uint16_t set_octets_number, uint16_t number);
bool is_all_flags_set(uint8_t *set_octets_flags, uint16_t set_octets_number, uint16_t actual_number);
bool is_no_flag_set(uint8_t *set_octets_flags, uint16_t set_octets_number, uint16_t actual_number);

#endif
