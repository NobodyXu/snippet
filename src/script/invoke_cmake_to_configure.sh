#!/bin/sh
CC=clang-5.0
CXX=clang++-5.0

C_FLAGS="-Ofast -pipe -flto=thin"
CXX_FLAGS="$C_FLAGS -fstrict-enums -fstrict-vtable-pointers"

build_dir="$PWD/$1"

initialize() {
    mkdir $build_dir && cd $build_dir
}
invoke_cmake_to_configure() {
    exec cmake -DCMAKE_BUILD_TYPE=Release		    \
       	       -DCMAKE_C_COMPILER="$CC"			    \
      	       -DCMAKE_C_FLAGS="$C_FLAGS"		    \
      	       -DCMAKE_CXX_COMPILER="$CXX"		    \
      	       -DCMAKE_CXX_FLAGS="$CXX_FLAGS"		    \
	       "$@"					    \
	       -G "Ninja" $src_dir
}
