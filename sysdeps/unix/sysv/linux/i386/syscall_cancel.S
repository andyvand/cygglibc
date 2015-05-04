/* Cancellable syscall wrapper - x86_64 version.
   Copyright (C) 2015 Free Software Foundation, Inc.
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

#include <sysdep.h>

ENTRY (__syscall_cancel_arch)
	pushl %ebp
	cfi_def_cfa_offset (8)
	cfi_offset (ebp, -8)
	pushl %edi
	cfi_def_cfa_offset (12)
	cfi_offset (edi, -12)
	pushl %esi
	cfi_def_cfa_offset (16)
	cfi_offset (esi, -16)
	pushl %ebx
	cfi_def_cfa_offset (20)
	cfi_offset (ebx, -20)

	.globl __syscall_cancel_arch_start
	.type  __syscall_cancel_arch_start,@function
__syscall_cancel_arch_start:

	testb	$4, (%eax)
	jne     1f //L(syscall_cancel_arch_do_cancel)

	movl    24(%esp), %eax
	movl    28(%esp), %ebx
	movl    32(%esp), %ecx
	movl    36(%esp), %edx
	movl    40(%esp), %esi
	movl    44(%esp), %edi
	movl    48(%esp), %ebp

        /* It can not use the vDSO __kernel_vsyscall because the cancelable
	   checks in libc-cancelation.c requires to know if the cancellation
	   IP value that was trigger between the two
	   __syscall_cancel_arch_{start,end} marks.  */
	int	$128

	.globl __syscall_cancel_arch_end
	.type  __syscall_cancel_arch_end,@function
__syscall_cancel_arch_end:

	popl %ebx
	cfi_restore (ebx)
	cfi_def_cfa_offset (16)
	popl %esi
	cfi_restore (esi)
	cfi_def_cfa_offset (12)
	popl %edi
	cfi_restore (edi)
	cfi_def_cfa_offset (8)
	popl %ebp
	cfi_restore (ebp)
	cfi_def_cfa_offset (4)
        ret

1:
	/* Although the __syscall_do_cancel do not return, we need to stack
	   being set correctly so exceptions work correctly.  */
	popl %ebx
	cfi_restore (ebx)
	cfi_def_cfa_offset (16)
	popl %esi
	cfi_restore (esi)
	cfi_def_cfa_offset (12)
	popl %edi
	cfi_restore (edi)
	cfi_def_cfa_offset (8)
	popl %ebp
	cfi_restore (ebp)
	cfi_def_cfa_offset (4)
	jmp __syscall_do_cancel

END (__syscall_cancel_arch)
libc_hidden_def (__syscall_cancel_arch)
