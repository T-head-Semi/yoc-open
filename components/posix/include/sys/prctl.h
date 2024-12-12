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

#ifndef _PRCTL_H
#define _PRCTL_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PR_SET_NAME: Set the name of the calling thread, using the value in the
 *              location pointed to by (char *) arg2.
 */
#define PR_SET_NAME 0x00000000

int prctl(int option, ...);

#ifdef __cplusplus
}
#endif

#endif /* _PRCTL_H */
