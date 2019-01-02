// compile with clang++-7 -std=c++17 -Wl,--as-needed -nodefaultlibs -fno-exceptions -fno-rtti -lc %
#include <cstdio>
#include <cstdlib>
#include <vector>

void operator delete(void *ptr) noexcept
{
    free(ptr);
}

int main(int argc, char* argv[]) {
    printf("Hello, world!\n");
    std::vector<int> v;
    return 0;
}
