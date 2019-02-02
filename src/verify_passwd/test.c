#include "verify_passwd.h"
#include "../getpasswd/getpasswd.h"

#include <stdio.h>

#include <assert.h>
#include <errno.h>

void Puts(const char *str)
{
    assert(puts(str) != EOF);
}

int main(int argc, char *argv[])
{
    Puts("Please enter your passwd:");

    const char *msg;

    char *passwd = NULL;
    size_t n = 0;
    ssize_t in_size = getpasswd(&passwd, &n, &msg);

    if (in_size < 0) {
	errno = -in_size;
	perror(msg);
	return 1;
    }

    int ret = verify_passwd(passwd, &msg);

    if (ret < 0) {
	errno = -ret;
	perror(msg);
	return 1;
    } else {
	printf("It is %s due to %s", ret ? "correct" : "incorrect", msg);
    }

    return 0;
}
