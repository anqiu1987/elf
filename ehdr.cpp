#include"elflib.h"
#include<stdio.h>
#define CASE_BREAK(type)\
	case type:         ret=#type; break
const char* get_ei_class(unsigned char type)
{
	char const *ret;
	switch(type)
	{
		CASE_BREAK(ELFCLASSNONE);
		CASE_BREAK(ELFCLASS32);
		CASE_BREAK(ELFCLASS64);
		CASE_BREAK(ELFCLASSNUM);
		default:
			ret = "unknown";
			break;
	}

	return ret;
}
const char* get_ei_type(unsigned short type)
{
	const char * ret;
	switch(type)
	{
		CASE_BREAK(ET_NONE);
		CASE_BREAK(ET_REL);
		CASE_BREAK(ET_EXEC);
		CASE_BREAK(ET_DYN);
		CASE_BREAK(ET_CORE);
		CASE_BREAK(ET_NUM);
		CASE_BREAK(ET_LOOS);
		CASE_BREAK(ET_HIOS);
		CASE_BREAK(ET_LOPROC);
		CASE_BREAK(ET_HIPROC);
		default:
		ret = "unknown";
		break;
	}

	return ret;
}
void dump_ehdr(ELF_t *elf)
{
	Elf64_Ehdr* elf_entity = GET_EHDR(elf);
	printf("\n %50s \n", "elf header");

	printf("e_ident(ELFMAG0)   : 0x%x\n", elf_entity->e_ident[0]);
	printf("e_ident(ELFMAG1)   : %c\n",   elf_entity->e_ident[1]);
	printf("e_ident(ELFMAG2)   : %c\n",   elf_entity->e_ident[2]);
	printf("e_ident(ELFMAG3)   : %c\n",   elf_entity->e_ident[3]);
	printf("e_ident(ELFCLASS)  : %s\n",get_ei_class(elf_entity->e_ident[4]));
	printf("e_ident(EI_DATA)   : %d\n",elf_entity->e_ident[5]);
	printf("e_ident(EI_VERSION): %d\n",elf_entity->e_ident[6]);
	printf("e_ident(EI_PAD)    : %d\n",elf_entity->e_ident[7]);
//	EPRINTF(e_type, "        :%hd\n");//object file type
	printf("e_type:            :%s\n",get_ei_type(elf_entity->e_type));
	EPRINTF(e_machine, "          :%hd\n");//architecture
	EPRINTF(e_version, "          :%d\n");//object file version
	EPRINTF(e_entry, "            :0x%lx\n");//virtual address
	EPRINTF(e_phoff, "            :%ld\n");//program header table offset
	EPRINTF(e_shoff, "            :%ld\n");//section header offset
	EPRINTF(e_flags, "            :%d\n");//processor spec flags
	EPRINTF(e_ehsize, "           :%hd\n");//elf header size
	EPRINTF(e_phentsize, "        :%hd\n");//program header table entry size 
	EPRINTF(e_phnum, "            :%hd\n");//program header entry count 
	EPRINTF(e_shentsize, "        :%hd\n");//section header size
	EPRINTF(e_shnum, "            :%hd\n");//section header entry count
	EPRINTF(e_shstrndx, "         :%hd\n");//section header index string table
}

int verify_file_format(ELF_t * elf)
{

	Elf64_Ehdr* elf_entity = GET_EHDR(elf);
	if(elf_entity->e_ident[1] !='E' || elf_entity->e_ident[2] != 'L' || elf_entity->e_ident[3] != 'F')
		return -1;

	if(elf_entity->e_ident[4] != ELFCLASS64)
		ERROR_RET("not 64 bit class", -1);

	return 0;
}
