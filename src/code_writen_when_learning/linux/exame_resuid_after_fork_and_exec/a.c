#include "a.h"

#include <sys/types.h>
#include <sys/wait.h>

#include <stdlib.h>
#include <stdbool.h>

#define assert_syscall(EXPR)		      \
    do {				      \
	if (__builtin_expect(!(EXPR), false)) {\
		perror(#EXPR);		      \
		exit(1);		      \
	}				      \
    } while(0)

_Noreturn void Execl(const char *exec, const char *arg)
{
    assert_syscall(execl(exec, exec, arg, (char*) NULL) != -1);
    __builtin_unreachable();
}

void try_fork_and_exec_nosuid_file()
{
    int ret = fork();

    assert_syscall(ret/* of fork */ != -1);

    if (ret == 0) {
	print_resuid("In the child process: ");
	Execl("./b.out", "After exec file ./b.out: ");
    } else
	assert_syscall(wait(NULL) == ret);
}

_Noreturn void try_exec_itself(const char *name)
{
    Execl(name, "After exec itself (which should be a suid executable): ");
}

int main(int argc, char* argv[])
{
    if (argc == 1) {
        print_resuid("In the parent: ");
        try_fork_and_exec_nosuid_file();
	try_exec_itself(argv[0]);
    } else {
	assert(argc == 2);
	print_resuid(argv[1]);
	return 0;
    }

    __builtin_unreachable();
}
