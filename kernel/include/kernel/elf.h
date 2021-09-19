#ifndef _KERNEL_ELF_H
#define _KERNEL_ELF_H

#include <stdbool.h>
#include <stdint.h>

typedef uint16_t Elf32_Half;
typedef uint32_t Elf32_Off;
typedef uint32_t Elf32_Addr;
typedef uint32_t Elf32_Word;
typedef int32_t Elf32_Sword;

#define ELF_NIDENT 16

typedef struct {
  uint8_t e_ident[ELF_NIDENT];
  Elf32_Half e_type;
  Elf32_Half e_machine;
  Elf32_Word e_version;
  Elf32_Addr e_entry;
  Elf32_Off e_phoff;
  Elf32_Off e_shoff;
  Elf32_Word e_flags;
  Elf32_Half e_ehsize;
  Elf32_Half e_phentsize;
  Elf32_Half e_phnum;
  Elf32_Half e_shentsize;
  Elf32_Half e_shnum;
  Elf32_Half e_shstrndx;
} Elf32_Ehdr;

enum Elf_Ident {
  EI_MAG0 = 0,
  EI_MAG1 = 1,
  EI_MAG2 = 2,
  EI_MAG3 = 3,
  EI_CLASS = 4,
  EI_DATA = 5,
  EI_VERSION = 6,
  EI_OSABI = 7,
  EI_ABIVERSION = 8,
  EI_PAD = 9
};

#define ELFMAG0 0x7F
#define ELFMAG1 'E'
#define ELFMAG2 'L'
#define ELFMAG3 'F'

#define ELFDATA2LSB (1)
#define ELFCLASS32 (1)

enum Elf_Type { ET_NONE = 0, ET_REL = 1, ET_EXEC = 2 };

#define EM_386 (3)
#define EV_CURRENT (1)

typedef struct {
  Elf32_Word sh_name;
  Elf32_Word sh_type;
  Elf32_Word sh_flags;
  Elf32_Addr sh_addr;
  Elf32_Off sh_offset;
  Elf32_Word sh_size;
  Elf32_Word sh_link;
  Elf32_Word sh_info;
  Elf32_Word sh_addralign;
  Elf32_Word sh_entsize;
} Elf32_Shdr;

#define SHN_UNDEF (0x00)
#define SHN_ABS (0x01)

enum ShT_Types {
  SHT_NULL = 0,
  SHT_PROGBITS = 1,
  SHT_SYMTAB = 2,
  SHT_STRTAB = 3,
  SHT_RELA = 4,
  SHT_NOBITS = 8,
  SHT_REL = 9,
};

enum ShT_Attributes { SHF_WRITE = 0x01, SHF_ALLOC = 0x02 };

typedef struct {
  Elf32_Word st_name;
  Elf32_Addr st_value;
  Elf32_Word st_size;
  uint8_t st_info;
  uint8_t st_other;
  Elf32_Half st_shndx;
} Elf32_Sym;

#define ELF32_ST_BIND(INFO) ((INFO) >> 4)
#define ELF32_ST_TYPE(INFO) ((INFO)&0x0F)

enum StT_Bindings { STB_LOCAL = 0, STB_GLOBAL = 1, STB_WEAK = 2 };

enum StT_Types { STT_NOTYPE = 0, STT_OBJECT = 1, STT_FUNC = 2 };

typedef struct {
  Elf32_Addr r_offset;
  Elf32_Word r_info;
} Elf32_Rel;

typedef struct {
  Elf32_Addr r_offset;
  Elf32_Word r_info;
  Elf32_Sword r_addend;
} Elf32_Rela;

#define ELF32_R_SYM(INFO) ((INFO) >> 8)
#define ELF32_R_TYPE(INFO) ((uint8_t)(INFO))

enum RtT_Types { R_386_NONE = 0, R_386_32 = 1, R_386_PC32 = 2 };

#define ELF_RELOC_ERR -1
#define DO_386_32(S, A) ((S) + (A))
#define DO_386_PC32(S, A, P) ((S) + (A) - (P))

typedef struct {
  Elf32_Word p_type;
  Elf32_Off p_offset;
  Elf32_Addr p_vaddr;
  Elf32_Addr p_paddr;
  Elf32_Word p_filesz;
  Elf32_Word p_memsz;
  Elf32_Word p_flags;
  Elf32_Word p_align;
} Elf32_Phdr;

bool check_file_elf(Elf32_Ehdr *header);
bool check_supported_elf(Elf32_Ehdr *header);
void *load_rel_elf(Elf32_Ehdr *header);
void *load_file_elf(void *file);
Elf32_Shdr *sheader_elf(Elf32_Ehdr *header);
Elf32_Shdr *section_elf(Elf32_Ehdr *header, int idx);
char *str_table_elf(Elf32_Ehdr *header);
char *lookup_string_elf(Elf32_Ehdr *header, int offset);
void *lookup_symbol_elf(const char *name);
int get_symval_elf(Elf32_Ehdr *header, int table, unsigned int idx);
int load_stage1_elf(Elf32_Ehdr *header);
int load_stage2_elf(Elf32_Ehdr *header);
int do_reloc_elf(Elf32_Ehdr *header, Elf32_Rel *rel, Elf32_Shdr *reltab);

#endif //_KERNEL_ELF_H
