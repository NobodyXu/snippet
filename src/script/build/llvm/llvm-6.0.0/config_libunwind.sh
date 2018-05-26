src_dir="$PWD"

source invoke_cmake_to_configure.sh

initialize
invoke_cmake_to_configure			  \
    -DLIBUNWIND_ENABLE_ASSERTIONS=False		  \
    -DLIBUNWIND_USE_COMPILER_RT=True		  \
    -DLLVM_ENABLE_LTO=Thin			  \
    -DLLVM_PARALLEL_COMPILE_JOBS=10		  \
    -DLLVM_PARALLEL_LINK_JOBS=4			  \
    -DLLVM_CONFIG_PATH=/usr/bin/llvm-config-5.0	  \
    ${@:2:222222}
