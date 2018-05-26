src_dir="$PWD"

source invoke_cmake_to_configure.sh

initialize
invoke_cmake_to_configure			\
    -DLLVM_CONFIG_PATH=/usr/bin/llvm-config-5.0 \
    -DSANITIZER_USE_COMPILER_RT=True		\
    ${@:2:222222}
