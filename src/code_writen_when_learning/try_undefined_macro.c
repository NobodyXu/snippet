#include <stdio.h>
int main() {
    #include "try_undefined_macro.h"
    #define AAA  1
    #include "try_undefined_macro.h"
}
