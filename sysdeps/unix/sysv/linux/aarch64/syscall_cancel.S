/* Cancellable syscall wrapper - aarch64 version.
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

/* __syscall_cancel_arch(&self->cancelhandling, nr, a1, a2, a3, a4, a5, a6)
                                 x0             x1  x2  x3  x4  x5  x6  x7 */

ENTRY (__syscall_cancel_arch)

        stp     x29, x30, [sp, -16]!
        cfi_def_cfa_offset (16)
        cfi_offset (29, -16)
        cfi_offset (30, -8)
        add     x29, sp, 0
        cfi_def_cfa_register (29)

	.globl __syscall_cancel_arch_start
	.type  __syscall_cancel_arch_start,@function
__syscall_cancel_arch_start:

	ldr	w0, [x0]
	tbnz    w0, 2, 1f

	mov	x8, x1
	mov	x0, x2
	mov	x1, x3
	mov	x2, x4
	mov	x3, x5
	mov	x4, x6
	mov	x5, x7
	svc	0x0

	.globl __syscall_cancel_arch_end
	.type  __syscall_cancel_arch_end,@function
__syscall_cancel_arch_end:

        ldp     x29, x30, [sp], 16
        cfi_remember_state
        cfi_restore (30)
        cfi_restore (29)
        cfi_def_cfa (31, 0)
	ret

1:
	cfi_restore_state
	b	__syscall_do_cancel

END (__syscall_cancel_arch)
libc_hidden_def (__syscall_cancel_arch)
