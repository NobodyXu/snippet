#!/bin/bash

src_dir="$PWD/llvm-6.0.0"
source invoke_cmake_to_configure.sh

initialize
invoke_cmake_to_configure
    -DCLANG_DEFAULT_CXX_STDLIB="libc++"			\
    -DCLANG_DEFAULT_RTLIB="compiler-rt"			\
    -DLIBCXXABI_ENABLE_ASSERTIONS=True			\
    -DLIBCXXABI_USE_COMPILER_RT=True			\
    -DLIBCXX_BENCHMARK_NATIVE_STDLIB="libstdc++"	\
    -DLIBCXX_USE_COMPILER_RT=True			\
    -DLLVM_ENABLE_ASSERTIONS=True			\
    -DLLVM_ENABLE_CXX1Y=True				\
    -DLLVM_ENABLE_CXX1Z=True				\
    -DLLVM_ENABLE_LIBCXX=True				\
    -DLLVM_ENABLE_LLD=True				\
    -DLLVM_ENABLE_LTO="Thin"				\
    -DLLVM_INSTALL_BINUTILS_SYMLINKS=True		\
    -DLLVM_INSTALL_UTILS=True				\
    -DLLVM_PARALLEL_COMPILE_JOBS="10"			\
    -DLLVM_PARALLEL_LINK_JOBS="3"			\
    -DCPACK_BINARY_DEB=True				\
    -G "Ninja"
