#include "readall.h"
#include "spawn.h"
#include "Fputs.h"
#include "ASSERT.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int in_fd;
    char *output;
    size_t n;

    spawn("/bin/ls", false, true, &in_fd);

    output = readall(in_fd, &n);

    Fputs(output, stdout);
    ASSERT_SYSCALL(printf("Writen %ld bytes in total", n) > 0);

    free(output);
    return 0;
}
