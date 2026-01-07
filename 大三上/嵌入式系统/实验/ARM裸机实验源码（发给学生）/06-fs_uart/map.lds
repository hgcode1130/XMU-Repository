OUTPUT_FORMAT("elf64-littleaarch64", "elf64-littleaarch64", "elf64-littleaarch64")
OUTPUT_ARCH(aarch64)
ENTRY(_start)
SECTIONS
{
	. = 0x00280000;
	. = ALIGN(8);
	.text :
	{
		start/start.o(.text)
		*(.text)
	}
	. = ALIGN(8);
    	.rodata : 
	{ *(.rodata) }
    	. = ALIGN(8);
    	.data : 
	{ *(.data) }
    	. = ALIGN(8);
    	.bss :
     	{ *(.bss) }
}
