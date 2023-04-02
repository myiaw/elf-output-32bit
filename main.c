#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <elf.h>

int output_elf_header(Elf32_Ehdr *elf_header, const char *elf_path) {
    FILE *fp = fopen(elf_path, "rb");
    if (fp == NULL) {
        fprintf(stderr, "Error: Cannot open file %s", elf_path);
        return 1;
    }
    size_t read_size = fread(elf_header, sizeof(Elf32_Ehdr), 1, fp);
    if (read_size != 1) {
        fprintf(stderr, "Error: Cannot read ELF header from file %s", elf_path);
        fclose(fp);
        return 1;
    }
    //Magic number
    printf("ELF Header:\n");
    printf("  Magic number:\t\t\t %02X %02X %02X %02X\n", elf_header->e_ident[0], elf_header->e_ident[1],
           elf_header->e_ident[2],
           elf_header->e_ident[3]); //First byte is an identifier, if it isn't 7F it's not ELF, then the next 3 are E, L, F.

    //Amount of bits
    if (elf_header->e_ident[EI_CLASS] == ELFCLASS32) {
        printf("  Class:\t\t\t %d-bit\n", 32);
    } else if (elf_header->e_ident[EI_CLASS] == ELFCLASS64) {
        printf("  Class:\t\t\t %d-bit\n", 64);
    } else {
        printf("  Class:\t\t\t Invalid class\n");
    }
// endianness, complement
    if (elf_header->e_ident[EI_DATA] == ELFDATA2LSB) {
        printf("  Data:\t\t\t\t 2's complement, little endian\n");
    } else if (elf_header->e_ident[EI_DATA] == ELFDATA2MSB) {
        printf("  Data:\t\t\t\t 2's complement, big endian\n");
    } else {
        printf("  Data:\t\t\t\t Invalid data encoding\n");
    }
    //Version
    if (elf_header->e_version == EV_CURRENT) {
        printf("  Version:\t\t\t 1 (current)\n");
    } else {
        printf("  Version:\t\t\t Invalid version: %d\n", elf_header->e_version);
    }
    //OS ABI
    if (elf_header->e_ident[EI_OSABI] == ELFOSABI_SYSV) {
        printf("  OS ABI: \t\t\t System V\n");
    } else if (elf_header->e_ident[EI_OSABI] == ELFOSABI_LINUX) {
        printf("  OS ABI: \t\t\t Linux\n");
    } else if (elf_header->e_ident[EI_OSABI] == ELFOSABI_FREEBSD) {
        printf("  OS ABI: \t\t\t FreeBSD\n");

    } else if (elf_header->e_ident[EI_OSABI] == ELFOSABI_NONE) {
        printf("  OS ABI:\t\t\t Windows\n");
    } else {
        printf("  OS ABI:\t\t\t Unknown\n");
    }

    // ABI Version
    printf("  ABI Version:\t\t\t %d\n", elf_header->e_ident[EI_ABIVERSION]);
    // File type
    if(elf_header->e_type == ET_EXEC){
        printf("  Type:\t\t\t\t Executable file\n");
    }else if(elf_header->e_type == ET_DYN){
        printf("  Type:\t\t\t\t Shared object file\n");
    }
    else if(elf_header->e_type == ET_REL){
        printf("  Type:\t\t\t\t Relocatable file\n");
    }
    else if(elf_header->e_type == ET_CORE){
        printf("  Type:\t\t\t\t Core file\n");
    }
    else{
        printf("  Type:\t\t\t\t Unknown\n");
    }
    // Machine
    if(elf_header->e_machine == EM_386){
        printf("  Machine:\t\t\t Intel 80386\n");
    }
    else if(elf_header->e_machine == EM_X86_64){
        printf("  Machine:\t\t\t AMD x86-64 architecture\n");
    }
    else if(elf_header->e_machine == EM_ARM){
        printf("  Machine:\t\t\t ARM\n");
    }
    else if(elf_header->e_machine == EM_AARCH64){
        printf("  Machine:\t\t\t ARM 64-bit\n");
    }
    else{
        printf("  Machine:\t\t\t Unknown\n");
    }
// Version
    if(elf_header->e_version == EV_CURRENT){
        printf("  Version:\t\t\t %d\n", EV_CURRENT);
    }
    else{
        printf("  Version:\t\t\t Unknown\n");
    }
// Entry point
    printf("  Entry point address:\t\t 0x%08x\n", elf_header->e_entry);
// Start of program headers
    printf("  Start of program headers:\t %d\n", elf_header->e_phoff);
// Start of section headers
    printf("  Start of section headers:\t %d\n", elf_header->e_shoff);
// Flags
    printf("  Flags:\t\t\t 0x%08x\n", elf_header->e_flags);
// Size of this header
    printf("  Size of this header:\t\t %d B\n", elf_header->e_ehsize);
// Size of program headers
    printf("  Size of program headers:\t %d B\n", elf_header->e_phentsize);
// Number of program headers
    printf("  Number of program headers:\t %d\n", elf_header->e_phnum);
// Size of section headers
    printf("  Size of section headers:\t %d B\n", elf_header->e_shentsize);
// Number of section headers
    printf("  Number of section headers:\t %d\n", elf_header->e_shnum);
// Section header string table index
    printf("  Section header string table index: %d\n", elf_header->e_shstrndx);

    fclose(fp);
    return 0;
}




        int main(int argc, char *argv[]) {
            Elf32_Ehdr header;
//            if (output_elf_header(&header, "hello.o") != 0) {
//                return 1;
//            }
//            if (outputFunctionsGreaterThan(&header, "hello.o") != 0) {
//                return 1;
//            }
    if (argc != 3) {
        fprintf(stderr, "Error: Invalid number of arguments\n");
        return 1;
    }
//    if(strcmp(argv[1], "-l") == 0){
//        const char *elf_path = argv[2];
//    }

    if (strcmp(argv[1], "-h") == 0) {
        const char *elf_path = argv[2];
        if (output_elf_header(&header, elf_path) != 0) {
            return 1;
        }
    }


            return 0;
        }

