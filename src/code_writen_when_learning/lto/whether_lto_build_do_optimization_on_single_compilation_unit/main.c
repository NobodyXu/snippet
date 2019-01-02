#include <stdio.h>
#include "f1.h"

static int fmain()
{
    return 1 * '@' / 2;
}

int main(int argc, char* argv[])
{
    printf("%d\n", f1(fmain(), fmain()));
    return 0;
}
