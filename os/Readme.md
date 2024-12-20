# A small OS
## Overview
This is a small OS that I am developing for fun. It is written in C and Assembly. It is a 32-bit OS that is designed to run on x86 hardware. It is not meant to be a full-fledged OS, but rather a learning experience. 

## Development Environment

| Toolchain | Version | Description | Install Command |
| --- | --- | --- | --- |
|nasm|2.15.05|Assembler|`sudo apt install nasm`|
|qemu|4.2.1|Emulator|`sudo apt install qemu-system-x86`|
|grub|2.04|Bootloader|`sudo apt install grub-pc-bin`|
|hexcurse|1.58|Hex Editor|`sudo apt install hexcurse`|
| cross-compiler | 10.2.0 | Compiler | Multiple see section developing  

### Cross-compiler
[GCC_Cross-Compiler](https://wiki.osdev.org/GCC_Cross-Compiler)

| Toolchain | Version | Description |
| --- | --- | --- |
| [binutils](https://sourceware.org/pub/binutils/releases/binutils-2.35.tar.gz) | 2.35 | Assembler, Linker, Object Copy |
| [gcc](https://bigsearcher.com/mirrors/gcc/releases/gcc-10.2.0/) | 10.2.0 | C Compiler |

### hexcurse
- `hexcurse bin/os.bin`
- `ctrl + h` for help
