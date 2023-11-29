# Makefile for creating a floppy disk bootloader and testing it with QEMU

# The name of the bootloader source file
BOOTLOADER_SRC := bootloader.asm
# The name of the binary bootloader file
BOOTLOADER_BIN := bootloader.bin
# The name of the floppy disk image
FLOPPY_IMG := floppy.img

# The default 'make' target
all: $(FLOPPY_IMG)

# How to build the bootloader binary
$(BOOTLOADER_BIN): $(BOOTLOADER_SRC)
	nasm -f bin -o $@ $<

# How to create a floppy disk image
$(FLOPPY_IMG): $(BOOTLOADER_BIN)
	dd if=/dev/zero of=$@ bs=512 count=2880
	dd if=$(BOOTLOADER_BIN) of=$@ conv=notrunc

# How to run QEMU with the floppy disk image
qemu: $(FLOPPY_IMG)
	qemu-system-x86_64 -drive file=$(FLOPPY_IMG),format=raw,if=floppy

# This target cleans up the compiled files
clean:
	rm -f $(BOOTLOADER_BIN) $(FLOPPY_IMG)

# Declare 'clean' as a phony target to ensure it always runs when called
.PHONY: all qemu clean
