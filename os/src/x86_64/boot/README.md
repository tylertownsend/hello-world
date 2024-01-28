## Overview

This document provides an overview of the bootloader and memory allocation mechanisms (stack and heap) for a simple operating system. The bootloader is the first piece of code that runs when a computer starts, and it is responsible for loading the operating system kernel into memory. Memory allocation is crucial for managing the system's resources during runtime.

## Bootloader

### Description

The bootloader is a critical component that initializes the system and loads the kernel. It performs the following key tasks:

- Initializes hardware and prepares the system for kernel execution.
- Sets up a basic runtime environment, including stack setup.
- Loads the kernel into memory and transfers control to it.

### Components

1. **Assembly Code (`start`)**: 
   - Initializes the system in 32-bit mode.
   - Displays "OK" on the screen using VGA text mode.

2. **Multiboot Header**:
   - Required for GRUB to recognize and load the kernel.
   - Contains architecture information, header length, and checksum.

3. **Linker Script (`linked.ld`)**:
   - Organizes the kernel's memory layout.
   - Sets kernel entry point and memory sections.

4. **GRUB Configuration (`grub.cfg`)**:
   - Configures GRUB to load the kernel with Multiboot 2 protocol.

## Testing and Debugging

- **QEMU**: Utilized for testing the kernel in a virtualized environment.
- **Debugging**: Kernel-level debugging and logging mechanisms are recommended for tracking memory allocation and general operational errors.

## Further Development

## Setup
Bootloader Assembly Code: The first snippet is an assembly program. It's the actual bootloader that runs when the system starts. This code is written for a 32-bit processor (bits 32). It prints "OK" to the screen by directly writing to the video memory (address 0xb8000). After displaying the message, it halts the CPU (hlt instruction).

### GRUB Bootloader Configuration (`grub.cfg`)

- Sets a boot entry named "buffalo" to load the kernel from `/boot/kernel.bin`.
- Utilizes the `multiboot2` command for Multiboot version 2 compliance.

### Linker Script

- Organizes the kernel layout in memory, starting at 1MB.
- The `.boot` section includes the Multiboot header.
- The `.text` section contains the kernel code.

### Multiboot Header

- Contains the necessary elements for Multiboot2 compliance, including the magic number, architecture, header length, and checksum.

### `main64.asm`: Transition to 64-bit Mode

- `long_mode_start`: Entry point for 64-bit operations.
- Clears all segment registers and transitions the CPU to 64-bit long mode.
- Calls the kernel's main function (`__kernel_main__`).

### Overall Boot Process

1. **GRUB Loading**: Loads the kernel as per the configuration in `grub.cfg`.
2. **Multiboot Header Recognition**: GRUB validates the Multiboot header.
3. **Transition to Protected Mode**: GRUB sets up the environment for the kernel.
4. **Kernel Loading**: The kernel is loaded into memory at 1MB.
5. **Entering Long Mode**: The assembly code executes to transition to long mode.
6. **Kernel Execution**: Control is handed to the kernel's main function.



## Detailed Explanation of Assembly Code for Transitioning to Long Mode

This assembly code is designed to transition a 32-bit x86 CPU into 64-bit long mode, a crucial step for modern 64-bit operating systems. The code is organized into several sections, each with specific functions and purposes.

### Global and External Declarations

- `global start`: This directive makes the `start` label globally visible, indicating the entry point of the program to the linker.
- `extern long_mode_start`: This declares an external label `long_mode_start`, which is defined elsewhere, likely marking the entry point for 64-bit operations.

### Section .text: Executable Code

This section contains the actual executable instructions of the program.

#### Boot and Initial Setup

- `start:`: Marks the beginning of the program.
- `mov esp, stack_top`: Initializes the stack pointer (`esp`) to the top of the stack. The stack is essential for function calls, local variables, and interrupt handling.

Several function calls perform critical checks and setups:

- `check_multiboot`: Verifies if the system was booted using a Multiboot-compliant bootloader, which is necessary for certain boot-time configurations.
- `check_cpuid`: Checks if the CPU supports the CPUID instruction, essential for identifying processor capabilities.
- `check_long_mode`: Ensures the processor supports 64-bit long mode.
- `setup_page_tables`: Initializes minimal page tables for paging, a prerequisite for long mode.
- `enable_paging`: Enables paging, crucial for memory management in long mode.

#### Transition to Long Mode

- `lgdt [gdt64.pointer]`: Loads the Global Descriptor Table (GDT), necessary for segment descriptor definitions in protected mode.
- `jmp gdt64.code_segment:long_mode_start`: A far jump that switches the CPU to a 64-bit code segment and begins executing 64-bit code.

#### Error Handling

- The `check_*` functions set an error code and jump to the `error` label upon failure, ensuring that the system doesn't proceed with incompatible configurations.
- The `error` label contains code to display an error message and halt, preventing further execution.

### Section .bss: Uninitialized Data

This section reserves space for data structures needed during boot:

- `page_table_l4`, `page_table_l3`, `page_table_l2`: Space for Level 4, Level 3, and Level 2 page tables, part of the paging structure.
- `stack_bottom`, `stack_top`: Allocate space for the stack, critical for holding temporary data and managing function calls.

### Section .rodata: Read-Only Data

- `gdt64`: This defines the Global Descriptor Table (GDT), which is a data structure used in protected mode (32-bit) to define the characteristics of the various memory areas used during program execution, such as the base address, the size, and access privileges like executability and writability. Despite 64-bit mode (long mode) not relying on segment-based memory management as heavily as 32-bit mode, the GDT is still necessary during the transition phase from protected mode to long mode. The CPU requires a valid GDT even in long mode, although it's used differently

### Specific Assembly Instructions

The code uses various assembly instructions (`mov`, `cmp`, `jmp`, `or`, `cpuid`, `rdmsr`, `wrmsr`, etc.) for data manipulation, flow control, and system configuration.

### Why Use Paging?

Paging is a memory management scheme that eliminates the need for contiguous allocation of physical memory. It allows the system to use a memory efficiently and is essential for modern operating systems for several reasons:

1. **Support for Long Mode**: Long mode operation on x86-64 architectures requires paging to be enabled. It's not just a preference but a technical requirement.
   
2. **Memory Protection**: Paging allows the operating system to protect and isolate different processes' memory, enhancing system stability and security.

3. **Virtual Memory**: It enables the use of virtual memory, allowing systems to use more memory than physically available by swapping to disk.