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

#include <stdio.h>
#include "board.h"

extern void benchmark_dhry_main(void);

int main(void)
{
    board_init();
    printf("bare_dhrystore demo start!\r\n");
#if CONFIG_CPU_XUANTIE_E902 || CONFIG_CPU_XUANTIE_E902M || CONFIG_CPU_XUANTIE_E902T || CONFIG_CPU_XUANTIE_E902MT
    // FIXME:
    csi_dcache_clean_invalid();
    csi_dcache_disable();
    csi_icache_disable();
#endif
    benchmark_dhry_main();
    return 0;
}
