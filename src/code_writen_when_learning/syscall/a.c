#include <unistd.h>
#include <sys/syscall.h>

int main() 
{ 
    syscall(__NR_dup, 0);
    syscall(__NR_exit, 0); 
}
