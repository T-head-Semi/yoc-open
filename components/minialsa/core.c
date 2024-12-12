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
#include <alsa/pcm.h>
#include <alsa/snd.h>

// static aos_task_t alsa_task_hdl;

enum {
    _PCM_WRITE_CMD,
    _PCM_READ_CMD,
};

typedef struct {
    int cmd;
    void (*cb)(void *param, int len);
} alsa_cmd_t;

void pcm_write(void *param, int len);
void pcm_read(void *param, int len);

const alsa_cmd_t alsa_cmt_table[] = {
    {_PCM_WRITE_CMD, pcm_write},
    {_PCM_READ_CMD, pcm_read},
};

void pcm_write(void *param, int len)
{

}

void pcm_read(void *param, int len)
{

}
void alsa_task(void *param)
{

}

int alsa_init(void)
{
    // aos_task_new_ext(&alsa_task_hdl, "alsa", alsa_task, NULL, 2048, AOS_DEFAULT_APP_PRI);

    return 0;
}