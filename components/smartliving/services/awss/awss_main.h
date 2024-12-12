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



#ifndef __AWSS_MAIN_H__
#define __AWSS_MAIN_H__

#include "exports/iot_export_awss.h"
#include "awss_log.h"

#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

#define DEFAULT_SSID                   zc_default_ssid
#define DEFAULT_PASSWD                 zc_default_passwd
#define ADHA_SSID                      zc_adha_ssid
#define ADHA_PASSWD                    zc_adha_passwd

extern const char *zc_default_ssid;
extern const char *zc_default_passwd;
extern const char *zc_adha_ssid;
extern const char *zc_adha_passwd;

int __awss_start(pair_success_callback pair_cb);
int __awss_stop(void);

int awss_cancel_aha_monitor(void);

#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
}
#endif

#endif
