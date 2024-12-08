#/bin/bash
#
# This script will install the necessary packages to build a cross-compiler

# Globals
export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf 
export PATH="$PREFIX/bin:$PATH" 

function download_source {
  if [ ! -d $HOME/src ]; then
    mkdir $HOME/src
  fi

  ## early return for now since we haven't implemented this part yet
  return
}

function install_gcc {
  cd $HOME/src

  # The $PREFIX/bin dir _must_ be in the PATH. We did that above.
  which -- $TARGET-as || echo $TARGET-as is not in the PATH

  gcc_ver="gcc-10.2.0"
  mkdir build-gcc
  cd build-gcc
  ../$gcc_ver/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
  make all-gcc
  make all-target-libgcc
  make install-gcc
  make install-target-libgcc
}
#

function install_binutils {
  cd $HOME/src

  ## 
  ## Assume we put the bin utils target in the $HOME/src directory
  ##

  ## Makes the bin utils target
  BINUTILS_VER=binutils-2.35
  mkdir build-binutils
  cd build-binutils
  ../$BINUTILS_VER/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
  make
  make install
}

function install_packages {
  download_source
  # install_binutils
  install_gcc
}

install_packages
