ENTRY(start)
memory_address = 0x00100000;

SECTIONS
{
  .text memory_address : AT(memory_address) {
    code = .;
    *(.text)
    *(.rodata)
    . = ALIGN(4096);
  }
 
  .data : AT(memory_address + (data - code))
  {
    data = .;
    *(.data)
    . = ALIGN(4096);
  }

  .bss : AT(memory_address + (bss - code))
  {
    bss = .;
    *(.bss)
    . = ALIGN(4096);
  }

  end = .;
  __kernel_end = .;
}
