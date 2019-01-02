#include <ucontext.h>
#include <cstdio>
#include <cassert>
#include <cstdlib>

auto f4()
{
    static int cnt = 0;

    ucontext_t uc;
    assert(getcontext(&uc) == 0);

    ++cnt;
    assert(cnt > 0);
    if (cnt != 1) {
	std::printf("AA\n");
	std::exit(0);
    }

    return uc;
}

int main(int argc, char* argv[])
{
    auto context = f4();
    assert(setcontext(&context) == 0);

    return 1;
}
