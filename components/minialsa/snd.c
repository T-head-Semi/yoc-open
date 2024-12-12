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
#include <string.h>
#include <errno.h>

#include <aos/aos.h>
#include <alsa/snd.h>
#include <alsa/pcm.h>

#define TAG "card"


// int snd_card_new(struct device *parent)
int snd_card_new(int *parent, int idx, const char *xid, struct module *module, int size, snd_card_drv_t **card_ret)
{

    return 0;
}

int snd_card_free(snd_card_drv_t *card)
{

    return 0;
}

int aos_card_attach(const char *name, card_dev_t **card)
{
    *card = (card_dev_t *)rvm_hal_device_open(name);
    return *card == NULL? 0 : -1;
}

int aos_card_lpm(const char *name ,int state)
{
    char *dev_name  = strdup(name);
    int len         = strlen(name);
    int id          = dev_name[len-1] - 0x30;
    dev_name[len-1] = 0;

    card_dev_t *card = (card_dev_t *)rvm_hal_device_find(dev_name, id);

    rvm_hal_device_lpm_enable((rvm_dev_t*)card, state);

    aos_free(dev_name);

    return 0;
}