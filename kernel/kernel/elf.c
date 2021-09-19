#include <kernel/elf.h>
#include <kernel/kheap.h>
#include <kernel/printm.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

bool check_file_elf(Elf32_Ehdr *header) {
  if (!header) {
    return;
  }

  if (header->e_ident[EI_MAG0] != ELFMAG0) {
    printm("ERROR: ELF Header EI_MAG0 incorrect.\n");
    return false;
  }
  if (header->e_ident[EI_MAG1] != ELFMAG1) {
    printm("ERROR: ELF Header EI_MAG1 incorrect.\n");
    return false;
  }
  if (header->e_ident[EI_MAG2] != ELFMAG2) {
    printm("ERROR: ELF Header EI_MAG2 incorrect.\n");
    return false;
  }
  if (header->e_ident[EI_MAG3] != ELFMAG3) {
    printm("ERROR: ELF Header EI_MAG3 incorrect.\n");
    return false;
  }

  return true;
}

bool check_supported_elf(Elf32_Ehdr *header) {
  if (!check_file_elf(header)) {
    printm("ERROR: Invalid ELF File.\n");
    return false;
  }
  if (header->e_ident[EI_CLASS] != ELFCLASS32) {
    printm("ERROR: Unsupported ELF File Class.\n");
    return false;
  }
  if (header->e_ident[EI_DATA] != ELFDATA2LSB) {
    printm("ERROR: Unsupported ELF File byte order.\n");
    return false;
  }
  if (header->e_machine != EM_386) {
    printm("ERROR: Unsupported ELF File target.\n");
    return false;
  }
  if (header->e_ident[EI_VERSION] != EV_CURRENT) {
    printm("ERROR: Unsupported ELF File version.\n");
    return false;
  }
  if (header->e_type != ET_REL && header->e_type != ET_EXEC) {
    printm("ERROR: Unsupported ELF File type.\n");
    return false;
  }

  return true;
}

void *load_rel_elf(Elf32_Ehdr *header) {
  int result;
  result = load_stage1_elf(header);

  if (result == ELF_RELOC_ERR) {
    printm("ERROR: Unable to load ELF file.\n");
    return NULL;
  }

  result = load_stage2_elf(header);

  if (result == ELF_RELOC_ERR) {
    printm("ERROR: Unable to load ELF file.\n");
    return NULL;
  }

  return (void *)header->e_entry;
}

void *load_file_elf(void *file) {
  Elf32_Ehdr *header = (Elf32_Ehdr *)file;

  if (!check_supported_elf(header)) {
    printm("ERROR: ELF File cannot be loaded.\n");
    return;
  }
  switch (header->e_type) {
  case ET_EXEC:
    // TODO: Implement this
    return NULL;
  case ET_REL:
    return load_rel_elf(header);
  }

  return NULL;
}

Elf32_Shdr *sheader_elf(Elf32_Ehdr *header) {
  return (Elf32_Shdr *)((int)header + header->e_shoff);
}

Elf32_Shdr *section_elf(Elf32_Ehdr *header, int idx) {
  return &sheader_elf(header)[idx];
}

char *str_table_elf(Elf32_Ehdr *header) {
  if (header->e_shstrndx == SHN_UNDEF) {
    return NULL;
  }

  return (char *)header + section_elf(header, header->e_shstrndx)->sh_offset;
}

char *lookup_string_elf(Elf32_Ehdr *header, int offset) {
  char *strtab = str_table_elf(header);

  if (strtab == NULL) {
    return NULL;
  }

  return strtab + offset;
}

void *lookup_symbol_elf(const char *name) {
  return NULL;
}

int get_symval_elf(Elf32_Ehdr *header, int table, unsigned int idx) {
  if (table == SHN_UNDEF || idx == SHN_UNDEF) {
    return 0;
  }

  Elf32_Shdr *symtab = section_elf(header, table);

  uint32_t symtab_entries = symtab->sh_size / symtab->sh_entsize;

  if (idx >= symtab_entries) {
    printm("ERROR: Symbol Index out of Range (%d:%u).\n", table, idx);
    return ELF_RELOC_ERR;
  }

  int symaddr = (int)header + symtab->sh_offset;
  Elf32_Sym *symbol = &((Elf32_Sym *)symaddr)[idx];

  if (symbol->st_shndx == SHN_UNDEF) {

    Elf32_Shdr *strtab = section_elf(header, symtab->sh_link);
    const char *name =
        (const char *)header + strtab->sh_offset + symbol->st_name;

    void *target = lookup_symbol_elf(name);

    if (target == NULL) {
      if (ELF32_ST_BIND(symbol->st_info) & STB_WEAK) {
        return 0;

      } else {
        printm("ERROR: Undefined External Symbol: %s.\n", name);
        return ELF_RELOC_ERR;
      }
    } else {
      return (int)target;
    }
  } else if (symbol->st_shndx == SHN_ABS) {
    return symbol->st_value;
  } else {
    Elf32_Shdr *target = section_elf(header, symbol->st_shndx);
    return (int)header + symbol->st_value + target->sh_offset;
  }
}

int load_stage1_elf(Elf32_Ehdr *header) {
  Elf32_Shdr *shdr = sheader_elf(header);

  unsigned int i;

  for (i = 0; i < header->e_shnum; i++) {
    Elf32_Shdr *section = &shdr[i];

    if (section->sh_type == SHT_NOBITS) {
      if (!section->sh_size) {
        continue;
      }

      if (section->sh_flags & SHF_ALLOC) {
        void *mem = kmalloc(section->sh_size);
        memset(mem, 0, section->sh_size);
        section->sh_offset = (int)mem - (int)header;
        printm("Allocated memory for a section (%ld).\n", section->sh_size);
      }
    }
  }

  return 0;
}

int load_stage2_elf(Elf32_Ehdr *header) {
  Elf32_Shdr *shdr = sheader_elf(header);

  unsigned int i, idx;

  for (i = 0; i < header->e_shnum; i++) {
    Elf32_Shdr *section = &shdr[i];

    if (section->sh_type == SHT_REL) {
      for (idx = 0; idx < section->sh_size / section->sh_entsize; idx++) {
        Elf32_Rel *reltab =
            &((Elf32_Rel *)((int)header + section->sh_offset))[idx];
        int result = do_reloc_elf(header, reltab, section);

        if (result == ELF_RELOC_ERR) {
          printm("ERROR: Failed to relocate symbol.\n");
          return ELF_RELOC_ERR;
        }
      }
    }
  }

  return 0;
}

int do_reloc_elf(Elf32_Ehdr *header, Elf32_Rel *rel, Elf32_Shdr *reltab) {
  Elf32_Shdr *target = section_elf(header, reltab->sh_info);

  int addr = (int)header + target->sh_offset;
  int *ref = (int *)(addr + rel->r_offset);

  int symval = 0;
  if (ELF32_R_SYM(rel->r_info) != SHN_UNDEF) {
    symval = get_symval_elf(header, reltab->sh_link, ELF32_R_SYM(rel->r_info));
    if (symval == ELF_RELOC_ERR) {
      return ELF_RELOC_ERR;
    }
  }

  switch (ELF32_R_TYPE(rel->r_info)) {
  case R_386_NONE:
    break;
  case R_386_32:
    *ref = DO_386_32(symval, *ref);
    break;
  case R_386_PC32:
    *ref = DO_386_PC32(symval, *ref, (int)ref);
    break;
  default:
    printm("ERROR: Unsupported Relocation Type (%d).\n",
           ELF32_R_TYPE(rel->r_info));
    return ELF_RELOC_ERR;
  }

  return symval;
}
