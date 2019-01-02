#include <sys/syscall.h>
#include <string.h>

int main(int argc, char* argv[])
{
    int ret = syscall(__NR_write, 2, argv[1], strlen(argv[1]));
    return !(ret != -1);
}
