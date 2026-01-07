OUTPUT_FORMAT("elf64-littleaarch64", "elf64-littleaarch64", "elf64-littleaarch64")
OUTPUT_ARCH(aarch64)
ENTRY(_start)

STACK_UND_SIZE	= 0x40000;	/* 256KB */
STACK_ABT_SIZE	= 0x40000;	/* 256KB */
STACK_IRQ_SIZE	= 0x40000;	/* 256KB */
STACK_FIQ_SIZE	= 0x40000;	/* 256KB */
STACK_SRV_SIZE	= 0x100000;	/* 1 MB */

MEMORY
{
	rom(rx) : org = 0x41c00000, len = 0x02000000	/* 32 MB */
	ram(rwx): org = 0x42100000, len = 0x0a000000	/* 160 MB */
}

SECTIONS
{
	. = ALIGN(8);
	.text :
	{
		PROVIDE(__image_start = .);
		PROVIDE(__text_start = .);
		start/start.o (.text)
		*(.text*)
		*(.glue*);
		*(.init.text)
		*(.exit.text)
		PROVIDE(__text_end = .);
	} > rom

	.rodata ALIGN(8) :
	{
		PROVIDE(__rodata_start = .);
		*(SORT_BY_ALIGNMENT(SORT_BY_NAME(.rodata*)))
		PROVIDE(__rodata_end = .);
	} > rom

	.data_shadow ALIGN(8) :
	{
		PROVIDE(__data_shadow_start = .);
		PROVIDE(__data_shadow_end = (. + SIZEOF(.data)));
		PROVIDE(__image_end = .);
	} > rom

	.data : AT(ADDR(.data_shadow))
	{
		PROVIDE(__data_start = .);	
		*(.data*)
		. = ALIGN(8);
  		PROVIDE(__data_end = .);
	} > ram

	.ARM.exidx ALIGN(8) :
	{
		PROVIDE (__exidx_start = .);
		*(.ARM.exidx*)
		PROVIDE (__exidx_end = .);
	} > ram

	.ARM.extab ALIGN(8) :
	{
		PROVIDE (__extab_start = .);
		*(.ARM.extab*)
		PROVIDE (__extab_end = .);
	} > ram

	.bss ALIGN(8) (NOLOAD) :
	{
		PROVIDE(__bss_start = .);
		*(.bss*)
		*(.sbss*)
		*(COMMON)
		. = ALIGN(8);
		PROVIDE(__bss_end = .);
	} > ram

	.heap ALIGN(8) (NOLOAD) :
	{
		PROVIDE(__heap_start = .);
		*(.heap*)
		. = ALIGN(8);
		PROVIDE(__heap_end = .);
	} > ram
	
	.stack ALIGN(8) (NOLOAD) :
	{
		PROVIDE(__stack_start = .);
		PROVIDE(__stack_und_start = .);
		. += STACK_UND_SIZE;
		PROVIDE(__stack_und_end = .);
		. = ALIGN(8);
		PROVIDE(__stack_abt_start = .);
		. += STACK_ABT_SIZE;
		PROVIDE(__stack_abt_end = .);
		. = ALIGN(8);
		PROVIDE(__stack_irq_start = .);
		. += STACK_IRQ_SIZE;
		PROVIDE(__stack_irq_end = .);
		. = ALIGN(8);
		PROVIDE(__stack_fiq_start = .);
		. += STACK_FIQ_SIZE;
		PROVIDE(__stack_fiq_end = .);
		. = ALIGN(8);
		PROVIDE(__stack_srv_start = .);
		. += STACK_SRV_SIZE;
		PROVIDE(__stack_srv_end = .);
		. = ALIGN(8);
		PROVIDE(__stack_end = .);
	} > ram

	.stab 0 : { *(.stab) }
	.stabstr 0 : { *(.stabstr) }
	.stab.excl 0 : { *(.stab.excl) }
	.stab.exclstr 0 : { *(.stab.exclstr) }
	.stab.index 0 : { *(.stab.index) }
	.stab.indexstr 0 : { *(.stab.indexstr) }
	.comment 0 : { *(.comment) }
	.debug_abbrev 0 : { *(.debug_abbrev) }
	.debug_info 0 : { *(.debug_info) }
	.debug_line 0 : { *(.debug_line) }
	.debug_pubnames 0 : { *(.debug_pubnames) }
	.debug_aranges 0 : { *(.debug_aranges) }
}
