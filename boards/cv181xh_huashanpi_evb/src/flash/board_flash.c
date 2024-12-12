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

#include <board.h>

#include <stdlib.h>
#include <stdio.h>
#include <devices/blockdev.h>
#include <devices/devicelist.h>

void board_flash_init(void)
{
    rvm_spiflash_drv_register(0);
#if CONFIG_PARTITION_SUPPORT_EMMC
	rvm_hal_mmc_config_t mmc_config;
	memset(&mmc_config, 0, sizeof(rvm_hal_mmc_config_t));
	mmc_config.sdif = CONFIG_EMMC_SDIF;
	mmc_config.hostVoltageWindowVCC = kMMC_VoltageWindows270to360;
	mmc_config.default_busWidth = kMMC_DataBusWidth4bit;
	mmc_config.use_default_busWidth = 1;
	rvm_mmc_drv_register(0, &mmc_config);
#endif
    rvm_hal_sd_config_t sd_config;
    sd_config.sdif = CONFIG_SD_SDIF;
    rvm_sd_drv_register(0, &sd_config);

#if CONFIG_PARTITION_SUPPORT_SPINANDFLASH
    rvm_spinandflash_drv_register(0);
#endif
}
