#include "macro.h"

.globl	_start
_start:
	b	reset
	.align 3
reset:
	adr	x0, vectors
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
halt:
	mov x0, #1;
	mov x1, #0;
	bl main
	b halt
lowlevel_init:
	mov	x29, x30			/* Save LR */
	ldr	x0, =0xFEE00000          //RKIO_GICD_PHYS   GIC DIST 
	bl	gic_init_secure

	ldr	x0, =0xFEF00000          //RKIO_GICR_PHYS
	bl	gic_init_secure_percpu
	mov	x30, x29			/* Restore LR */
	ret

gic_init_secure:
	mov	w9, #0x37		         //EnableGrp0 | EnableGrp1NS  
				            	 //EnableGrp1S | ARE_S | ARE_NS  
	str	w9, [x0, 0x0000]	     //Secure GICD_CTLR 
	ldr	w9, [x0, 0x0004]
	and	w10, w9, #0x1f		     //ITLinesNumber 
	cbz	w10, 1f			         //No SPIs 
	add	x11, x0, (0x0080 + 4)	//interrupt group
	add	x12, x0, (0x0d00 + 4)	//Interrupt Group Modifier Registers
	mov	w9, #~0
0:	str	w9, [x11], #0x4
	str	wzr, [x12], #0x4	     //Config SPIs as Group1NS 
	sub	w10, w10, #0x1
	cbnz	w10, 0b
1:
	ret

gic_init_secure_percpu:
	mrs	x10, mpidr_el1
	lsr	x9, x10, #32
	bfi	x10, x9, #24, #8	    //w10 is aff3:aff2:aff1:aff0 
	mov	x9, x0
1:	ldr	x11, [x9, 0x0008]
	lsr	x11, x11, #32		    //w11 is aff3:aff2:aff1:aff0 
	cmp	w10, w11
	b.eq	2f
	add	x9, x9, #(2 << 16)
	b	1b
2:	mov	w10, #~0x2
	ldr	w11, [x9, 0x0014]
	and	w11, w11, w10		    //Clear ProcessorSleep 
	str	w11, [x9, 0x0014]
	dsb	st
	isb
3:	ldr	w10, [x9, 0x0014]
	tbnz	w10, #2, 3b		    //Wait Children be Alive 

	add	x10, x9, #(1 << 16)   	//SGI_Base 
	mov	w11, #~0
	str	w11, [x10, 0x0080]
	str	wzr, [x10, 0x0d00]	    //SGIs|PPIs Group1NS 
	mov	w11, #0x1		        //Enable SGI 0 
	str	w11, [x10, 0x0100]
	switch_el x0, el3_sre, el2_sre, el1_sre

el3_sre:
	mrs	x10, S3_6_C12_C12_5
	orr	x10, x10, #0xf		     //SRE & Disable IRQ/FIQ Bypass & 
					             //Allow EL2 access to ICC_SRE_EL2 
	msr	S3_6_C12_C12_5, x10
	isb

el2_sre:
	mrs	x10, S3_4_C12_C9_5
	orr	x10, x10, #0xf		     //SRE & Disable IRQ/FIQ Bypass & 
				             	 //Allow EL1 access to ICC_SRE_EL1 
	msr	S3_4_C12_C9_5, x10
	isb

el1_sre:
	mrs	x0, CurrentEL	         //check currentEL 
	cmp	x0, 0xC
	b.ne	el1_ctlr	         //currentEL != EL3 

el3_ctlr:
	mov	x10, #0x3		         //EnableGrp1NS | EnableGrp1S 
	msr	S3_6_C12_C12_7, x10
	isb

	msr	S3_6_C12_C12_4, xzr
	isb

el1_ctlr:
	mov	x10, #0x3		         //EnableGrp1NS | EnableGrp1S 
	msr	S3_0_C12_C12_7, x10
	isb

	msr	S3_0_C12_C12_4, xzr    	 //NonSecure ICC_CTLR_EL1 
	isb

	mov	x10, #0xf0		         //Non-Secure access to ICC_PMR_EL1 
	msr	S3_0_C4_C6_0, x10
	isb	

	ret

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

	.align	11
vectors:
	.align	7
	b	_do_bad_sync	    //Current EL Synchronous Thread  
                          
	.align	7              
	b	_do_bad_irq	        //Current EL IRQ Thread  
                            
	.align	7               
	b	_do_bad_fiq	        //Current EL FIQ Thread 
                            
	.align	7               
	b	_do_bad_error	    //Current EL Error Thread 
                           
	.align	7               
	b	_do_sync	        //Current EL Synchronous Handler 
                            
	.align	7               
	b	_do_irq		        //Current EL IRQ Handler 
                            
	.align	7               
	b	_do_fiq		        //Current EL FIQ Handler 
                           
	.align	7              
	b	_do_error	        //Current EL Error Handler 


_do_bad_sync:
	exception_entry
	bl	halt 				//do_bad_sync

_do_bad_irq:
	exception_entry
	bl	halt 				//do_bad_irq

_do_bad_fiq:
	exception_entry
	bl	halt				//do_bad_fiq

_do_bad_error:
	exception_entry
	bl	halt 				//do_bad_error

_do_sync:
	exception_entry
	bl	halt 				//do_sync

_do_irq:
	exception_entry
	bl	do_irq              //do_irq
	exception_exit

_do_fiq:
	exception_entry
	bl	halt 				//do_fiq

_do_error:
	exception_entry
	bl	halt 				//do_error
