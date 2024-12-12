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

#include <reent.h>
#include <errno.h>
#include <stdio.h>
#include <sys/unistd.h>
#include <stdlib.h>
#include <drv/uart.h>

extern csi_uart_t g_console_handle;
int _isatty_r(struct _reent *ptr, int fd)
{
    if (fd >= 0 && fd < 3) {
        return 1;
    }

    ptr->_errno = ENOTSUP;
    return -1;
}

_ssize_t _write_r(struct _reent *ptr, int fd, const void *buf, size_t nbytes)
{
    if (buf == NULL) {
        return 0;
    }
    if ((fd == STDOUT_FILENO) || (fd == STDERR_FILENO)) {
        char *ch = (char *)buf;
        for (int i = 0; i < nbytes; i ++) {

            if (ch[i] == '\n') {
                csi_uart_putc(&g_console_handle, '\r');
            }
        
            csi_uart_putc(&g_console_handle, ch[i]);
        }
        return nbytes;
    }
    return -1;
}

int _fstat_r(struct _reent *ptr, int fd, struct stat *pstat)
{
    ptr->_errno = ENOTSUP;
    return -1;
}

void *_sbrk_r(struct _reent *ptr, ptrdiff_t incr)
{
    ptr->_errno = ENOTSUP;
    return NULL;
}
