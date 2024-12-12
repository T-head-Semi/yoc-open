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

extern void posix_cond_test_case(void);
extern void posix_dirent_test_case(void);
extern void posix_jump_test_case(void);
extern void posix_mutex_test_case(void);
extern void posix_pthread_attr_test_case(void);
extern void posix_sched_test_case(void);
extern void posix_pthread_test_case(void);
extern void posix_sem_test_case(void);
extern void posix_timer_test_case(void);
extern void posix_tsd_test_case(void);
extern void posix_enviro_test_case(void);
extern int posix_init(void);

void posix_test_entry(void)
{
    posix_init();
    posix_cond_test_case();
    //posix_dirent_test_case();
    posix_jump_test_case();
    posix_mutex_test_case();
    posix_pthread_attr_test_case();
    posix_sched_test_case();
    posix_pthread_test_case();
    posix_sem_test_case();
    posix_timer_test_case();
    posix_tsd_test_case();
    posix_enviro_test_case();
}
