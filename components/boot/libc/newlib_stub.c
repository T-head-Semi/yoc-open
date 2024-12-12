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
#if CONFIG_NEWLIB_STUB
#include <reent.h>
#include <sys/errno.h>
#include <sys/unistd.h>
#include <sys/time.h>
#include <stdarg.h>

int _execve_r(struct _reent *ptr, const char *name, char *const *argv,
              char *const *env)
{
    return -1;
}

int _fcntl_r(struct _reent *ptr, int fd, int cmd, int arg)
{
    return -1;
}

int _fork_r(struct _reent *ptr)
{
    return -1;
}

int _getpid_r(struct _reent *ptr)
{
    return 0;
}

int _isatty_r(struct _reent *ptr, int fd)
{
    return -1;
}

int _kill_r(struct _reent *ptr, int pid, int sig)
{
    return -1;
}

int _link_r(struct _reent *ptr, const char *old, const char *new)
{
    return -1;
}

_off_t _lseek_r(struct _reent *ptr, int fd, _off_t pos, int whence)
{
    return -1;
}

int _mkdir_r(struct _reent *ptr, const char *name, int mode)
{
    return -1;
}

int _open_r(struct _reent *ptr, const char *file, int flags, int mode)
{
    return -1;
}

int _close_r(struct _reent *ptr, int fd)
{
    return -1;
}

_ssize_t _read_r(struct _reent *ptr, int fd, void *buf, size_t nbytes)
{
    return -1;
}

_ssize_t _write_r(struct _reent *ptr, int fd, const void *buf, size_t nbytes)
{
    return -1;
}

int _fstat_r(struct _reent *ptr, int fd, struct stat *pstat)
{
    return -1;
}

void *_sbrk_r(struct _reent *ptr, ptrdiff_t incr)
{
    return NULL;
}
#endif