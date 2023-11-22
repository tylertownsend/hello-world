# Makefile for creating a CD-ROM bootloader and testing it with QEMU

# The name of the bootloader source file
BOOTLOADER_SRC := bootloader.asm
# The name of the binary bootloader file
BOOTLOADER_BIN := bootloader.bin
# The name of the CD-ROM image
CDROM_IMG := bootable.iso

# The default 'make' target
all: $(CDROM_IMG)

# How to build the bootloader binary
$(BOOTLOADER_BIN): $(BOOTLOADER_SRC)
	nasm -f bin -o $@ $<

# How to create a CD-ROM ISO image
$(CDROM_IMG): $(BOOTLOADER_BIN)
	mkisofs -no-emul-boot -boot-load-size 4 -boot-info-table \
	-o $@ -b $< .

# How to run QEMU with the CD-ROM image
qemu: $(CDROM_IMG)
	qemu-system-x86_64 -cdrom $<

# This target cleans up the compiled files
clean:
	rm -f $(BOOTLOADER_BIN) $(CDROM_IMG)

# Declare 'clean' as a phony target to ensure it always runs when called
.PHONY: all qemu clean
