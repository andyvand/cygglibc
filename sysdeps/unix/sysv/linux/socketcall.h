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
    __syscall_arg_t __args[6] = { __SSC (__a1), __SSC (__a2),		\
				  __SSC (__a3), __SSC (__a4), 		\
				  __SSC (__a5), __SSC (__a6) };		\
    long int sc_ret = INLINE_SYSCALL (socketcall, 2, SOCKOP_##name,	\
				      __args);				\
    sc_ret;								\
  })

#define SOCKETCALL_CANCEL(name, __a1, __a2, __a3, __a4, __a5, __a6)	\
  ({									\
    __syscall_arg_t __args[6] = { __SSC (__a1), __SSC (__a2),		\
				  __SSC (__a3), __SSC (__a4), 		\
				  __SSC (__a5), __SSC (__a6) };		\
    long int sc_ret = SYSCALL_CANCEL_NCS (socketcall, SOCKOP_##name,	\
					  __args);			\
    if (SYSCALL_CANCEL_ERROR (sc_ret))					\
      {									\
        __set_errno (SYSCALL_CANCEL_ERRNO (sc_ret));			\
        sc_ret = -1L;							\
      }									\
    sc_ret;								\
  })


#endif /* sys/socketcall.h */
