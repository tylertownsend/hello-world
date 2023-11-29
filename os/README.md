# Development Environment
Development will use a docker image to build the code and qemu to run the image.
## Setup
This guide provides instructions on how to install QEMU and set up your environment to run a bootloader for your operating system development.

### Installing QEMU

QEMU is a generic and open-source machine emulator and virtualizer. Follow these instructions to install QEMU on your system:

#### For Ubuntu/Debian-based Linux Distributions:

Run the following command in your terminal:

```bash
sudo apt-get update
sudo apt-get install qemu
```

### Compile Bootloader
```bash
nasm -f bin -o bootloader.bin bootloader.asm
```

### Create Bootable CD-ROM Image
```
mkisofs -no-emul-boot -boot-load-size 4 -boot-info-table \
-o bootable.iso -b bootloader.bin .
```

### Running QEMU
```bash
qemu-system-x86_64 -cdrom bootable.iso
```
Observation: When QEMU runs, it will execute the bootloader code. You should see the results of your bootloader code on the QEMU screen. If you've set up any output or status messages in your bootloader, they should appear here.

Debugging: If the bootloader doesn't work as expected, you may need to debug it. One common method is to use QEMU's built-in monitor. You can access the monitor by pressing Ctrl-Alt-2 when running QEMU. To return to the emulation, press Ctrl-Alt-1.

Iterating: Development often requires an iterative process. Make changes to your bootloader code, recompile, recreate the bootable image, and test again with QEMU.

## Docker

Run `buildenv/setup.sh`
