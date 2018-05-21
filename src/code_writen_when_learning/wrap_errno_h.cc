namespace c::posix {
#include <stdio.h>
#include <errno.h>
error_t get_errno() noexcept { return errno; }
#undef errno
}
int main() {
    c::posix::printf("Hello, World!\n");
    int errno{c::posix::get_errno()};
    c::posix::printf("errno: %d\n", errno);
}
