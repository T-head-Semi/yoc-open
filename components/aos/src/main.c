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
 * @file     main.c
 * @brief    CSI Source File for main
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/

#include <yoc/sysinfo.h>
#include <yoc/yoc.h>

#ifdef CONFIG_OS_TRACE 
#include <trcTrig.h>
#include <trcKernelPort.h>
#endif


#ifndef CONFIG_INIT_TASK_STACK_SIZE
#define INIT_TASK_STACK_SIZE 8192
#else
#define INIT_TASK_STACK_SIZE CONFIG_INIT_TASK_STACK_SIZE
#endif
static aos_task_t app_task_handle;
extern int main(void);

static void components_init(void)
{
#if defined(AOS_COMP_VFS) && AOS_COMP_VFS
    extern int aos_vfs_init(void);
    aos_vfs_init();
#endif

}

static void application_task_entry(void *arg)
{
    components_init();

#if defined(CONFIG_SMP) && CONFIG_SMP
    aos_secondary_cpu_up();
#endif /* CONFIG_SMP */

    main();

    aos_task_exit(0);
}

void base_init()
{

}

int pre_main(void)
{
    /* kernel init */
    aos_init();
#ifdef CONFIG_OS_TRACE 
    trace_init_data();
#endif

    /* init task */
    aos_task_new_ext(&app_task_handle, "app_task", application_task_entry,
                     NULL, INIT_TASK_STACK_SIZE, AOS_DEFAULT_APP_PRI);

    /* kernel start */
    aos_start();

    return 0;
}
