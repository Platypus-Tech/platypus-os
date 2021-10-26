#include <kernel/elf.h>
#include <stdint.h>
#include <string.h>

const char *lookup_symbol_elf(uint32_t addr, elf_t *elf) {
  for (int i = 0; i < (elf->symtabsz / sizeof(elf_symbol_t)); i++) {
    if (ELF32_ST_TYPE(elf->symtab[i].info) != 0x2) {
      continue;
    }

    if ((addr >= elf->symtab[i].value) &&
        (addr < (elf->symtab[i].value + elf->symtab[i].size))) {
      const char *name =
          (const char *)((uint32_t)elf->strtab + elf->symtab[i].name);
      return name;
    }
  }
}

elf_t elf_from_multiboot(multiboot_elf_section_header_table_t elfinfo) {
  elf_t elf;
  elf_section_header_t *sh = (elf_section_header_t *)elfinfo.addr;

  uint32_t shstrtab = sh[elfinfo.shndx].addr;

  for (int i = 0; i < elfinfo.num; i++) {
    const char *name = (const char *)(shstrtab + sh[i].name);
    if (strcmp(name, ".strtab") == 0) {
      elf.strtab = (const char *)sh[i].addr;
      elf.strtabsz = sh[i].size;
    }
    if (strcmp(name, ".symtab") == 0) {
      elf.symtab = (elf_symbol_t *)sh[i].addr;
      elf.symtabsz = sh[i].size;
    }
  }
  return elf;
}
