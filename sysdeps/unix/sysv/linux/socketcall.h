/* ID for functions called via socketcall system call.
   Copyright (C) 1995-2015 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#ifndef _SYS_SOCKETCALL_H
#define _SYS_SOCKETCALL_H	1

/* Define unique numbers for the operations permitted on socket.  Linux
   uses a single system call for all these functions.  The relevant code
   file is /usr/include/linux/net.h.
   We cannot use an enum here because the values are used in assembler
   code.  */

#define SOCKOP_invalid		-1
#define SOCKOP_socket		1
#define SOCKOP_bind		2
#define SOCKOP_connect		3
#define SOCKOP_listen		4
#define SOCKOP_accept		5
#define SOCKOP_getsockname	6
#define SOCKOP_getpeername	7
#define SOCKOP_socketpair	8
#define SOCKOP_send		9
#define SOCKOP_recv		10
#define SOCKOP_sendto		11
#define SOCKOP_recvfrom		12
#define SOCKOP_shutdown		13
#define SOCKOP_setsockopt	14
#define SOCKOP_getsockopt	15
#define SOCKOP_sendmsg		16
#define SOCKOP_recvmsg		17
#define SOCKOP_accept4		18
#define SOCKOP_recvmmsg		19
#define SOCKOP_sendmmsg		20

#define SOCKETCALL(name, __a1, __a2, __a3, __a4, __a5, __a6)		\
  ({									\
    long int __args[6] = { (long int) __a1,				\
                           (long int) __a2,				\
                           (long int) __a3,				\
                           (long int) __a4,				\
                           (long int) __a5,				\
                           (long int) __a6 };				\
    long int sc_ret = INLINE_SYSCALL (socketcall, 2, SOCKOP_##name,	\
                                     __args);				\
    sc_ret;								\
  })

#if IS_IN (libc)
# define __pthread_enable_asynccancel  __libc_enable_asynccancel
# define __pthread_disable_asynccancel __libc_disable_asynccancel
#endif

#define SOCKETCALL_CANCEL(name, __a1, __a2, __a3, __a4, __a5, __a6)	\
  ({									\
    long int __args[6] = { (long int) __a1,				\
                           (long int) __a2,				\
                           (long int) __a3,				\
                           (long int) __a4,				\
                           (long int) __a5,				\
                           (long int) __a6 };				\
    int oldtype = LIBC_CANCEL_ASYNC ();					\
    long int sc_ret = INLINE_SYSCALL (socketcall, 2, SOCKOP_##name,	\
                                     __args);				\
    LIBC_CANCEL_RESET (oldtype);					\
    sc_ret;								\
  })


#endif /* sys/socketcall.h */
