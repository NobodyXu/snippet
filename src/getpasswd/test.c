#include "getpasswd.h"

#include <stdio.h>
#include <stdlib.h>

#include <assert.h>
#include <errno.h>

void Puts(const char *str)
{
    assert(puts(str) != EOF);
}

int main(int argc, char *argv[])
{
    char *passwd = NULL;
    size_t n = 0;
    const char *msg;

    Puts("Please enter the passwd:");

    ssize_t in_cnt = getpasswd(&passwd, &n, &msg);
    if (in_cnt < 0) {
	errno = -in_cnt;
	perror(msg);
	return 1;
    }

    Puts(passwd);
    free(passwd);

    return 0;
}
