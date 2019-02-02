#define _GNU_SOURCE
#include <stdio.h>
#include <assert.h>
#include <syscall.h>  // For syscall to call getpid
#include <signal.h>   // For SIGCHILD
#include <sys/types.h>// For getppid
#include <unistd.h>   // For getppid, sleep, exec
#include <sched.h>    // For clone
#include <stdlib.h>   // For calloc, free, exit
#include <string.h>   // For strerror
#include <errno.h>    // For EAGAIN

#define STACK_SIZE 1900
#define SLEEP_TIME 20
#define STR_HELPER(expr) #expr
#define STR(expr) STR_HELPER(expr)

void Puts(const char *str)
{
    assert(fputs(str, stderr) != EOF);
}

void Sleep(unsigned int sec)
{
    do {
	sec = sleep(sec);
    } while(sec > 0);
}

int child(void *useless)
{
    Puts("The new process is created.\n");
    // fprintf is not safe to use here.
    assert(dprintf(2, "pid = %d, ppid = %d\n", (pid_t) syscall(SYS_getpid), getppid()) > 0);
    Puts(strerror(EAGAIN));

    Puts("sleep for "  STR(SLEEP_TIME) " secs\n");
    Sleep(SLEEP_TIME);

    return 0;
}

int child2(void *useless)
{
    Puts("The new process is created.\n");
    // fprintf is not safe to use here.
    //assert(dprintf(2, "pid = %d, ppid = %d\n", (pid_t) syscall(SYS_getpid), getppid()) > 0);

    Puts("exec echo haha\n");
    assert(execl("/bin/echo", "/bin/echo", "haha", (char*) NULL) != -1);

    return 0;
}

void Clone(int (*f)(void *), void *stack_top)
{
    Puts("clone\n");
    int ret = clone(f, stack_top, CLONE_VM | CLONE_VFORK | CLONE_PARENT | SIGCHLD, NULL);
    Puts("clone returns\n");

    if (ret == -1) {
	perror("clone(child, stack, CLONE_VM | CLONE_VFORK, NULL)");
	exit(EXIT_FAILURE);

	__builtin_unreachable();
    }  else
	Puts("Child dies...\n");
}

int main(int argc, char* argv[])
{
    Puts("Allocate stack for new process\n");
    void *stack = calloc(STACK_SIZE, sizeof(char));
    void *stack_top = (void*) ((char*) stack + STACK_SIZE - 1);
    assert(fprintf(stderr, "stack = %p, stack top = %p\n", stack, stack_top) > 0);

    Clone(child, stack_top);
    Clone(child2, stack_top);

    Puts("Free the stack\n");
    free(stack);

    return 0;
}
