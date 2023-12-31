kernel_c_source_files := $(shell find src/kernel -name *.cpp)
kernel_c_object_files := $(patsubst src/kernel/%.cpp, build/kernel/%.o, $(kernel_c_source_files))

x86_64_c_source_files := $(shell find src/x86_64 -name *.cpp)
x86_64_c_object_files := $(patsubst src/x86_64/%.cpp, build/x86_64/%.o, $(x86_64_c_source_files))

x86_64_asm_source_files := $(shell find src/x86_64 -name *.asm)
x86_64_asm_object_files := $(patsubst src/x86_64/%.asm, build/x86_64/%.o, $(x86_64_asm_source_files))


# combine x86_64 object files
x86_64_object_files := $(x86_64_asm_object_files) $(x86_64_c_object_files)


# build c files
$(kernel_c_object_files): build/kernel/%.o : src/kernel/%.cpp
	mkdir -p $(dir $@) && \
	g++ --std=c++20 -c -I include -ffreestanding $(patsubst build/kernel/%.o, src/kernel/%.cpp, $@) -o $@

# g++ = x86_64-elf-g++
$(x86_64_c_object_files): build/x86_64/%.o : src/x86_64/%.cpp
	mkdir -p $(dir $@) && \
	g++ --std=c++20 -c -I include -ffreestanding $(patsubst build/x86_64/%.o, src/x86_64/%.cpp, $@) -o $@

# build assembly files
$(x86_64_asm_object_files): build/x86_64/%.o : src/x86_64/%.asm
	mkdir -p $(dir $@) && \
	nasm -f elf64 $(patsubst build/x86_64/%.o, src/x86_64/%.asm, $@) -o $@

.PHONY: build-x86_64
build-x86_64: $(kernel_c_object_files) $(x86_64_object_files)
	@echo "Building x86_64 target..."
	mkdir -p dist/x86_64 && \
	ld -n -o dist/x86_64/kernel.bin -T targets/x86_64/linker.ld $(kernel_c_object_files) $(x86_64_object_files) && \
	cp dist/x86_64/kernel.bin targets/x86_64/iso/boot/kernel.bin && \
	grub-mkrescue /usr/lib/grub/i386-pc -o dist/x86_64/kernel.iso targets/x86_64/iso
	@echo "Build complete."

qemu:
	qemu-system-x86_64 -cdrom dist/x86_64/kernel.iso 