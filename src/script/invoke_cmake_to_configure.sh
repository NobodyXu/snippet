#!/bin/sh
C_COMPILE_FLAGS="-Ofast -pipe -flto=thin"
CXX_COMPILE_FLAGS="$C_COMCPILE_FLAGS -fstrict-enums -fstrict-vtable-pointers"

build_dir="$PWD/$1"

initialize() {
    mkdir $build_dir && cd $build_dir
}
invoke_cmake_to_configure() {
    exec cmake -DCMAKE_BUILD_TYPE=Release		    \
       	       -DCMAKE_C_COMPILER=clang-5.0		    \
      	       -DCMAKE_C_FLAGS="$C_FAMILY_COMPILE_FLAGS"    \
      	       -DCMAKE_CXX_COMPILER=clang++-5.0		    \
      	       -DCMAKE_CXX_FLAGS="$C_FAMILY_COMPILE_FLAGS"  \
	       "$@"					    \
	       -G "Ninja" $src_dir
}
