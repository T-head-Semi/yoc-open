/*
 * Copyright (C) 2017-2019 Alibaba Group Holding Limited
 */

/******************************************************************************
 * @file     pmu_regs.h
 * @brief    header file for the pmu
 * @version  V1.0
 * @date     07. Aug 2019
 * @vendor   csky
 * @chip     pangu
 ******************************************************************************/

#ifndef _PMU_REGS_
#define _PMU_REGS_

/* PMU_CLKSRCSEL, Offset: 0x0 */
#define PMU_CLKSRCSEL_EILS_SEL_Pos       0U
#define PMU_CLKSRCSEL_EILS_SEL_Msk       (0x1U << PMU_CLKSRCSEL_EILS_SEL_Pos)
#define PMU_CLKSRCSEL_EILS_SEL_ILS       PMU_CLKSRCSEL_EILS_SEL_Msk

/* PMU_SYSCLKDIVEN, Offset: 0x4 */
#define PMU_SYSCLKDIVEN_D0_EN_Pos        0U
#define PMU_SYSCLKDIVEN_D0_EN_Msk        (0x1U << PMU_SYSCLKDIVEN_D0_EN_Pos)
#define PMU_SYSCLKDIVEN_D0_EN            PMU_SYSCLKDIVEN_D0_EN_Msk
#define PMU_SYSCLKDIVEN_D0_DIV_Pos       4U
#define PMU_SYSCLKDIVEN_D0_DIV_Msk       (0xFU << PMU_SYSCLKDIVEN_D0_DIV_Pos)
#define PMU_SYSCLKDIVEN_D0_DIV(n)        (((n) - 2) << PMU_SYSCLKDIVEN_D0_DIV_Pos)
#define PMU_SYSCLKDIVEN_D1_EN_Pos        8U
#define PMU_SYSCLKDIVEN_D1_EN_Msk        (0x1U << PMU_SYSCLKDIVEN_D1_EN_Pos)
#define PMU_SYSCLKDIVEN_D1_EN            PMU_SYSCLKDIVEN_D1_EN_Msk
#define PMU_SYSCLKDIVEN_D1_DIV_Pos       12U
#define PMU_SYSCLKDIVEN_D1_DIV_Msk       (0xFU << PMU_SYSCLKDIVEN_D1_DIV_Pos)
#define PMU_SYSCLKDIVEN_D1_DIV(n)        (((n) - 2) << PMU_SYSCLKDIVEN_D1_DIV_Pos)
#define PMU_SYSCLKDIVEN_D2_EN_Pos        16U
#define PMU_SYSCLKDIVEN_D2_EN_Msk        (0x1U << PMU_SYSCLKDIVEN_D2_EN_Pos)
#define PMU_SYSCLKDIVEN_D2_EN            PMU_SYSCLKDIVEN_D2_EN_Msk
#define PMU_SYSCLKDIVEN_D2_DIV_Pos       20U
#define PMU_SYSCLKDIVEN_D2_DIV_Msk       (0x7U << PMU_SYSCLKDIVEN_D2_DIV_Pos)
#define PMU_SYSCLKDIVEN_D2_DIV(n)        (((n) - 2) << PMU_SYSCLKDIVEN_D2_DIV_Pos)

/* PMU_CPU12SWRST, Offset: 0x8 */
#define PMU_CPU12SWRST_CPU1_RST_EN_Pos   0U
#define PMU_CPU12SWRST_CPU1_RST_EN_Msk   (0x1U << PMU_CPU12SWRST_CPU1_RST_EN_Pos)
#define PMU_CPU12SWRST_CPU1_RST_EN       PMU_CPU12SWRST_CPU1_RST_EN_Msk
#define PMU_CPU12SWRST_CPU2_RST_EN_Pos   1U
#define PMU_CPU12SWRST_CPU2_RST_EN_Msk   (0x1U << PMU_CPU12SWRST_CPU2_RST_EN_Pos)
#define PMU_CPU12SWRST_CPU2_RST_EN       PMU_CPU12SWRST_CPU2_RST_EN_Msk

/* PMU_PLLCTRL, Offset: 0xC */
#define PMU_PLLCTRL_PLL_LOCK_STA_Pos      0U
#define PMU_PLLCTRL_PLL_LOCK_STA_Msk      (0x1U << PMU_PLLCTRL_PLL_LOCK_STA_Pos)
#define PMU_PLLCTRL_PLL_LOCK_STA_LOCK     PMU_PLLCTRL_PLL_LOCK_STA_Msk
#define PMU_PLLCTRL_PLL_BYPASS_Pos        2U
#define PMU_PLLCTRL_PLL_BYPASS_Msk        (0x1U << PMU_PLLCTRL_PLL_BYPASS_Pos)
#define PMU_PLLCTRL_PLL_BYPASS_EN         PMU_PLLCTRL_PLL_BYPASS_Msk
#define PMU_PLLCTRL_PLL_DACPD_Pos         3U
#define PMU_PLLCTRL_PLL_DACPD_Msk         (0x1U << PMU_PLLCTRL_PLL_DACPD_Pos)
#define PMU_PLLCTRL_PLL_POSTDIV1_Pos      4U
#define PMU_PLLCTRL_PLL_POSTDIV1_Msk      (0x7U << PMU_PLLCTRL_PLL_POSTDIV1_Pos)
#define PMU_PLLCTRL_PLL_POSTDIV1(n)       ((n) << PMU_PLLCTRL_PLL_POSTDIV1_Pos)
#define PMU_PLLCTRL_PLL_FOUT4PHASEPD_Pos  7U
#define PMU_PLLCTRL_PLL_FOUT4PHASEPD_Msk  (0x1U << PMU_PLLCTRL_PLL_FOUT4PHASEPD_Pos)
#define PMU_PLLCTRL_PLL_POSTDIV2_Pos      8U
#define PMU_PLLCTRL_PLL_POSTDIV2_Msk      (0x7U << PMU_PLLCTRL_PLL_POSTDIV2_Pos)
#define PMU_PLLCTRL_PLL_POSTDIV2(n)       ((n) << PMU_PLLCTRL_PLL_POSTDIV2_Pos)
#define PMU_PLLCTRL_PLL_FOUTPOSTDIVPD_Pos 11U
#define PMU_PLLCTRL_PLL_FOUTPOSTDIVPD_Msk (0x1U << PMU_PLLCTRL_PLL_FOUTPOSTDIVPD_Pos)
#define PMU_PLLCTRL_PLL_REFDIV_Pos        12U
#define PMU_PLLCTRL_PLL_REFDIV_Msk        (0x3FU << PMU_PLLCTRL_PLL_REFDIV_Pos)
#define PMU_PLLCTRL_PLL_FOUTVCOPD_Pos     18U
#define PMU_PLLCTRL_PLL_FOUTVCOPD_Msk     (0x1U << PMU_PLLCTRL_PLL_FOUTVCOPD_Pos)
#define PMU_PLLCTRL_PLL_FBDIV_Pos         20U
#define PMU_PLLCTRL_PLL_FBDIV_Msk         (0xFFFU << PMU_PLLCTRL_PLL_FBDIV_Pos)
#define PMU_PLLCTRL_PLL_FBDIV(n)          ((n) << PMU_PLLCTRL_PLL_FBDIV_Pos)

/* PMU_PLLCTRL_FRAC, Offset: 0x10 */
#define PMU_PLLCTRL_FRAC_PLL_LOCK_STA_Pos      0U
#define PMU_PLLCTRL_FRAC_PLL_LOCK_STA_Msk      (0x1U << PMU_PLLCTRL_FRAC_PLL_LOCK_STA_Pos)
#define PMU_PLLCTRL_FRAC_PLL_LOCK_STA_LOCK     PMU_PLLCTRL_FRAC_PLL_LOCK_STA_Msk
#define PMU_PLLCTRL_FRAC_PLL_BYPASS_Pos        2U
#define PMU_PLLCTRL_FRAC_PLL_BYPASS_Msk        (0x1U << PMU_PLLCTRL_FRAC_PLL_BYPASS_Pos)
#define PMU_PLLCTRL_FRAC_PLL_BYPASS_EN         PMU_PLLCTRL_FRAC_PLL_BYPASS_Msk
#define PMU_PLLCTRL_FRAC_PLL_DACPD_Pos         3U
#define PMU_PLLCTRL_FRAC_PLL_DACPD_Msk         (0x1U << PMU_PLLCTRL_FRAC_PLL_DACPD_Pos)
#define PMU_PLLCTRL_FRAC_PLL_POSTDIV1_Pos      4U
#define PMU_PLLCTRL_FRAC_PLL_POSTDIV1_Msk      (0x7U << PMU_PLLCTRL_FRAC_PLL_POSTDIV1_Pos)
#define PMU_PLLCTRL_FRAC_PLL_POSTDIV1(n)       ((n) << PMU_PLLCTRL_FRAC_PLL_POSTDIV1_Pos)
#define PMU_PLLCTRL_FRAC_PLL_FOUT4PHASEPD_Pos  7U
#define PMU_PLLCTRL_FRAC_PLL_FOUT4PHASEPD_Msk  (0x1U << PMU_PLLCTRL_FRAC_PLL_FOUT4PHASEPD_Pos)
#define PMU_PLLCTRL_FRAC_PLL_POSTDIV2_Pos      8U
#define PMU_PLLCTRL_FRAC_PLL_POSTDIV2_Msk      (0x7U << PMU_PLLCTRL_FRAC_PLL_POSTDIV2_Pos)
#define PMU_PLLCTRL_FRAC_PLL_POSTDIV2(n)       ((n) << PMU_PLLCTRL_FRAC_PLL_POSTDIV2_Pos)
#define PMU_PLLCTRL_FRAC_PLL_FOUTPOSTDIVPD_Pos 11U
#define PMU_PLLCTRL_FRAC_PLL_FOUTPOSTDIVPD_Msk (0x1U << PMU_PLLCTRL_FRAC_PLL_FOUTPOSTDIVPD_Pos)
#define PMU_PLLCTRL_FRAC_PLL_REFDIV_Pos        12U
#define PMU_PLLCTRL_FRAC_PLL_REFDIV_Msk        (0x3FU << PMU_PLLCTRL_FRAC_PLL_REFDIV_Pos)
#define PMU_PLLCTRL_FRAC_PLL_FOUTVCOPD_Pos     18U
#define PMU_PLLCTRL_FRAC_PLL_FOUTVCOPD_Msk     (0x1U << PMU_PLLCTRL_FRAC_PLL_FOUTVCOPD_Pos)
#define PMU_PLLCTRL_FRAC_PLL_FBDIV_Pos         20U
#define PMU_PLLCTRL_FRAC_PLL_FBDIV_Msk         (0xFFFU << PMU_PLLCTRL_FRAC_PLL_FBDIV_Pos)
#define PMU_PLLCTRL_FRAC_PLL_FBDIV(n)          ((n) << PMU_PLLCTRL_FRAC_PLL_FBDIV_Pos)

/* PMU_LPCR, Offset: 0x14 */
#define PMU_LPCR_LPEN_Pos                      0U
#define PMU_LPCR_LPEN_Msk                      (0x1U << PMU_LPCR_LPEN_Pos)
#define PMU_LPCR_LPEN                          PMU_LPCR_LPEN_Msk
#define PMU_LPCR_CHANGE_VOLT_Pos               1U
#define PMU_LPCR_CHANGE_VOLT_Msk               (0x1U << PMU_LPCR_CHANGE_VOLT_Pos)
#define PMU_LPCR_CHANGE_VOLT_ENTER_HW_VAD1     PMU_LPCR_CHANGE_VOLT_Msk
#define PMU_LPCR_SW_TRIGGER_Pos                2U
#define PMU_LPCR_SW_TRIGGER_Msk                (0x1U << PMU_LPCR_SW_TRIGGER_Pos)
#define PMU_LPCR_SW_TRIGGER                    PMU_LPCR_SW_TRIGGER_Msk
#define PMU_LPCR_BOOT_FROM_LP_Pos              3U
#define PMU_LPCR_BOOT_FROM_LP_Msk              (0x1U << PMU_LPCR_BOOT_FROM_LP_Pos)
#define PMU_LPCR_BOOT_FROM_LP                  PMU_LPCR_BOOT_FROM_LP_Msk

/* PMU_WKUPMASK, Offset: 0x18 */
#define PMU_WKUPMASK_GPIO_MASK_EN_Pos          0U
#define PMU_WKUPMASK_GPIO_MASK_EN_Msk          (0x1 << PMU_WKUPMASK_GPIO_MASK_EN_Pos)
#define PMU_WKUPMASK_GPIO_MASK_EN              PMU_WKUPMASK_GPIO_MASK_EN_Msk
#define PMU_WKUPMASK_AONTIM_MASK_EN_Pos        1U
#define PMU_WKUPMASK_AONTIM_MASK_EN_Msk        (0x1U << PMU_WKUPMASK_AONTIM_MASK_EN_Pos)
#define PMU_WKUPMASK_AONTIM_MASK_EN            PMU_WKUPMASK_AONTIM_MASK_EN_Msk
#define PMU_WKUPMASK_RTC_MASK_EN_Pos           2U
#define PMU_WKUPMASK_RTC_MASK_EN_Msk           (0x1U << PMU_WKUPMASK_RTC_MASK_EN_Pos)
#define PMU_WKUPMASK_RTC_MASK_EN               PMU_WKUPMASK_RTC_MASK_EN_Msk
#define PMU_WKUPMASK_CODEC_WT_MASK_EN_Pos      3U
#define PMU_WKUPMASK_CODEC_WT_MASK_EN_Msk      (0x1U << PMU_WKUPMASK_CODEC_WT_MASK_EN_Pos)
#define PMU_WKUPMASK_CODEC_WT_MASK_EN          PMU_WKUPMASK_CODEC_WT_MASK_EN_Msk

/* PMU_RSTSTA, Offset: 0x1C */
#define PMU_RSTSTA_POR_RST_FLAG_Pos            0U
#define PMU_RSTSTA_POR_RST_FLAG_Msk            (0x1U << PMU_RSTSTA_POR_RST_FLAG_Pos)
#define PMU_RSTSTA_POR_RST                     PMU_RSTSTA_POR_RST_FLAG_Msk
#define PMU_RSTSTA_MCU_RST_FLAG_Pos            1U
#define PMU_RSTSTA_MCU_RST_FLAG_Msk            (0x1U << PMU_RSTSTA_MCU_RST_FLAG_Pos)
#define PMU_RSTSTA_MCU_RST                     PMU_RSTSTA_MCU_RST_FLAG_Msk
#define PMU_RSTSTA_WDG_RST_FLAG_Pos            2U
#define PMU_RSTSTA_WDG_RST_FLAG_Msk            (0x1U << PMU_RSTSTA_WDG_RST_FLAG_Pos)
#define PMU_RSTSTA_WDG_RST                     PMU_RSTSTA_WDG_RST_FLAG_Msk
#define PMU_RSTSTA_CPU0_RST_FLAG_Pos           3U
#define PMU_RSTSTA_CPU0_RST_FLAG_Msk           (0x1U << PMU_RSTSTA_CPU0_RST_FLAG_Pos)
#define PMU_RSTSTA_CPU0_RST                    PMU_RSTSTA_CPU0_RST_FLAG_Msk

/* PMU_RCCTRL, Offset: 0x20 */
#define PMU_RCCTRL_ILS_RC_TRIM_Pos             0U
#define PMU_RCCTRL_ILS_RC_TRIM_Msk             (0x3FU << PMU_RCCTRL_ILS_RC_TRIM_Pos)
#define PMU_RCCTRL_ILS_RC_TRIM(n)              ((n) << PMU_RCCTRL_ILS_RC_TRIM_Pos)
#define PMU_RCCTRL_ILS_CLK_EN_Pos              16U
#define PMU_RCCTRL_ILS_CLK_EN_Msk              (0x3U << PMU_RCCTRL_ILS_CLK_EN_Pos)
#define PMU_RCCTRL_ILS_CLK_EN                  PMU_RCCTRL_ILS_CLK_EN_Msk
#define PMU_RCCTRL_ELS_CLK_EN_Pos              19U
#define PMU_RCCTRL_ELS_CLK_EN_Msk              (0x1U << PMU_RCCTRL_ELS_CLK_EN_Pos)
#define PMU_RCCTRL_ELS_CLK_EN                  PMU_RCCTRL_ELS_CLK_EN_Msk
#define PMU_RCCTRL_ELS_CLK_BYPASS_Pos          20U
#define PMU_RCCTRL_ELS_CLK_BYPASS_Msk          (0x1U << PMU_RCCTRL_ELS_CLK_BYPASS_Pos)
#define PMU_RCCTRL_ELS_CLK_BYPASS              PMU_RCCTRL_ELS_CLK_BYPASS_Msk

/* PMU_LPSTA, Offset: 0x24 */
#define PMU_LPSTA_CPU0_LP_STA_Pos              0U
#define PMU_LPSTA_CPU0_LP_STA_Msk              (0x3U << PMU_LPSTA_CPU0_LP_STA_Pos)
#define PMU_LPSTA_CPU1_LP_STA_Pos              2U
#define PMU_LPSTA_CPU1_LP_STA_Msk              (0x3U << PMU_LPSTA_CPU0_LP_STA_Pos)
#define PMU_LPSTA_CPU2_LP_STA_Pos              4U
#define PMU_LPSTA_CPU2_LP_STA_Msk              (0x3U << PMU_LPSTA_CPU0_LP_STA_Pos)

/* PMU_LVMD, Offset: 0x28 */
#define PMU_LVMD_LV_MD_INTR_Pos                0U
#define PMU_LVMD_LV_MD_INTR_Msk                (0x1U << PMU_LVMD_LV_MD_INTR_Pos)

/* PMU_REQMDTRIG, Offset: 0x2C */
#define PMU_REQMDTRIG_CHANGEMODE_REQ_Pos       0U
#define PMU_REQMDTRIG_CHANGEMODE_REQ_Msk       (0x1U << PMU_REQMDTRIG_CHANGEMODE_REQ_Pos)
#define PMU_REQMDTRIG_CHANGEMODE_REQ           PMU_REQMDTRIG_CHANGEMODE_REQ_Msk

/* PMU_PERIERRSTA, Offset: 0x30 */
//TODO

/* PMU_PLLINTRCTRL, Offset: 0x34 */
#define PMU_PLLINTRCTRL_PLL_LOSELOCK_EN_Pos         0U
#define PMU_PLLINTRCTRL_PLL_LOSELOCK_EN_Msk         (0x1U << PMU_PLLINTRCTRL_PLL_LOSELOCK_EN_Pos)
#define PMU_PLLINTRCTRL_PLL_LOSELOCK_EN             PMU_PLLINTRCTRL_PLL_LOSELOCK_EN_Msk
#define PMU_PLLINTRCTRL_PLL_LOSELOCK_EN_FRAC_Pos    1U
#define PMU_PLLINTRCTRL_PLL_LOSELOCK_EN_FRAC_Msk    (0x1U << PMU_PLLINTRCTRL_PLL_LOSELOCK_EN_FRAC_Pos)
#define PMU_PLLINTRCTRL_PLL_LOSELOCK_EN_FRAC        PMU_PLLINTRCTRL_PLL_LOSELOCK_EN_FRAC_Msk
#define PMU_PLLINTRCTRL_PLL_LOSELOCK_CLR_Pos        2U
#define PMU_PLLINTRCTRL_PLL_LOSELOCK_CLR_Msk        (0x1U << PMU_PLLINTRCTRL_PLL_LOSELOCK_CLR_Pos)
#define PMU_PLLINTRCTRL_PLL_LOSELOCK_CLR            PMU_PLLINTRCTRL_PLL_LOSELOCK_CLR_Msk
#define PMU_PLLINTRCTRL_PLL_LOSELOCK_CLR_FRAC_Pos   3U
#define PMU_PLLINTRCTRL_PLL_LOSELOCK_CLR_FRAC_Msk   (0x1U << PMU_PLLINTRCTRL_PLL_LOSELOCK_CLR_FRAC_Pos)
#define PMU_PLLINTRCTRL_PLL_LOSELOCK_CLR_FRAC       PMU_PLLINTRCTRL_PLL_LOSELOCK_CLR_FRAC_Msk
#define PMU_PLLINTRCTRL_PLL_LOCK_EN_Pos             4U
#define PMU_PLLINTRCTRL_PLL_LOCK_EN_Msk             (0x1U << PMU_PLLINTRCTRL_PLL_LOCK_EN_Pos)
#define PMU_PLLINTRCTRL_PLL_LOCK_EN                 PMU_PLLINTRCTRL_PLL_LOCK_EN_Msk
#define PMU_PLLINTRCTRL_PLL_LOCK_EN_FRAC_Pos        5U
#define PMU_PLLINTRCTRL_PLL_LOCK_EN_FRAC_Msk        (0x1U << PMU_PLLINTRCTRL_PLL_LOCK_EN_FRAC_Pos)
#define PMU_PLLINTRCTRL_PLL_LOCK_EN_FRAC            PMU_PLLINTRCTRL_PLL_LOCK_EN_FRAC_Msk
#define PMU_PLLINTRCTRL_PLL_LOCK_CLR_Pos            6U
#define PMU_PLLINTRCTRL_PLL_LOCK_CLR_Msk            (0x1U << PMU_PLLINTRCTRL_PLL_LOCK_CLR_Pos)
#define PMU_PLLINTRCTRL_PLL_LOCK_CLR                PMU_PLLINTRCTRL_PLL_LOCK_CLR_Msk
#define PMU_PLLINTRCTRL_PLL_LOCK_CLR_FRAC_Pos       7U
#define PMU_PLLINTRCTRL_PLL_LOCK_CLR_FRAC_Msk       (0x1U << PMU_PLLINTRCTRL_PLL_LOCK_CLR_FRAC_Pos)
#define PMU_PLLINTRCTRL_PLL_LOCK_CLR_FRAC           PMU_PLLINTRCTRL_PLL_LOCK_CLR_FRAC_Msk

/* PMU_FRACPLLFRAC, Offset: 0x38 */
#define PMU_FRACPLLFRAC_FRAC_PLL_FRAC_Pos           0U
#define PMU_FRACPLLFRAC_FRAC_PLL_FRAC_Msk           (0xFFFFFFU << PMU_FRACPLLFRAC_FRAC_PLL_FRAC_Pos)
#define PMU_FRACPLLFRAC_FRAC_PLL_FRAC(n)            ((n) << PMU_FRACPLLFRAC_FRAC_PLL_FRAC_Pos)

/* PMU_BOOTADDR_BYPASS, Offset: 0x48 */
#define PMU_BOOTADDR_BYPASS_BOOTADDR_BYPASS_Pos     0U
#define PMU_BOOTADDR_BYPASS_BOOTADDR_BYPASS_Msk     (0x1U << PMU_BOOTADDR_BYPASS_BOOTADDR_BYPASS_Pos)
#define PMU_BOOTADDR_BYPASS_BOOTADDR_BYPASS         PMU_BOOTADDR_BYPASS_BOOTADDR_BYPASS_Msk

/* PMU_AONTIMCTRL, Offset: 0x4C */
#define PMU_AONTIMCTRL_PCLK_CG_EN_Pos                 0U
#define PMU_AONTIMCTRL_PCLK_CG_EN_Msk                 (0x1U << PMU_AONTIMCTRL_PCLK_CG_EN_Pos)
#define PMU_AONTIMCTRL_PCLK_CG_EN                     PMU_AONTIMCTRL_PCLK_CG_EN_Msk
#define PMU_AONTIMCTRL_CNT_CG_EN_Pos                  4U
#define PMU_AONTIMCTRL_CNT_CG_EN_Msk                  (0x1U << PMU_AONTIMCTRL_CNT_CG_EN_Pos)
#define PMU_AONTIMCTRL_CNT_CG_EN                      PMU_AONTIMCTRL_CNT_CG_EN_Msk
#define PMU_AONTIMCTRL_SERIE_SEL_Pos                  8U
#define PMU_AONTIMCTRL_SERIE_SEL_Msk                  (0x1U << PMU_AONTIMCTRL_SERIE_SEL_Pos)
#define PMU_AONTIMCTRL_SERIE_SEL                      PMU_AONTIMCTRL_SERIE_SEL_Msk

/* PMU_AONTIMRST, Offset: 0x54 */
#define PMU_AONTIMRST_CNT0_RST_EN_Pos              0U
#define PMU_AONTIMRST_CNT0_RST_EN_Msk              (0x1U << PMU_AONTIMRST_CNT0_RST_EN_Pos)
#define PMU_AONTIMRST_CNT0_RST_EN                  PMU_AONTIMRST_CNT0_RST_EN_Msk
#define PMU_AONTIMRST_CNT1_RST_EN_Pos              1U
#define PMU_AONTIMRST_CNT1_RST_EN_Msk              (0x1U << PMU_AONTIMRST_CNT1_RST_EN_Pos)
#define PMU_AONTIMRST_CNT1_RST_EN                  PMU_AONTIMRST_CNT1_RST_EN_Msk
#define PMU_AONTIMRST_PCLK_RST_EN_Pos              2U
#define PMU_AONTIMRST_PCLK_RST_EN_Msk              (0x1U << PMU_AONTIMRST_PCLK_RST_EN_Pos)
#define PMU_AONTIMRST_PCLK_RST_EN                  PMU_AONTIMRST_PCLK_RST_EN_Msk

/* PMU_AONRTCRST, Offset: 0x5C */
#define PMU_AONRTCRST_RTC_RST_EN_Pos                0U
#define PMU_AONRTCRST_RTC_RST_EN_Msk                (0x1U << PMU_AONRTCRST_RTC_RST_EN_Pos)
#define PMU_AONRTCRST_RTC_RST_EN                    PMU_AONRTCRST_RTC_RST_EN_Msk

/* PMU_AONGPIORST，Offset: 0x64 */
#define PMU_AONGPIORST_AONGPIO_RST_EN_Pos           0U
#define PMU_AONGPIORST_AONGPIO_RST_EN_Msk           (0x1U << PMU_AONGPIORST_AONGPIO_RST_EN_Pos)
#define PMU_AONGPIORST_AONGPIO_RST_EN               PMU_AONGPIORST_AONGPIO_RST_EN_Msk

/* PMU_RTCCLKCTRL */
#define PMU_RTCCLKCTRL_RTC_32K_CG_EN_Pos            0U
#define PMU_RTCCLKCTRL_RTC_32K_CG_EN_Msk            (0x1U << PMU_RTCCLKCTRL_RTC_32K_CG_EN_Pos)
#define PMU_RTCCLKCTRL_RTC_32K_CG_EN                PMU_RTCCLKCTRL_RTC_32K_CG_EN_Msk
#define PMU_RTCCLKCTRL_RTC_PCLK_CG_EN_Pos           4U
#define PMU_RTCCLKCTRL_RTC_PCLK_CG_EN_Msk           (0x1U << PMU_RTCCLKCTRL_RTC_PCLK_CG_EN_Pos)
#define PMU_RTCCLKCTRL_RTC_PCLK_CG_EN               PMU_RTCCLKCTRL_RTC_PCLK_CG_EN_Msk

typedef struct {
    __IOM uint32_t PMU_CLKSRCSEL;
    __IOM uint32_t PMU_SYSCLKDIVEN;
    __IOM uint32_t PMU_CPU12SWRST;
    __IOM uint32_t PMU_PLLCTRL;
    __IOM uint32_t PMU_PLLCTRL_FRAC;
    __IOM uint32_t PMU_LPCR;
    __IOM uint32_t PMU_WKUPMASK;
    __IOM  uint32_t PMU_RSTSTA;
    __IOM uint32_t PMU_RCCTRL;
    __IM  uint32_t PMU_LPSTA;
    __IM  uint32_t PMU_LVMD;
    __IOM uint32_t PMU_REQMDTRIG;
    __IM  uint32_t PMU_PERIERRSTA;
    __IOM uint32_t PMU_PLLINTRCTRL;
    __IOM uint32_t PMU_FRACPLLFRAC;
    uint32_t RESERVED0;
    __IOM uint32_t PMU_BOOTADDR_804_0;
    __IOM uint32_t PMU_BOOTADDR_805;
    __IOM uint32_t PMU_BOOTADDR_BYPASS;
    __IOM uint32_t PMU_AONTIMCTRL;
    uint32_t RESERVED1;
    __IOM uint32_t PMU_AONTIMRST;
    uint32_t RESERVED2;
    __IOM uint32_t PMU_AONRTCRST;
    uint32_t RESERVED3;
    __IOM uint32_t PMU_AONGPIORST;
    __IOM uint32_t PMU_LPBOOTADDR_804_0;
    __IOM uint32_t PMU_LPBOOTADDR_805;
    __IOM uint32_t PMU_QSPI_CNT;
    __IOM uint32_t PMU_WAIT_12M;
    __IOM uint32_t PMU_RTCCLKCTRL;
    uint32_t RESERVED4;
    __IOM uint32_t PMU_BOOTADDR_804_1;
    __IOM uint32_t PMU_LP_BOOTADDR_804_1;
    uint32_t RESERVED5[94];
    __IOM uint32_t DLC_PCTRL;
    __IOM uint32_t DLC_PRDATA;
    __IOM uint32_t DLC_SR;
    __IOM uint32_t DLC_IMR;
    __IOM uint32_t DLC_IFR;
    __IOM uint32_t DLC_IOIFR;
    __IOM uint32_t DLC_IDIFR;
    __IOM uint32_t DLC_IMCIFR;
} pmu_reg_t;

#endif
