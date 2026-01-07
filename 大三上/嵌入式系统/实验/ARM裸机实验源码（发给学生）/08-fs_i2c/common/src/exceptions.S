#include "macro.h"

.macro  disable_dbg
msr daifset, #8
.endm

.macro  enable_dbg
msr daifclr, #8
.endm

#if 0
.macro	exception_entry
	stp	x29, x30, [sp, #-16]!
	stp	x27, x28, [sp, #-16]!
	stp	x25, x26, [sp, #-16]!
	stp	x23, x24, [sp, #-16]!
	stp	x21, x22, [sp, #-16]!
	stp	x19, x20, [sp, #-16]!
	stp	x17, x18, [sp, #-16]!
	stp	x15, x16, [sp, #-16]!
	stp	x13, x14, [sp, #-16]!
	stp	x11, x12, [sp, #-16]!
	stp	x9, x10, [sp, #-16]!
	stp	x7, x8, [sp, #-16]!
	stp	x5, x6, [sp, #-16]!
	stp	x3, x4, [sp, #-16]!
	stp	x1, x2, [sp, #-16]!
	switch_el x11, 3f, 2f, 1f
3:	mrs	x1, esr_el3
	mrs	x2, elr_el3
	b	0f
2:	mrs	x1, esr_el2
	mrs	x2, elr_el2
	b	0f
1:	mrs	x1, esr_el1
	mrs	x2, elr_el1
0:
	stp	x2, x0, [sp, #-16]!
	mov	x0, sp
.endm
#else
.macro	exception_entry
	stp	x29, x30, [sp, #-16]!
	stp	x27, x28, [sp, #-16]!
	stp	x25, x26, [sp, #-16]!
	stp	x23, x24, [sp, #-16]!
	stp	x21, x22, [sp, #-16]!
	stp	x19, x20, [sp, #-16]!
	stp	x17, x18, [sp, #-16]!
	stp	x15, x16, [sp, #-16]!
	stp	x13, x14, [sp, #-16]!
	stp	x11, x12, [sp, #-16]!
	stp	x9,  x10, [sp, #-16]!
	stp	x7,  x8,  [sp, #-16]!
	stp	x5,  x6,  [sp, #-16]!
	stp	x3,  x4,  [sp, #-16]!
	stp	x1,  x2,  [sp, #-16]!
	switch_el x11, 3f, 2f, 1f
3:	mrs	x1, esr_el3
	mrs	x2, elr_el3
	b	0f
2:	mrs	x1, esr_el2
	mrs	x2, elr_el2
	b	0f
1:	mrs	x1, esr_el1
	mrs	x2, elr_el1
0:
	stp	x2, x0, [sp, #-16]!
	mov	x0, sp
.endm

.macro	exception_exit
	ldp	x2, x0, [sp],#16

	switch_el x11, 3f, 2f, 1f
3:	msr	elr_el3, x2
	b	0f
2:	msr	elr_el2, x2
	b	0f
1:	msr	elr_el1, x2
0:
	ldp	x1,  x2,  [sp],#16
	ldp	x3,  x4,  [sp],#16
	ldp	x5,  x6,  [sp],#16
	ldp	x7,  x8,  [sp],#16
	ldp	x9,  x10, [sp],#16
	ldp	x11, x12, [sp],#16
	ldp	x13, x14, [sp],#16
	ldp	x15, x16, [sp],#16
	ldp	x17, x18, [sp],#16
	ldp	x19, x20, [sp],#16
	ldp	x21, x22, [sp],#16
	ldp	x23, x24, [sp],#16
	ldp	x25, x26, [sp],#16
	ldp	x27, x28, [sp],#16
	ldp	x29, x30, [sp],#16
	eret
.endm
#endif

#if 0
	.align	11
	.globl	vectors
vectors:
	.align	7
    b  _el1_sync_invalid        // Synchronous EL1t
	.align	7
    b  _el1_irq_invalid         // IRQ EL1t
	.align	7
    b  _el1_fiq_invalid         // FIQ EL1t
	.align	7
    b  _el1_error_invalid       // Error EL1t

	.align	7
    b  _el1_sync            // Synchronous EL1h
	.align	7
    b  _el1_irq             // IRQ EL1h
	.align	7
    b  _el1_fiq_invalid         // FIQ EL1h
	.align	7
    b  _el1_error_invalid       // Error EL1h

	.align	7
    b  _el0_sync            // Synchronous 64-bit EL0
	.align	7
    b  _el0_irq             // IRQ 64-bit EL0
	.align	7
    b  _el0_fiq_invalid         // FIQ 64-bit EL0
	.align	7
    b  _el0_error_invalid       // Error 64-bit EL0

	.align	7
    b  _el0_sync_compat         // Synchronous 32-bit EL0
	.align	7
    b  _el0_irq_compat          // IRQ 32-bit EL0
	.align	7
    b  _el0_fiq_invalid_compat      // FIQ 32-bit EL0
	.align	7
    b  _el0_error_invalid_compat    // Error 32-bit EL0

_el1_sync_invalid:
	bl el1_sync_invalid
	b _el1_sync_invalid
_el1_irq_invalid:
	bl el1_irq_invalid
	b _el1_irq_invalid
_el1_fiq_invalid:
	bl el1_fiq_invalid
	b _el1_fiq_invalid
_el1_error_invalid:
	bl el1_error_invalid
	b _el1_error_invalid
.align  6
_el1_sync:
	bl el1_sync
	b _el1_sync
.align  6
_el1_irq:
	exception_entry
	bl el1_irq
	exception_exit
.align  6
_el0_sync:
	bl el0_sync
	b _el0_sync
.align  6
_el0_irq:
	bl el0_irq
	b _el0_irq
_el0_fiq_invalid:
	bl el0_fiq_invalid
	b _el0_fiq_invalid
_el0_error_invalid:
	bl el0_error_invalid
	b _el0_error_invalid
.align  6
_el0_sync_compat:
	bl el0_sync_compat
	b _el0_sync_compat
.align  6
_el0_irq_compat:
	bl el0_irq_compat
	b _el0_irq_compat
_el0_fiq_invalid_compat:
	bl el0_fiq_invalid_compat
	b _el0_fiq_invalid_compat
_el0_error_invalid_compat:
	bl el0_error_invalid_compat
	b _el0_error_invalid_compat
#endif
