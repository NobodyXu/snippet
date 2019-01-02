#include <sys/syscall.h>

_Noreturn void _start()
{
    register int syscall_num asm ("rax") = __NR_exit;
    register int exit_code   asm ("rdi") = 0;

    // The actual syscall to exit
    asm volatile ("syscall # Doing syscall"
	    : /* no output Operands */
	    : "r" (syscall_num), "r" (exit_code));

    __builtin_unreachable();
}
