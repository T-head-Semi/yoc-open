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

#ifndef __SAL2LWIP_H__
#define __SAL2LWIP_H__

#include "lwip/opt.h"

#define sal_mutex_t sys_mutex_t
#define sal_mutex_new sys_mutex_new
#define sal_mutex_lock sys_mutex_lock
#define sal_mutex_unlock sys_mutex_unlock
#define sal_mutex_free sys_mutex_free
#define sal_mutex_valid sys_mutex_valid
#define sal_mutex_set_invalid sys_mutex_set_invalid

#define sal_sem_t sys_sem_t
#define sal_sem_new sys_sem_new
#define sal_sem_signal sys_sem_signal
#define sal_arch_sem_wait sys_arch_sem_wait
#define sal_sem_free sys_sem_free
#define sal_sem_valid sys_sem_valid
#define sal_sem_set_invalid sys_sem_set_invalid

#define sal_mbox_t sys_mbox_t
#define sal_mbox_new sys_mbox_new
#define sal_mbox_post sys_mbox_post
#define sal_mbox_trypost sys_mbox_trypost
#define sal_mbox_tryfetch sys_mbox_tryfetch
#define sal_arch_mbox_fetch sys_arch_mbox_fetch
#define sal_arch_mbox_tryfetch sys_arch_mbox_tryfetch
#define sal_mbox_free sys_mbox_free
#define sal_mbox_valid sys_mbox_valid
#define sal_mbox_set_invalid sys_mbox_set_invalid

#define sal_now sys_now

#define sal_mutex_arch_init sys_init
#define sal_mutex_arch_free() sys_deinit()

#define SAL_ARCH_DECL_PROTECT SYS_ARCH_DECL_PROTECT
#define SAL_ARCH_PROTECT SYS_ARCH_PROTECT
#define SAL_ARCH_UNPROTECT SYS_ARCH_UNPROTECT

#define SAL_ARCH_GET SYS_ARCH_GET
#define SAL_ARCH_SET SYS_ARCH_SET

#define SAL_MBOX_EMPTY SYS_MBOX_EMPTY
#define SAL_ARCH_TIMEOUT SYS_ARCH_TIMEOUT
/*********************************************/

#define sal_netconn_t struct netconn
//#define sal_sock lwip_sock
#define sal_event lwip_event
#define sal_select_cb lwip_select_cb

#define SAL_SOCKET_OFFSET LWIP_SOCKET_OFFSET
#define sal_htons lwip_htons

#define SAL_NETCONN_SEM_PER_THREAD LWIP_NETCONN_SEM_PER_THREAD
/*********************************************/
#define sal_accept       accept
#define sal_bind         bind
#define sal_shutdown     shutdown
#define sal_getpeername  getpeername
#define sal_getsockname  getsockname
#define sal_setsockopt   setsockopt
#define sal_getsockopt   getsockopt
#define sal_close        closesocket
#define sal_connect      connect
#define sal_listen       listen
#define sal_recv         recv
#define sal_recvfrom     recvfrom
#define sal_send         send
#define sal_sendmsg      sendmsg
#define sal_sendto       sendto
#define sal_socket       socket
#define sal_ioctlsocket  ioctl

#if LWIP_POSIX_SOCKETS_IO_NAMES
#define sal_select       select
#define sal_select2      select2
#endif /* LWIP_POSIX_SOCKETS_IO_NAMES */

// #define sal_fcntl        fcntl

#define sal_getaddrinfo       getaddrinfo
#define sal_freeaddrinfo      freeaddrinfo

#define sal_gethostbyname gethostbyname

#endif
