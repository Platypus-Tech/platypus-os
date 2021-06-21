[BITS 32]

global start
start:
      mov esp, sys_stack
      jmp stublet

ALIGN 4
multiboot:

    PAGE_ALIGN   equ 1<<0
    MEMORY_INFO  equ 1<<0
    KLUDGE_AOUT  equ 1<<16
    MAGIC        equ 0x1BADB002
    FLAGS        equ PAGE_ALIGN | MEMORY_INFO | KLUDGE_AOUT
    CHECKSUM     equ -(MAGIC + FLAGS)

    EXTERN code, bss, end
    dd MAGIC
    dd FLAGS
    dd CHECKSUM
    
    dd multiboot
    dd code
    dd bss
    dd end
    dd start

stublet:
     extern kernel_main
     push eax
     push ebx
     call kernel_main
     jmp $

SECTION .bss
    resb 8192            
sys_stack:
