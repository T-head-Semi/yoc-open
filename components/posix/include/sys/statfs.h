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

#ifndef _SYS_STATFS_H
#define _SYS_STATFS_H

#ifdef __cplusplus
extern "C" {
#endif

struct statfs {
    long f_type;    /* fs type */
    long f_bsize;   /* optimized transport block size */
    long f_blocks;  /* total blocks */
    long f_bfree;   /* available blocks */
    long f_bavail;  /* number of blocks that non-super users can acquire */
    long f_files;   /* total number of file nodes */
    long f_ffree;   /* available file nodes */
    long f_fsid;    /* fs id */
    long f_namelen; /* max file name length */
};

int statfs(const char *path, struct statfs *buf);

#ifdef __cplusplus
}
#endif

#endif /*_SYS_STATFS_H*/
