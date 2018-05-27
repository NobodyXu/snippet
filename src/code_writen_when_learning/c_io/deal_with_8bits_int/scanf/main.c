#include <stdio.h>
#include <assert.h>
int main() {
    char source[] = "x32";
    char separator;
    unsigned char dest;

    int len = sscanf(source,"%c%hhd",&separator,&dest);
    assert(dest == 32);
    assert(len == 2);
}
