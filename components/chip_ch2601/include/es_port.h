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

/******************************************************************************
 * @file     es_port.h
 * @brief
 * @version
 * @date     2020-10-16
 ******************************************************************************/

#ifndef _ES_PORT_H_
#define _ES_PORT_H_
#include <stdio.h>
#include <string.h>
#include <sys_clk.h>
#include <drv/iic.h>
#include <drv/pin.h>
#include <drv/common.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CODEC_IIC_IDX       0U
#define CODEC_IIC_SDA       PA9
#define CODEC_IIC_SCL       PA8
#define CODEC_IIC_SDA_FUNC  PA9_IIC0_SDA
#define CODEC_IIC_SCL_FUNC  PA8_IIC0_SCL

/**
  \brief  Init the IIC port
  \return error code
*/
csi_error_t es_port_iic_init(void);

/**
  \brief  IIC read date
  \param[in]   data            Pointer to send data buffer
  \param[in]   date_len        Size of data items to send
  \return      The amount of real data received or error code
*/
csi_error_t es_port_iic_read(uint8_t addr, uint8_t *data, uint32_t date_len);

/**
  \brief  IIC write data
  \param[in]   data            Pointer to send data buffer
  \param[in]   date_len        Size of data items to send
  \return      The amount of real data sent or error code
*/
csi_error_t es_port_iic_write(uint8_t addr, uint8_t *data, uint32_t date_len);

#ifdef __cplusplus
}
#endif

#endif  /* _ES_PORT_H_*/