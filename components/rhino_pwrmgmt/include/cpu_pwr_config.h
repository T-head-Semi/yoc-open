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

#ifndef __k_config_pwr_mgmt_h__
#define __k_config_pwr_mgmt_h__

/* cpu power management configuration */

#ifndef RHINO_CONFIG_CPU_TICKLESS
#define RHINO_CONFIG_CPU_TICKLESS               1
#endif

#ifndef RHINO_CONFIG_PWRMGMT_SHOW
#define RHINO_CONFIG_PWRMGMT_SHOW          0
#endif

#ifndef RHINO_CONFIG_CPU_PWR_P_STATE_SUPPORT
#define RHINO_CONFIG_CPU_PWR_P_STATE_SUPPORT    0
#endif

#ifndef RHINO_CONFIG_PWR_DEBUG
#define RHINO_CONFIG_PWR_DEBUG                  0
#endif

#ifndef RHINO_PWR_MGMT_ERR
#define RHINO_PWR_MGMT_ERR -1
#endif

#endif /* __k_config_pwr_mgmt_h__ */
