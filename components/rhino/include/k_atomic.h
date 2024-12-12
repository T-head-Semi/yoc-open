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

#ifndef K_ATOMIC_H
#define K_ATOMIC_H

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned int    atomic_t;
typedef atomic_t        atomic_val_t;

extern atomic_val_t rhino_atomic_add(atomic_t *target, atomic_val_t value);
extern atomic_val_t rhino_atomic_sub(atomic_t *target, atomic_val_t value);
extern atomic_val_t rhino_atomic_inc(atomic_t *target);
extern atomic_val_t rhino_atomic_dec(atomic_t *target);
extern atomic_val_t rhino_atomic_set(atomic_t *target, atomic_val_t value);
extern atomic_val_t rhino_atomic_get(const atomic_t *target);
extern atomic_val_t rhino_atomic_or(atomic_t *target, atomic_val_t value);
extern atomic_val_t rhino_atomic_xor(atomic_t *target, atomic_val_t value);
extern atomic_val_t rhino_atomic_and(atomic_t *target, atomic_val_t value);
extern atomic_val_t rhino_atomic_nand(atomic_t *target, atomic_val_t value);
extern atomic_val_t rhino_atomic_clear(atomic_t *target);
extern int rhino_atomic_cas(atomic_t *target, atomic_val_t old_value,
			                atomic_val_t new_value);

#ifdef __cplusplus
}
#endif

#endif /* K_ATOMIC_H */

