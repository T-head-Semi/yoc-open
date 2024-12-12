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

#ifndef __IOT_EXPORT_COMPAT_H__
#define __IOT_EXPORT_COMPAT_H__

#if defined(__cplusplus)
extern "C" {
#endif

/* for forward compatibility */

/* V2.3.0 */
#define IOTX_CLOUD_DOMAIN_SH        IOTX_CLOUD_REGION_SHANGHAI
#define IOTX_CLOUD_DOMAIN_SG        IOTX_CLOUD_REGION_SINGAPORE
#define IOTX_CLOUD_DOMAIN_JP        IOTX_CLOUD_REGION_JAPAN
#define IOTX_CLOUD_DOMAIN_US        IOTX_CLOUD_REGION_USA_WEST
#define IOTX_CLOUD_DOMAIN_GER       IOTX_CLOUD_REGION_GERMANY
#define IOTX_IOCTL_SET_DOMAIN       IOTX_IOCTL_SET_REGION
#define IOTX_IOCTL_GET_DOMAIN       IOTX_IOCTL_GET_REGION

#define IOT_OpenLog(arg)
#define IOT_CloseLog()              IOT_SetLogLevel(IOT_LOG_NONE)
#define IOT_LOG_EMERG               IOT_LOG_NONE

#define IOT_Linkkit_Post            IOT_Linkkit_Report

#if defined(__cplusplus)
}
#endif
#endif  /* __IOT_EXPORT_COMPAT_H__ */

