#include "spawn.h"
#include "Fputs.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/wait.h>

#include <unistd.h> // For sleep
#include <assert.h>

#include "ASSERT.h"

void Puts(const char *str)
{
    ASSERT_SYSCALL(puts(str) != EOF);
}

void Wait()
{
    int status;
    ASSERT_SYSCALL(wait(&status));

    if (!WIFEXITED(status)) {
	Fputs("Subprocess was killed by signal.\n", stderr);
	exit(1);
    }

    if (WEXITSTATUS(status)) {
	ASSERT_SYSCALL(fprintf(stderr, "Subprocess failed with %d.\n", status) > 0);
	exit(1);
    }
}

void Sleep(unsigned int sec)
{
    do {
	sec = sleep(sec);
    } while (sec > 0);
}

int main(int argc, char *argv[])
{
    int array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    array[0] = 2;
    array[3] = 3;
    array[9] = argc;
    int i = 0;

    spawn("/bin/ls", true, false, NULL);
    Wait();
    spawn("/bin/ls", false, false, NULL);
    Wait();
    spawn("/bin/ls", false, true, NULL);
    Sleep(1);

    int in_fd;
    spawn("/bin/ls", false, false, &in_fd);
    FILE *pipe;
    ASSERT_SYSCALL((pipe = fdopen(in_fd, "r")) != NULL);

    int c;
    for (c = getc(pipe); c != EOF; c = getc(pipe))
	ASSERT_SYSCALL(putchar(c));
    assert(ferror(pipe) == 0);
    ASSERT_SYSCALL(fclose(pipe) == 0);

    Wait();

    for (; i != 10; ++i)
	printf("%d", array[i]);

    puts("");

    // spawn("/bin/haha", false, false, NULL);
    // The above line clearly cause the program to print error message
    // about the executable is not found and the parent exits.

    return 0;
}
