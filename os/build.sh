#/bin/bash

## Globals
export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH" 

# script
make all
