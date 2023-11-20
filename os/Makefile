# Makefile for building a simple bootloader and testing with QEMU

# Compiler and QEMU settings
ASM=nasm
QEMU=qemu-system-x86_64

# Bootloader and image file names
BOOTLOADER_SRC=bootloader.asm
BOOTLOADER_BIN=bootloader.bin
FLOPPY_IMG=floppy.img

# Phony targets for make
.PHONY: all clean run

# Default target
all: $(FLOPPY_IMG)

# How to build the bootloader binary
$(BOOTLOADER_BIN): $(BOOTLOADER_SRC)
	$(ASM) -f bin -o $(BOOTLOADER_BIN) $(BOOTLOADER_SRC)

# How to create the floppy image and write the bootloader to it
$(FLOPPY_IMG): $(BOOTLOADER_BIN)
	dd if=/dev/zero of=$(FLOPPY_IMG) bs=1024 count=1440
	dd if=$(BOOTLOADER_BIN) of=$(FLOPPY_IMG) seek=0 count=1 conv=notrunc

# Target to run the image in QEMU
run: $(FLOPPY_IMG)
	$(QEMU) -fda $(FLOPPY_IMG)

# Clean the workspace
clean:
	rm -f $(BOOTLOADER_BIN) $(FLOPPY_IMG)
