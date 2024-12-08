FILES = ./build/kernel.asm.o

all: ./bin/boot.bin $(FILES)
	dd if=./bin/boot.bin >> ./bin/os.bin

./bin/boot.bin: ./src/boot/boot.asm
	nasm -f bin ./src/boot/boot.asm -o ./bin/boot.bin
./build/kernel.asm.o: ./src/kernel.asm
	nasm -f elf32 -g ./src/kernel.asm -o ./build/kernel.asm.o

clean:
	rm -f ./bin/boot.bin

qemu:
	qemu-system-x86_64 -cdrom dist/x86_64/kernel.iso 
