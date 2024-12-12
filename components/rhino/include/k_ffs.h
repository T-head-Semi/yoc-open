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

#ifndef K_FFS_H
#define K_FFS_H

#ifdef __cplusplus
extern "C" {
#endif

/* function declarations */

extern int ffs32_lsb (uint32_t i);
extern int ffs32_msb (uint32_t i);

#define FFS_LSB(i)		ffs32_lsb(i)
#define FFS_MSB(i)		ffs32_msb(i)

#ifdef __cplusplus
}
#endif

#endif /* K_FFS_H */

