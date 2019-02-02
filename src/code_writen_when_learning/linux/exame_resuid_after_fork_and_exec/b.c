#include "a.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
        printf("argc = %d, argv[0] = %s\n", argc, argv[0]);

    print_resuid(argv[1]);

    return 0;
}
