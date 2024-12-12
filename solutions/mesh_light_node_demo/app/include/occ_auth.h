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
#ifndef _MESH_OCC_AUTH_H
#define _MESH_OCC_AUTH_H

#define OCC_AUTH_MESH_OOB_SIZE 8

int occ_auth_init(void);
int occ_auth_set_dev_mac_by_kp(void);
int occ_auth_get_uuid_and_oob(uint8_t uuid[16], uint32_t *short_oob);

#endif
