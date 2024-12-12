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

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __SND_SND__
#define __SND_SND__

// typedef struct snd_card_drv {
//     slist_t          pcm_head;
// } snd_card_drv_t;

// typedef struct snd_dev {
//     void           *priv;
// } card_dev_t;

// typedef struct module
// {
//     char test;
// } module_t;

//提供声卡注册和查询

// int aos_card_new(int *parent, int idx, const char *xid, struct module *module, int size, snd_card_drv_t **card_ret);
// int aos_card_free(snd_card_drv_t *card);
// int aos_card_attach(const char *name, card_dev_t **card);
int aos_card_lpm(const char *name ,int state);

#ifdef __cplusplus
}
#endif

#endif