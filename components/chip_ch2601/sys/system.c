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
 * @file     system.c
 * @brief    CSI Device System Source File
 * @version  V1.0
 * @date     02. Oct 2018
 ******************************************************************************/

#include <csi_config.h>
#include <soc.h>
#include <csi_core.h>
#include <drv/irq.h>
#include <drv/dma.h>
#include <drv/tick.h>
#include <drv/etb.h>
#include <drv/spiflash.h>
#include <drv/pin.h>

#if (defined(CONFIG_KERNEL_RHINO) || defined(CONFIG_KERNEL_FREERTOS) || defined(CONFIG_KERNEL_RTTHREAD)) && defined(CONFIG_KERNEL_NONE)
#error "Please check the current system is baremetal or not!!!"
#endif

csi_dma_t g_dma;
#ifdef CONFIG_XIP
csi_spiflash_t g_spiflash;
#endif
void section_data_copy(void);
void section_ram_code_copy(void);
void section_bss_clear(void);

void enable_theadisaee(void)
{
    uint32_t mxstatus = __get_MXSTATUS();
    mxstatus |= (1 << 22);
    __set_MXSTATUS(mxstatus);
}

static void sys_dma_init(void)
{
    csi_dma_init(&g_dma, 0);
}

static void cache_init(void)
{
    uint32_t cache;
    __DSB();
    __ISB();
    cache = 0x3; ///< only open icache and dcache
    __set_MHCR(cache);
    __DSB();
    __ISB();
}

static void section_init(void)
{
#ifdef CONFIG_XIP
    section_data_copy();
    section_ram_code_copy();
    soc_dcache_clean();
    soc_icache_invalid();
#endif

    section_bss_clear();
}

static void clic_init(void)
{
    int i;
//    CLIC->CLICCFG = 0x4UL;
    /* get interrupt level from info */
    CLIC->CLICCFG = (((CLIC->CLICINFO & CLIC_INFO_CLICINTCTLBITS_Msk) >> CLIC_INFO_CLICINTCTLBITS_Pos) << CLIC_CLICCFG_NLBIT_Pos);

    for (i = 0; i < 64; i++) {
        CLIC->CLICINT[i].IE = 0;
        CLIC->CLICINT[i].IP = 0;
        CLIC->CLICINT[i].ATTR = 1; /* use vector interrupt */
    }

    /* config csitimer tick irq priority */
    csi_vic_set_prio(DW_TIMER0_IRQn, 3U);

    /* tspend use positive interrupt */
    CLIC->CLICINT[Machine_Software_IRQn].ATTR = 0x3;
    csi_irq_enable(Machine_Software_IRQn);
}

static void interrupt_init(void)
{
    clic_init();
#ifdef CONFIG_KERNEL_NONE
    __enable_excp_irq();
#endif
}

#ifdef CONFIG_XIP
static void sys_spiflash_init(void)
{
    csi_spiflash_qspi_init(&g_spiflash, 0, NULL);
    csi_spiflash_config_data_line(&g_spiflash, SPIFLASH_DATA_4_LINES);
    csi_spiflash_frequence(&g_spiflash, 50000000U);
}
#endif

void bootrom_uart_uninit(void)
{
    csi_pin_set_mux(PA17, PIN_FUNC_GPIO);
    csi_pin_set_mux(PA18, PIN_FUNC_GPIO);
}
/**
  * @brief  initialize the system
  *         Initialize the psr and vbr.
  * @param  None
  * @return None
  */
void SystemInit(void)
{
    enable_theadisaee();

    cache_init();

    section_init();

    interrupt_init();

    soc_set_sys_freq(CPU_196_608MHZ);

    csi_etb_init();

    sys_dma_init();

    csi_tick_init();

#ifdef CONFIG_XIP
    sys_spiflash_init();
#endif
    bootrom_uart_uninit();
}

uint32_t soc_get_cpu_id(void)
{
    return 0;
}
