ENTRY(_start)

SECTIONS
{
	. = 2M;

	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}

	.init : { *(.init) }
	.fini : { *(.fini) }

	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}

	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
		KEEP(*(.ctors))
		KEEP(*(.init_array))
		KEEP(*(SORT_BY_INIT_PRIORITY(.init_array.*)))
	}

	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}
}
