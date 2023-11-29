sudo docker build buildenv/ -t os-test
sudo docker run --rm -it -v $(pwd):/root/env os-test make build-x86_64
# emulate qemu
qemu-system-x86_64 -cdrom dist/x86_64/kernel.iso 
