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

## Memory Allocation

### Stack Allocation

- **Purpose**: Used for managing function calls and local variables.
- **Initialization**: Set up very early, typically in the bootloader or initial assembly code.
- **Functionality**: Automatically handles saving return addresses and local variables during function calls.
- **Implementation**: Involves setting the stack pointer to a fixed-size memory area.

### Heap Allocation

- **Purpose**: Provides dynamic memory allocation during runtime.
- **Implementation**: Requires developing a memory allocator (e.g., for `malloc` and `free` functionality).
- **Initialization**: Set up after basic kernel services, such as memory management.
- **Functionality**: Manages dynamic memory requests, including allocation and deallocation.
- **Considerations**: Involves handling fragmentation and synchronization in multitasking environments.

## Testing and Debugging

- **QEMU**: Utilized for testing the kernel in a virtualized environment.
- **Debugging**: Kernel-level debugging and logging mechanisms are recommended for tracking memory allocation and general operational errors.

## Further Development

## Setup
Bootloader Assembly Code: The first snippet is an assembly program. It's the actual bootloader that runs when the system starts. This code is written for a 32-bit processor (bits 32). It prints "OK" to the screen by directly writing to the video memory (address 0xb8000). After displaying the message, it halts the CPU (hlt instruction).

Multiboot Header: This is a special header required by the GRUB bootloader to recognize your kernel. It includes the magic number (0xe85250d6), the target architecture (32-bit mode), the header length, and a checksum. The end tag indicates the end of the header.

Linker Script (linked.ld): This script tells the linker how to assemble the different parts of your kernel. It sets the starting address of the kernel to 1MB (.=1M;), includes the multiboot header, and then the actual code (.text section). The ENTRY(start) directive sets the entry point of the kernel to the start label in your assembly code.

GRUB Configuration (grub.cfg): This configuration is for the GRUB bootloader. It specifies a menu entry named "buffalo" that loads your kernel (/boot/kernel.bin) using the Multiboot 2 protocol.

Makefile: This is a build script for your kernel. It finds all assembly source files, compiles them into object files, links them using your linker script, and then creates a bootable ISO image using grub-mkrescue

### Memory
1. Stack Memory Allocation
Initialization: In most cases, the stack is set up very early in the boot process, often in the bootloader or in the initial assembly code before handing control over to the main kernel written in C or C++.
Setting Up: The stack is typically a fixed-size area of memory. You set the stack pointer (SP or ESP register on x86 architectures) to the top of this area. The size of the stack should be chosen carefully to balance between using too much memory and risking a stack overflow.
Usage: The stack is used automatically by the CPU when calling functions (to store return addresses and local variables). You usually don't need to manually manage stack memory in your kernel code.
2. Heap Memory Allocation
Implementation: Implementing heap memory management is more involved. You need to write (or port) a memory allocator, which can handle dynamic memory requests (like malloc and free in C).
Setting Up the Heap: Choose a region of memory to be your heap. It's common to start the heap at the end of the kernel and let it grow upwards.
Allocator Algorithm: You need an algorithm to allocate and free memory blocks. Common algorithms include buddy system, slab allocator, and binary buddy system.
Considerations: Keep in mind that managing a heap requires handling fragmentation, allocation efficiency, and synchronization in a multitasking environment.
Integration in Your Kernel
To integrate these in your kernel, you'll need to modify your boot process and kernel code.
Stack: Modify your bootloader or initial assembly code to set up the stack pointer. This is often just a few lines of code.
Heap: Write or integrate a memory allocator into your kernel. This is usually done after setting up basic kernel services like memory management.


## Stack
Setting up the stack very early in the boot process, often in the bootloader or initial assembly code, is crucial for several reasons:

Function Calls and Local Variables: The stack is used for managing function calls and local variables. As soon as the control is transferred to a piece of code that might call functions or use local variables (which is almost any C or C++ code), a stack needs to be available. Without a stack, even the simplest function calls or local variable assignments would fail, leading to unpredictable behavior or a system crash.

Consistency and Control: Setting up the stack early ensures that you have a known, consistent state of the stack when your higher-level kernel code starts executing. This is important for debugging and reliability, as it removes uncertainties about the state of the system when the main kernel code begins execution.

Interrupt Handling: The CPU uses the stack to store return addresses and register values when an interrupt occurs. Since interrupts can be triggered at almost any time, including during the early stages of booting, a stack must be available to handle these interrupts properly.

Bootloader to Kernel Handoff: The transition from the bootloader to the kernel is a critical phase. The bootloader prepares the environment for the kernel, which includes setting up essential hardware and memory structures like the stack. Once the kernel starts, it assumes that these structures are already in place and operational.

Simplicity and Reliability: Setting up the stack is relatively simple compared to other initialization tasks, but its presence is vital. Doing this early avoids complex scenarios where part of the system is initialized but can't reliably call functions or handle interrupts.

Architecture Requirements: On many architectures, including x86, the stack is an integral part of the CPU's functioning for managing function calls, interrupts, and exceptions. The CPU automatically uses the stack pointer (SP or ESP) for various operations, so it must point to a valid memory area as soon as possible.