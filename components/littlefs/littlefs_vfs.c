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

#include <vfs.h>
#include <vfs_inode.h>
#include <vfs_file.h>
#include <vfs_register.h>
#include <yoc/partition.h>
#include <aos/list.h>

#include "lfs.h"
#include "littlefs_vfs.h"
#include "lfs_util.h"

/* lookahead size should be 8 bytes aligned */
#define _ALIGN8(n) (((n)+7) & (~7))
#define GET_LOOKAHEAD_SIZE(blks) (_ALIGN8((blks)>>4) > 16 ? _ALIGN8((blks)>>4) : 16)

#define WAIT_FOREVER 0xFFFFFFFF

typedef aos_mutex_t lfs_lock_t;

static lfs_lock_t g_lfs_vfs_lock = NULL;
typedef struct {
    slist_t           node;
    partition_t       lfs_hdl;
    char              *lfs_mount_path;
    struct lfs_config config;
    lfs_t             *lfs;
    lfs_lock_t        *lock;
} lfs_manager_t;

typedef struct _lfsvfs_dir_t
{
    vfs_dir_t    dir;
    lfs_dir_t    lfsdir;
    vfs_dirent_t cur_dirent;
} lfsvfs_dir_t;

static slist_t lfs_node_list = {NULL};

static void lfs_vfs_find_object(vfs_file_t *fp, lfs_manager_t** lfs_manager)
{
    lfs_manager_t* lfs_node = NULL;

    if (fp == NULL || lfs_manager == NULL) {
        return;
    }
    *lfs_manager = NULL;
    slist_for_each_entry(&lfs_node_list, lfs_node, lfs_manager_t, node) {
        if (!strncmp(lfs_node->lfs_mount_path, fp->node->i_name, strlen(lfs_node->lfs_mount_path))) {
            *lfs_manager = lfs_node;
            return;
        }
    }
}

static int32_t littlefs_block_read(const struct lfs_config *cfg, lfs_block_t block,
                             lfs_off_t off, void *dst, lfs_size_t size)
{
    uint32_t off_set = off + cfg->block_size * block;
    return partition_read((partition_t)(uintptr_t)cfg->context, off_set, dst, size);
}

static int32_t littlefs_block_write(const struct lfs_config *cfg, lfs_block_t block,
                              lfs_off_t off, const void *dst, lfs_size_t size)
{
    uint32_t off_set = off + cfg->block_size * block;
    return partition_write((partition_t)(uintptr_t)cfg->context, off_set, (void *)dst, size);
}

static int32_t littlefs_block_erase(const struct lfs_config *cfg, lfs_block_t block)
{
    uint32_t off_set = cfg->block_size * block;
    return partition_erase_size((partition_t)(uintptr_t)cfg->context, off_set, cfg->block_size);
}

static int32_t littlefs_block_sync(const struct lfs_config *cfg)
{
    return 0;
}


/* Global FS lock init */
static void lfs_lock_create(lfs_lock_t *lock)
{
    aos_mutex_new(lock);
}

/* Global FS lock destroy */
static void lfs_lock_destory(lfs_lock_t *lock)
{
    if (lock) {
        aos_mutex_free(lock);
        LFS_TRACE("%s: lock %p destroyed", aos_task_name(), lock);
    }
}

static void lfs_lock(lfs_lock_t *lock)
{
    if (lock) {
        aos_mutex_lock(lock, WAIT_FOREVER);
        LFS_TRACE("%s: lock %p locked", aos_task_name(), lock);
    }
}

static void lfs_unlock(lfs_lock_t *lock)
{
    if (lock) {
        LFS_TRACE("%s: lock %p to be unlocked", aos_task_name(), lock);
        aos_mutex_unlock(lock);
    }
}

static int lfs_lock_is_valid(lfs_lock_t *lock)
{
    return lock && *lock != NULL;
}

/* Relative path convert */
static char *path_convert(lfs_manager_t* lfs_manager, const char *path)
{
    int32_t len, prefix;
    char *target_path, *p;

    if (path == NULL) {
        return NULL;
    }

    len = strlen(path);
    prefix = strlen(lfs_manager->lfs_mount_path);
    if (strncmp(lfs_manager->lfs_mount_path, path, prefix) != 0) {
        return NULL;
    }

    len = len - prefix;
    target_path =(char *)aos_malloc(len + 1);
    if (target_path == NULL) {
        return NULL;
    }

    memset(target_path, 0, len + 1);
    if (len > 0) {
        if (strcmp(lfs_manager->lfs_mount_path, "/") == 0) {
            p = (char *)(path + prefix);
            memcpy(target_path, p, len);
        } else {
            p = (char *)(path + prefix + 1);
            memcpy(target_path, p, len - 1);
        }
    }

    target_path[len] = '\0';
    return target_path;
}

static int32_t mode_convert(int32_t flags)
{
    int32_t mode, res = 0;

    mode = flags & O_ACCMODE;
    if (mode == O_RDONLY) {
        res |= LFS_O_RDONLY;
    } else if (mode == O_WRONLY) {
        res |= LFS_O_WRONLY;
    } else if (mode == O_RDWR) {
        res |= LFS_O_RDWR;
    }

    if (flags & O_CREAT) {
        res |= LFS_O_CREAT;
    }
    if (flags & O_EXCL) {
        res |= LFS_O_EXCL;
    }
    if (flags & O_TRUNC) {
        res |= LFS_O_TRUNC;
    }
    if (flags & O_APPEND) {
        res |= LFS_O_CREAT | LFS_O_APPEND;
    }
    return res;
}

static int lfs_ret_value_convert(int lfs_ret)
{
    int ret;

    if (lfs_ret > 0) {
        return lfs_ret;
    }

    switch(lfs_ret) {
        case LFS_ERR_OK: ret = 0; break;
        case LFS_ERR_IO: ret = -EIO; break;
        case LFS_ERR_CORRUPT: ret = -EIO; break;
        case LFS_ERR_NOENT: ret = -ENOENT; break;
        case LFS_ERR_EXIST: ret = -EEXIST; break;
        case LFS_ERR_NOTDIR: ret = -ENOTDIR; break;
        case LFS_ERR_ISDIR: ret = -EISDIR; break;
        case LFS_ERR_NOTEMPTY: ret = -ENOTEMPTY; break;
        case LFS_ERR_BADF: ret = -EBADF; break;
        case LFS_ERR_FBIG: ret = -EFBIG; break;
        case LFS_ERR_INVAL: ret = -EINVAL; break;
        case LFS_ERR_NOSPC: ret = -ENOSPC; break;
        case LFS_ERR_NOMEM: ret = -ENOMEM; break;
        case LFS_ERR_NOATTR: ret = -ENODATA; break;
        case LFS_ERR_NAMETOOLONG: ret = -ENAMETOOLONG; break;
        default: ret = lfs_ret; break;
    }

    return ret;
}

static int32_t _lfs_deinit(lfs_manager_t* lfs_manager)
{
    if (lfs_manager->lfs != NULL) {
        aos_free(lfs_manager->lfs);
    }

    if (lfs_manager->lock != NULL) {
        lfs_lock_destory(lfs_manager->lock);
        aos_free(lfs_manager->lock);
    }
    return 0;
}

static int32_t _lfs_init(lfs_manager_t* lfs_manager)
{
    /* Create LFS Global Lock */
    lfs_manager->lock = (lfs_lock_t *)aos_malloc(sizeof(lfs_lock_t));
    if (lfs_manager->lock == NULL) {
        goto ERROR;
    }
    lfs_lock_create(lfs_manager->lock);

    /* Create LFS struct */
    lfs_manager->lfs = (lfs_t *)aos_malloc(sizeof(lfs_t));
    if (lfs_manager->lfs == NULL) {
        goto ERROR;
    }

    return 0;

ERROR:
    _lfs_deinit(lfs_manager);
    return -1;
}

static int lfs_vfs_open(vfs_file_t *fp, const char *path, int flags)
{
    int res;
    char *target_path = NULL;
    lfs_file_t *file = NULL;

    lfs_manager_t *lfs_manager = NULL;
    lfs_vfs_find_object(fp, &lfs_manager);
    if (!lfs_manager) {
        return -EINVAL;
    }
    target_path = path_convert(lfs_manager, path);
    if (target_path == NULL) {
        return -EINVAL;
    }

    if (!strlen(target_path)) {
        return -EINVAL;
    }

    file = (lfs_file_t *)aos_malloc(sizeof(lfs_file_t));
    if (file == NULL) {
        aos_free(target_path);
        return -EINVAL;
    }

    lfs_lock(lfs_manager->lock);
    res = lfs_file_open(lfs_manager->lfs, file,  target_path, mode_convert(flags));
    lfs_unlock(lfs_manager->lock);

    if (res != LFS_ERR_OK) {
        aos_free(target_path);
        aos_free(file);
        return res;
    } else {
        fp->f_arg = (void *)file;
    }


    aos_free(target_path);
    return res;
}

static int lfs_vfs_close(vfs_file_t *fp)
{
    int res = LFS_ERR_INVAL;
    lfs_file_t *file = (lfs_file_t *)(fp->f_arg);

    lfs_manager_t *lfs_manager = NULL;

    lfs_vfs_find_object(fp, &lfs_manager);
    if (!lfs_manager) {
        return -EINVAL;
    }

    lfs_lock(lfs_manager->lock);
    res = lfs_file_close(lfs_manager->lfs, file);
    lfs_unlock(lfs_manager->lock);

    if (res == LFS_ERR_OK) {
        aos_free(file);
    }

    return res;
}

static ssize_t lfs_vfs_read(vfs_file_t *fp, char *buf, size_t len)
{
    int nbytes;
    lfs_file_t *file = (lfs_file_t *)(fp->f_arg);
    lfs_manager_t *lfs_manager = NULL;

    lfs_vfs_find_object(fp, &lfs_manager);
    if (!lfs_manager) {
        return -EINVAL;
    }

    lfs_lock(lfs_manager->lock);
    nbytes = lfs_file_read(lfs_manager->lfs, file, buf, len);
    lfs_unlock(lfs_manager->lock);

    return nbytes;
}

static ssize_t lfs_vfs_write(vfs_file_t *fp, const char *buf, size_t len)
{
    int nbytes;
    lfs_file_t *file = (lfs_file_t *)(fp->f_arg);
    lfs_manager_t *lfs_manager = NULL;

    lfs_vfs_find_object(fp, &lfs_manager);
    if (!lfs_manager) {
        return -EINVAL;
    }
    lfs_lock(lfs_manager->lock);
    nbytes = lfs_file_write(lfs_manager->lfs, file, buf, len);
    lfs_unlock(lfs_manager->lock);

    return nbytes;
}

static off_t lfs_vfs_lseek(vfs_file_t *fp, off_t off, int whence)
{
    off_t res;
    lfs_file_t *file = (lfs_file_t *)(fp->f_arg);
    lfs_manager_t *lfs_manager = NULL;

    lfs_vfs_find_object(fp, &lfs_manager);
    if (!lfs_manager) {
        return -EINVAL;
    }

    lfs_lock(lfs_manager->lock);
    res = lfs_file_seek(lfs_manager->lfs, file, off, whence);
    lfs_unlock(lfs_manager->lock);

    return res;
}

static int lfs_vfs_sync(vfs_file_t *fp)
{
    int res;
    lfs_file_t *file = (lfs_file_t *)(fp->f_arg);
    lfs_manager_t *lfs_manager = NULL;

    lfs_vfs_find_object(fp, &lfs_manager);
    if (!lfs_manager) {
        return -EINVAL;
    }

    lfs_lock(lfs_manager->lock);
    res = lfs_file_sync(lfs_manager->lfs, file);
    lfs_unlock(lfs_manager->lock);

    return res;
}

static int lfs_vfs_fstat(vfs_file_t *fp, vfs_stat_t *st)
{
    int32_t ret;
    struct lfs_info s;
    lfs_file_t *file = (lfs_file_t*)(fp->f_arg);
    lfs_manager_t *lfs_manager = NULL;

    memset(&s, 0, sizeof(struct lfs_info));
    lfs_vfs_find_object(fp, &lfs_manager);
    if (!lfs_manager) {
        return -EINVAL;
    }

    lfs_lock(lfs_manager->lock);
    ret = lfs_fstat(lfs_manager->lfs, file, &s);
    lfs_unlock(lfs_manager->lock);

    ret = lfs_ret_value_convert(ret);
    if (ret == 0){
        st->st_size = s.size;
        st->st_mode = S_IRWXU | S_IRWXG | S_IRWXO |
                      ((s.type == LFS_TYPE_DIR) ? S_IFDIR : S_IFREG);
#ifdef FS_TIMESTAMP_WORKAROUND
        st->st_actime = time(NULL);
        st->st_modtime = time(NULL);
#endif
    }

    return ret;
}

static int lfs_vfs_stat(vfs_file_t *fp, const char *path, vfs_stat_t *st)
{
    int res;
    struct lfs_info s;
    char *target_path = NULL;

    lfs_manager_t *lfs_manager = NULL;

    memset(&s, 0, sizeof(struct lfs_info));
    lfs_vfs_find_object(fp, &lfs_manager);
    if (!lfs_manager) {
        return -EINVAL;
    }

    target_path = path_convert(lfs_manager, path);
    if (target_path == NULL) {
        return -EINVAL;
    }

    lfs_lock(lfs_manager->lock);
    res = lfs_stat(lfs_manager->lfs, target_path, &s);
    lfs_unlock(lfs_manager->lock);

    if (res == LFS_ERR_OK) {
        st->st_size = s.size;
        st->st_mode = S_IRWXU | S_IRWXG | S_IRWXO |
                      ((s.type == LFS_TYPE_DIR ? S_IFDIR : S_IFREG));
    }

    aos_free(target_path);
    return res;
}

static int lfs_vfs_access(vfs_file_t *fp, const char *path, int mode)
{
    vfs_stat_t s;
    int ret;

    ret = lfs_vfs_stat(fp, path, &s);
    ret = lfs_ret_value_convert(ret);
    if (ret == 0) {
        switch(mode) {
            case F_OK: return 0;
            case R_OK: return s.st_mode & S_IRUSR ? 0 : 1;
            case W_OK: return s.st_mode & S_IWUSR ? 0 : 1;
            case X_OK: return s.st_mode & S_IXUSR ? 0 : 1;
        }
    }

    return ret;
}

static int lfs_vfs_statfs(vfs_file_t *fp, const char *path, vfs_statfs_t *sfs)
{
    int ret;
    int32_t block_used;
    lfs_manager_t *lfs_manager = NULL;

    lfs_vfs_find_object(fp, &lfs_manager);
    if (!lfs_manager) {
        return -EINVAL;
    }

    lfs_lock(lfs_manager->lock);
    ret = lfs_fs_size(lfs_manager->lfs);
    lfs_unlock(lfs_manager->lock);
    ret = lfs_ret_value_convert(ret);
    if (ret >= 0) {
        block_used = ret;
        memset(sfs, 0, sizeof(vfs_statfs_t));
        sfs->f_type = 0xd3fc;
        sfs->f_bsize = lfs_manager->config.block_size;
        sfs->f_blocks = lfs_manager->config.block_count;
        sfs->f_bfree = lfs_manager->config.block_count - block_used;
        sfs->f_bavail = sfs->f_bfree;
        sfs->f_files = 1024;
        ret = 0;
    }

    return ret;
}

static int lfs_vfs_remove(vfs_file_t *fp, const char *path)
{
    int res;
    char *target_path = NULL;
    lfs_manager_t *lfs_manager = NULL;

    lfs_vfs_find_object(fp, &lfs_manager);
    if (!lfs_manager) {
        return -EINVAL;
    }

    target_path = path_convert(lfs_manager, path);
    if (target_path == NULL) {
        return -EINVAL;
    }

    lfs_lock(lfs_manager->lock);
    res = lfs_remove(lfs_manager->lfs, target_path);
    lfs_unlock(lfs_manager->lock);

    aos_free(target_path);
    return res;
}

static int lfs_vfs_rename(vfs_file_t *fp, const char *oldpath, const char *newpath)
{
    int32_t ret;
    char *oldname = NULL;
    char *newname = NULL;
    lfs_manager_t *lfs_manager = NULL;

    lfs_vfs_find_object(fp, &lfs_manager);
    if (!lfs_manager) {
        return -EINVAL;
    }

    oldname = path_convert(lfs_manager, oldpath);
    if (!oldname) {
        return -EINVAL;
    }

    newname = path_convert(lfs_manager, newpath);
    if (!newname) {
        aos_free(oldname);
        return -EINVAL;
    }

    lfs_lock(lfs_manager->lock);
    ret = lfs_rename(lfs_manager->lfs, oldname, newname);
    lfs_unlock(lfs_manager->lock);

    aos_free(oldname);
    aos_free(newname);

    return ret;
}

static vfs_dir_t *lfs_vfs_opendir(vfs_file_t *fp, const char *path)
{
    int32_t ret;
    char *relpath = NULL;
    lfsvfs_dir_t *lfsvfs_dir = NULL;
    lfs_manager_t *lfs_manager = NULL;

    lfs_vfs_find_object(fp, &lfs_manager);
    if (!lfs_manager) {
        return NULL;
    }

    relpath = path_convert(lfs_manager, path);
    if (!relpath) {
        return NULL;
    }

    lfsvfs_dir = (lfsvfs_dir_t *)aos_malloc(sizeof(lfsvfs_dir_t) + LFS_NAME_MAX + 1);
    if (!lfsvfs_dir) {
        aos_free(relpath);
        return NULL;
    }

    memset(lfsvfs_dir, 0, sizeof(lfsvfs_dir_t) + LFS_NAME_MAX + 1);

    lfs_lock(lfs_manager->lock);
    ret = lfs_dir_open(lfs_manager->lfs, &lfsvfs_dir->lfsdir, relpath);
    lfs_unlock(lfs_manager->lock);

    if (ret != LFS_ERR_OK) {
        aos_free(relpath);
        aos_free(lfsvfs_dir);
        return NULL;
    }

    aos_free(relpath);
    return (vfs_dir_t *)lfsvfs_dir;
}

static vfs_dirent_t *lfs_vfs_readdir(vfs_file_t *fp, vfs_dir_t *dir)
{
    lfsvfs_dir_t *lfsvfs_dir = (lfsvfs_dir_t*)dir;
    struct lfs_info info;
    int32_t ret;

    if (!lfsvfs_dir) {
        return NULL;
    }

    lfs_manager_t *lfs_manager = NULL;
    memset(&info, 0, sizeof(struct lfs_info));
    lfs_vfs_find_object(fp, &lfs_manager);
    if (!lfs_manager) {
        return NULL;
    }

    lfs_lock(lfs_manager->lock);
    ret = lfs_dir_read(lfs_manager->lfs, &lfsvfs_dir->lfsdir, &info);
    lfs_unlock(lfs_manager->lock);

    if (ret != true) {
        return NULL;
    }

    if (info.name[0] == 0) {
        return NULL;
    }

    lfsvfs_dir->cur_dirent.d_ino = 0;
    lfsvfs_dir->cur_dirent.d_type = info.type;
    strncpy(lfsvfs_dir->cur_dirent.d_name, info.name, LFS_NAME_MAX);
    lfsvfs_dir->cur_dirent.d_name[LFS_NAME_MAX] = '\0';

    return &lfsvfs_dir->cur_dirent;
}

static int lfs_vfs_closedir(vfs_file_t *fp, vfs_dir_t *dir)
{
    lfsvfs_dir_t *lfsvfs_dir = (lfsvfs_dir_t *)dir;
    int32_t ret;

    if (!lfsvfs_dir) {
        return -EINVAL;
    }

    lfs_manager_t *lfs_manager = NULL;
    lfs_vfs_find_object(fp, &lfs_manager);
    if (!lfs_manager) {
        return -EINVAL;
    }

    lfs_lock(lfs_manager->lock);
    ret = lfs_dir_close(lfs_manager->lfs, &lfsvfs_dir->lfsdir);
    lfs_unlock(lfs_manager->lock);
    if (ret != 0) {
        return ret;
    }

    aos_free(lfsvfs_dir);

    return ret;
}

static int lfs_vfs_mkdir(vfs_file_t *fp, const char *path)
{
    int32_t ret;
    char *pathname = NULL;

    lfs_manager_t *lfs_manager = NULL;
    lfs_vfs_find_object(fp, &lfs_manager);
    if (!lfs_manager) {
        return -EINVAL;
    }

    pathname = path_convert(lfs_manager, path);
    if (!pathname) {
        return -EINVAL;
    }

    lfs_lock(lfs_manager->lock);
    ret = lfs_mkdir(lfs_manager->lfs, pathname);
    lfs_unlock(lfs_manager->lock);

    aos_free(pathname);

    return ret;
}

static int lfs_vfs_rmdir (vfs_file_t *fp, const char *path)
{
    int32_t ret;
    char *pathname = NULL;

    lfs_manager_t *lfs_manager = NULL;
    lfs_vfs_find_object(fp, &lfs_manager);
    if (!lfs_manager) {
        return -EINVAL;
    }

    pathname = path_convert(lfs_manager, path);
    if (!pathname) {
        return -EINVAL;
    }

    lfs_lock(lfs_manager->lock);
    ret = lfs_remove(lfs_manager->lfs, pathname);
    lfs_unlock(lfs_manager->lock);

    aos_free(pathname);

    return ret;
}

static void lfs_vfs_rewinddir(vfs_file_t *fp, vfs_dir_t *dir)
{
    lfs_manager_t *lfs_manager = NULL;
    lfsvfs_dir_t *lfsvfs_dir = (lfsvfs_dir_t *)dir;

    if (!lfsvfs_dir) {
        return;
    }

    lfs_vfs_find_object(fp, &lfs_manager);
    if (!lfs_manager) {
        return;
    }

    lfs_lock(lfs_manager->lock);
    lfs_dir_rewind(lfs_manager->lfs, &lfsvfs_dir->lfsdir);
    lfs_unlock(lfs_manager->lock);
}

static long lfs_vfs_telldir(vfs_file_t *fp, vfs_dir_t *dir)
{
    lfsvfs_dir_t *lfsvfs_dir = (lfsvfs_dir_t *)dir;
    int32_t ret;

    if (!lfsvfs_dir) {
        return -EINVAL;
    }

    lfs_manager_t *lfs_manager = NULL;
    lfs_vfs_find_object(fp, &lfs_manager);
    if (!lfs_manager) {
        return -EINVAL;
    }

    lfs_lock(lfs_manager->lock);
    ret = lfs_dir_tell(lfs_manager->lfs, &lfsvfs_dir->lfsdir);
    lfs_unlock(lfs_manager->lock);

    return lfs_ret_value_convert(ret);
}

static void lfs_vfs_seekdir(vfs_file_t *fp, vfs_dir_t *dir, long loc)
{
    lfs_manager_t *lfs_manager = NULL;
    lfsvfs_dir_t *lfsvfs_dir = (lfsvfs_dir_t*)dir;

    if (!lfsvfs_dir) {
        return;
    }

    lfs_vfs_find_object(fp, &lfs_manager);
    if (!lfs_manager) {
        return;
    }

    lfs_lock(lfs_manager->lock);
    lfs_dir_seek(lfs_manager->lfs, &lfsvfs_dir->lfsdir, (lfs_off_t)loc);
    lfs_unlock(lfs_manager->lock);
}

static int lfs_vfs_utime(vfs_file_t *fp, const char *path, const vfs_utimbuf_t *times)
{
    return lfs_ret_value_convert(LFS_ERR_OK);
}

static int lfs_vfs_truncate(vfs_file_t *fp, off_t size)
{
    int32_t ret;

    lfs_file_t *file = (lfs_file_t *)(fp->f_arg);

    lfs_manager_t *lfs_manager = NULL;
    lfs_vfs_find_object(fp, &lfs_manager);
    if (!lfs_manager) {
        return -EINVAL;
    }

    lfs_lock(lfs_manager->lock);
    ret = lfs_file_truncate(lfs_manager->lfs, file, size);
    lfs_unlock(lfs_manager->lock);

    return lfs_ret_value_convert(ret);
}

static const vfs_fs_ops_t littlefs_ops = {
    .open       = &lfs_vfs_open,
    .close      = &lfs_vfs_close,
    .read       = &lfs_vfs_read,
    .write      = &lfs_vfs_write,
    .lseek      = &lfs_vfs_lseek,
    .sync       = &lfs_vfs_sync,
    .stat       = &lfs_vfs_stat,
    .unlink     = &lfs_vfs_remove,
    .remove     = &lfs_vfs_remove,
    .rename     = &lfs_vfs_rename,
    .access     = &lfs_vfs_access,
    .fstat      = &lfs_vfs_fstat,
    .statfs     = &lfs_vfs_statfs,
    .opendir    = &lfs_vfs_opendir,
    .readdir    = &lfs_vfs_readdir,
    .closedir   = &lfs_vfs_closedir,
    .mkdir      = &lfs_vfs_mkdir,
    .rmdir      = &lfs_vfs_rmdir,
    .rewinddir  = &lfs_vfs_rewinddir,
    .telldir    = &lfs_vfs_telldir,
    .seekdir    = &lfs_vfs_seekdir,
    .ioctl      = NULL,
    .utime      = &lfs_vfs_utime,
    .truncate   = &lfs_vfs_truncate,
};

int lfs_vfs_mount(lfs_manager_t* lfs_manager)
{
    int res;

    res = _lfs_init(lfs_manager);
    if (res != LFS_ERR_OK) {
        return res;
    }

    lfs_lock(lfs_manager->lock);

    res = lfs_mount(lfs_manager->lfs, &lfs_manager->config);
#ifdef LITTLEFS_FORMAT
    if (res != LFS_ERR_OK) {
        res = lfs_format(lfs_manager->lfs, &lfs_manager->config);
        if (res != LFS_ERR_OK) {
            goto ERROR;
        }

        res = lfs_mount(lfs_manager->lfs, &lfs_manager->config);
        if (res != LFS_ERR_OK) {
            goto ERROR;
        }
    }
#endif

    lfs_unlock(lfs_manager->lock);
    return res;

#ifdef LITTLEFS_FORMAT
ERROR:
    lfs_unlock(lfs_manager->lock);
    _lfs_deinit(lfs_manager);
    return res;
#endif
}

static int lfs_vfs_unmount(lfs_manager_t* lfs_manager)
{
    lfs_unmount(lfs_manager->lfs);
    _lfs_deinit(lfs_manager);
    return LFS_ERR_OK;
}

int32_t vfs_lfs_register(char *partition_desc)
{
    return vfs_lfs_register_with_path(partition_desc, (const char *)LFS_MOUNTPOINT);
}

static void lfs_set_config(lfs_manager_t *lfs_manager, char *partition_desc)
{
    if (lfs_manager == NULL || partition_desc == NULL) {
        return;
    }

    partition_t lfs_hdl = partition_open(partition_desc);
    aos_check(lfs_hdl > 0, EIO);

    lfs_manager->lfs_hdl = lfs_hdl;
    // block device configuration
    partition_info_t *part_info = partition_info_get(lfs_hdl);

    lfs_manager->config.context  = (void*)(uintptr_t)lfs_manager->lfs_hdl;
    lfs_manager->config.read     = littlefs_block_read;
    lfs_manager->config.prog     = littlefs_block_write;
    lfs_manager->config.erase    = littlefs_block_erase;
    lfs_manager->config.sync     = littlefs_block_sync;

#ifdef CONFIG_LFS_BLOCK_SIZE
    lfs_manager->config.block_size     = LFS_BLOCK_SIZE;
#else
    lfs_manager->config.block_size     = part_info->sector_size;
#endif
#ifdef CONFIG_LFS_BLOCK_COUNT
    lfs_manager->config.block_count    = LFS_BLOCK_COUNT;
#else
    lfs_manager->config.block_count    = part_info->length / part_info->sector_size;
#endif
#ifdef CONFIG_LFS_READ_SIZE
    lfs_manager->config.read_size      = LFS_READ_SIZE;
#else
    lfs_manager->config.read_size      = 256;
#endif
#ifdef CONFIG_LFS_PROG_SIZE
    lfs_manager->config.prog_size      = LFS_PROG_SIZE;
#else
    lfs_manager->config.prog_size      = 256;
#endif
#ifdef CONFIG_LFS_CACHE_SIZE
    lfs_manager->config.cache_size     = LFS_CACHE_SIZE;
#else
    lfs_manager->config.cache_size     = lfs_manager->config.prog_size;
#endif
#ifdef CONFIG_LFS_LOOKAHEAD_SIZE
    lfs_manager->config.lookahead_size = LFS_LOOKAHEAD_SIZE;
#else
    lfs_manager->config.lookahead_size = GET_LOOKAHEAD_SIZE(lfs_manager->config.block_count);
#endif
#ifdef CONFIG_LFS_BLOCK_CYCLES
    lfs_manager->config.block_cycles   = LFS_BLOCK_CYCLES;
#else
    lfs_manager->config.block_cycles   = 1000;
#endif

    // printf("lfs_manager->config.block_size: %d\n", lfs_manager->config.block_size);
    // printf("lfs_manager->config.block_count: %d\n", lfs_manager->config.block_count);
    // printf("lfs_manager->config.read_size: %d\n", lfs_manager->config.read_size);
    // printf("lfs_manager->config.prog_size: %d\n", lfs_manager->config.prog_size);
    // printf("lfs_manager->config.cache_size: %d\n", lfs_manager->config.cache_size);
    // printf("lfs_manager->config.lookahead_size: %d\n", lfs_manager->config.lookahead_size);
    // printf("lfs_manager->config.block_cycles: %d\n", lfs_manager->config.block_cycles);
}

int32_t vfs_lfs_register_with_path(char *partition_desc, const char *path)
{
    int res;

    if (partition_desc == NULL || path == NULL) {
        return -EINVAL;
    }
    char* lfs_mount_path = strdup(path);
    if (lfs_mount_path == NULL) {
        return -ENOMEM;
    }

    lfs_manager_t *lfs_manager= aos_zalloc(sizeof(lfs_manager_t));
    if (!lfs_manager) {
        free(lfs_mount_path);
        return -ENOMEM;
    }

    lfs_manager->lfs_mount_path = lfs_mount_path;
    lfs_set_config(lfs_manager, partition_desc);

    res = lfs_vfs_mount(lfs_manager);
    if (res) {
        goto failure;
    }
    res = vfs_register_fs(lfs_mount_path, &littlefs_ops, NULL);
    if (res) {
        goto failure;
    }

    if (!lfs_lock_is_valid(&g_lfs_vfs_lock)) {
        lfs_lock_create(&g_lfs_vfs_lock);
    }

    lfs_lock(&g_lfs_vfs_lock);
    slist_add(&lfs_manager->node, &lfs_node_list);
    lfs_unlock(&g_lfs_vfs_lock);
    return res;
failure:
    free(lfs_mount_path);
    free(lfs_manager);
    return res;
}

int32_t vfs_lfs_unregister(void)
{
    int ret = -1;
    lfs_manager_t* lfs_node = NULL;
    slist_for_each_entry(&lfs_node_list, lfs_node, lfs_manager_t, node) {
        if (!strcmp(lfs_node->lfs_mount_path, LFS_MOUNTPOINT)) {
                lfs_vfs_unmount(lfs_node);
                partition_close(lfs_node->lfs_hdl);
                ret = vfs_unregister_fs(lfs_node->lfs_mount_path);
            if (lfs_node->lfs_mount_path)
                free(lfs_node->lfs_mount_path);

            if (lfs_lock_is_valid(&g_lfs_vfs_lock)) {
                lfs_lock(&g_lfs_vfs_lock);
                slist_remove(&lfs_node_list, &lfs_node->node);
                lfs_unlock(&g_lfs_vfs_lock);
            }
            free(lfs_node);
            break;
        }
    }
    return ret;
}

int32_t vfs_lfs_unregister_with_path(const char *path)
{
    int ret = -1;
    lfs_manager_t* lfs_node = NULL;
    slist_for_each_entry(&lfs_node_list, lfs_node, lfs_manager_t, node) {
        if (!strcmp(lfs_node->lfs_mount_path, path)) {
            lfs_vfs_unmount(lfs_node);
            partition_close(lfs_node->lfs_hdl);
            ret = vfs_unregister_fs(lfs_node->lfs_mount_path);
            if (lfs_node->lfs_mount_path)
                free(lfs_node->lfs_mount_path);
            if (lfs_lock_is_valid(&g_lfs_vfs_lock)) {
                lfs_lock(&g_lfs_vfs_lock);
                slist_remove(&lfs_node_list, &lfs_node->node);
                lfs_unlock(&g_lfs_vfs_lock);
            }
            free(lfs_node);
            break;
        }
    }
    return ret;
}