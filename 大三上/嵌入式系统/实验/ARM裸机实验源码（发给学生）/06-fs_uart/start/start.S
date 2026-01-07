#include "macro.h"

.globl	_start
_start:
	b	reset
	.align 3
reset:
#if 1
	switch_el x1, 3f, 2f, 1f
3:	msr	vbar_el3, x0
	mrs	x0, scr_el3
	orr	x0, x0, #0xf			/* SCR_EL3.NS|IRQ|FIQ|EA */
	msr	scr_el3, x0
	msr	cptr_el3, xzr			/* Enable FP/SIMD */
	ldr	x0, =240000000
	msr	cntfrq_el0, x0			/* Initialize CNTFRQ */
	b	0f
2:	msr	vbar_el2, x0
	mov	x0, #0x33ff
	msr	cptr_el2, x0			/* Enable FP/SIMD */
	b	0f
1:	msr	vbar_el1, x0
	mov	x0, #3 << 20
	msr	cpacr_el1, x0			/* Enable FP/SIMD */
0:
	bl	lowlevel_init
	branch_if_master x0, x1, master_cpu
slave_cpu:
	wfe
	ldr	x1, =0x41c00000
	ldr	x0, [x1]
	cbz	x0, slave_cpu
	br	x0			/* branch to the given address */
master_cpu:
#endif
_main:
	mov x0, #1;
	mov x1, #0;
	bl main
	b _main
ENTRY(lowlevel_init)
	mov	x29, x30			/* Save LR */
	branch_if_master x0, x1, 2f
	bl	armv8_switch_to_el2
2:
	mov	x30, x29			/* Restore LR */
	ret
ENDPROC(lowlevel_init)

ENTRY(armv8_switch_to_el2)
switch_el x0, 1f, 0f, 0f
0:  ret
1:  armv8_switch_to_el2_m x0
ENDPROC(armv8_switch_to_el2)


