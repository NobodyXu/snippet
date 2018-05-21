#include <stdio.h>
#include <sys/syscall.h>
#define GET_SYSCALL_NUM(SYSCALL_NAME) __NR_ ## SYSCALL_NAME
int main() { printf("%d\n", GET_SYSCALL_NUM(stat)); }
