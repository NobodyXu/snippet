#include <unistd.h>
#include <stdio.h>

#include <errno.h>
#include <sys/types.h>

int main() 
{
    int ret = fork();

    if (ret == 0) {
	printf("pid = %d, ppid = %d\n", getpid(), getppid());
	sleep(3);
	puts("Exiting\n");
    } else if (ret > 0)
	ret = 0;

    return ret;
}
