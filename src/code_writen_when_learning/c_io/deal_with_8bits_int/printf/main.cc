#include <stdio.h>
#include <assert.h>
int main() {
    unsigned char source = 32;
    char dest[3];

    int len = sprintf(dest, "%hhd", source);
    assert(len == 2);
    assert(dest[0] == '3');
    assert(dest[1] == '2');
    assert(dest[2] == '\0');
}
