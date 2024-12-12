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

#ifndef __AWSS_BIND_STATIS_H__
#define __AWSS_BIND_STATIS_H__

#ifndef AWSS_SUPPORT_DEV_BIND_STATIS
#define AWSS_SUPPORT_DEV_BIND_STATIS
#endif

enum {
    AWSS_DB_STATIS_START,
    AWSS_DB_STATIS_SUC,
};

#ifdef AWSS_SUPPORT_DEV_BIND_STATIS
struct awss_statis_dev_bind_t {
    uint32_t dev_bind_cnt;        /* the count of token sync */
    uint32_t dev_bind_suc;        /* the successful count of token sync */
    uint32_t dev_bind_time_mean;  /* the mean time of token sync */
    uint32_t dev_bind_time_max;   /* the max time of token sync */
    uint32_t dev_bind_time_min;   /* the min time of token sync */
    uint32_t dev_bind_start;      /* the start time to sync token */
    uint32_t dev_bind_end;        /* the end time of token sync */
};  /* statistics for token sync */


int awss_bind_report_statis(const char *module);
void awss_bind_update_statis(int type);
void awss_bind_clear_statis();
void awss_bind_disp_statis();


#define AWSS_DB_UPDATE_STATIS(type) awss_bind_update_statis(type)
#define AWSS_DB_DISP_STATIS()       awss_bind_disp_statis()
#define AWSS_DB_CLEAR_STATIS()      awss_bind_clear_statis()
#define AWSS_DB_REPORT_STATIS(m)    awss_bind_report_statis(m)
#else
#define AWSS_DB_UPDATE_STATIS(type)
#define AWSS_DB_DISP_STATIS()
#define AWSS_DB_CLEAR_STATIS()
#define AWSS_DB_REPORT_STATIS(m)
#endif
#endif
