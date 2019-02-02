#define _GNU_SOURCE   // For setresuid, clone, pipe2

#include "spawn.h"
#include "ASSERT.h"
#include "Fputs.h"

#include <sched.h>

#include <sys/types.h>// For exec
#include <fcntl.h>    // For pipe2
#include <unistd.h>   // For exec, pipe, close, dup2, read
#include <stdlib.h>   // For calloc and free
#include <errno.h>

struct arguments
{
    const char *path;
    bool privileged;
    // The fd returned by pipe
    int in_fd; // This will be automatically closed on exec
    int out_fd;// This will be dupped and automatically closed on exec
    int ret;	     // Indicate whether cleanup_and_exec success or not
};

static int cleanup_and_exec(void*);
static void getPipe(struct arguments*);

extern pid_t spawn(const char *path, bool privileged, bool shares_parent, int *in_fd)
{
    // Put args into a struct so that it can be passed through clone
    struct arguments args = {path, privileged, -1, -1, 0};

    // Set up flags for clone
    // CLONE_VFORK is set so that when clone returns, the process either success exec or exited on error.
    // CLONE_VM is set so that the memory is not copied.
    int flags = CLONE_VFORK | CLONE_VM;
    if (shares_parent)
	// Make the new process to have the same parent as this process 
	// so that when the process exec, the new process won't become zombies.
	flags |= CLONE_PARENT;

    void *stack;
    void *stack_top;
    ASSERT_SYSCALL((stack = calloc(3000, sizeof(char))) != NULL);
    stack_top = stack + 3000 - 1;

    int ret;// Ret code of syscall

    // Open the pipe if asked
    if (in_fd)
	getPipe(&args);

    ret = clone(cleanup_and_exec, stack_top, flags, (void*) &args);

    // Since either the new process dies or it exec and has a new stack allocated,
    // the stack can be freed.
    free(stack);

    if (unlikely(ret == -1))
	assert_syscall_failure("clone(cleanup_and_exec, stack, flags, (void*) args)");

    if (unlikely(args.ret == 1)) {
	Fputs("Child process fails to clean up and exec", stderr);
	exit(1);
    }

    if (in_fd) {
        ASSERT_SYSCALL(close(args.out_fd) != -1);
	*in_fd = args.in_fd;
    }

    return ret;
}

static void getPipe(struct arguments *args)
{
    int fd[2];
    ASSERT_SYSCALL(pipe2(fd, O_CLOEXEC) != -1);

    args->in_fd = fd[0];
    args->out_fd = fd[1];
}

static int cleanup_and_exec(void *args)
{
    struct arguments *args_p = (struct arguments*) args;

    if (!args_p->privileged) {
	if(unlikely(setresuid(-1, getuid(), getuid()) != 0)) {
	    args_p->ret = 1;
	    assert_syscall_failure("setresuid(-1, getuid(), getuid()) == 0 fails");
	}
    }

    if (args_p->out_fd != -1) {
	if (unlikely(dup2(args_p->out_fd, 1) == -1)) {
	    args_p->ret = 1;
	    assert_syscall_failure("dup2(args_p->out_fd, 1) != -1 fails");
	}
    }

    if (unlikely(execl(args_p->path, args_p->path, (char*) NULL) == -1)) {
	args_p->ret = 1;
	assert_syscall_failure("execl(args_p->path, args_p->path, (char*) NULL) != -1 fails");
    }

    __builtin_unreachable();
}
