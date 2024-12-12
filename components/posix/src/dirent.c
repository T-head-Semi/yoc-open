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

#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <aos/kernel.h>

#include "internal/common.h"

DIR *opendir(const char *dirname)
{
    if (dirname == NULL) {
        errno = EINVAL;
        return NULL;
    }

    return (DIR *)aos_opendir(dirname);
}

int closedir(DIR *dirp)
{
    int ret;

    CHECK_POSIX_PARAM(dirp);

    ret = aos_closedir((aos_dir_t *)dirp);
    CHECK_AOS_RET(ret);

    return ret;
}

struct dirent *readdir(DIR *dirp)
{
    if (dirp == NULL) {
        errno = EINVAL;
        return NULL;
    }

    return (struct dirent *)aos_readdir(dirp);
}

long telldir(DIR *dirp)
{
    long ret;

    CHECK_POSIX_PARAM(dirp);

    ret = aos_telldir((aos_dir_t *)dirp);
    CHECK_AOS_RET(ret);

    return ret;
}

void seekdir(DIR *dirp, long loc)
{
    if (dirp == NULL) {
        return;
    }

    return aos_seekdir((aos_dir_t *)dirp, loc);
}

int scandir(const char *dirname, struct dirent ***namelist,
            int (*filter)(const struct dirent *),
            int (*compar)(const struct dirent **, const struct dirent **))
{

    size_t name_len;
    int num_entry = 0;
    int array_size = 16;
    DIR *dirp;
    struct dirent *d, *p;
    struct dirent **names, **names_new;

    if ((dirname == NULL) || (namelist == NULL)) {
        errno = EINVAL;
        return -1;
    }

    dirp = opendir(dirname);
    if (dirp == NULL)
        return -1;

    names = (struct dirent **)malloc(sizeof(struct dirent *) * array_size);
    if (names == NULL) {
        errno = ENOMEM;
        goto error;
    }

    while ((d = readdir(dirp)) != NULL) {
        if ((filter != NULL) && ((*filter)(d) == 0))
            continue;

        name_len = strlen(d->d_name);
        p = (struct dirent*) malloc(DIRSIZ(d));
        if (p == NULL) {
            errno = ENOMEM;
            goto error;
        }
        p->d_ino  = d->d_ino;
        p->d_type = d->d_type;
        strncpy(p->d_name, d->d_name, name_len);
        p->d_name[name_len] = '\0';

        if (num_entry >= array_size) {
            names_new = realloc(names, sizeof(struct dirent *) * array_size * 2);
            if (names_new == NULL) {
                free(p);
                errno = ENOMEM;
                goto error;
            }

            names = names_new;
            array_size *= 2;
        }

        names[num_entry++] = p;
    }
    closedir(dirp);
    if ((num_entry > 0) && (compar != NULL))
        qsort(names, num_entry, sizeof(struct dirent *), (void *)compar);
    *namelist = names;
    return num_entry;

error:
    while (num_entry > 0)
        free(names[num_entry--]);
    free(names);
    closedir(dirp);
    return -1;
}

int mkdir(const char *path, mode_t mode)
{
    int ret;

    CHECK_POSIX_PARAM(path);

    ret = aos_mkdir(path);
    CHECK_AOS_RET(ret);

    return ret;
}

int rmdir(const char *path)
{
    int ret;

    CHECK_POSIX_PARAM(path);

    ret = aos_rmdir(path);
    CHECK_AOS_RET(ret);

    return ret;
}

void rewinddir(DIR *dirp)
{
    if (dirp == NULL) {
        return;
    }

    aos_rewinddir((aos_dir_t *)dirp);
}

int chdir(const char *path)
{
    int ret;

    CHECK_POSIX_PARAM(path);

    ret = aos_chdir(path);
    CHECK_AOS_RET(ret);

    return ret;
}
