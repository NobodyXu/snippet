#include <stdio.h>
#include <string.h>
#include <errno.h>
int main() {
    int ret = dprintf(4, "Hello, World!\n"), _errno = errno;
    printf("%d\n", ret);
    puts(strerror(_errno));
}
