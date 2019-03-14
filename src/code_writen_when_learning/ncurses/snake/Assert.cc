#define _POSIX_C_SOURCE 200809L

#include <ncurses.h>

#include "Assert.hpp"

#include <cstdarg>   // For variable args
#include <cstdlib>   // std::exit
#include <stdio.h>   // std::vdprintf
#include <sysexits.h>// For EX_*

inline void Assert_internal(bool val, const char *str) noexcept
{
    if (__builtin_expect(!(val), false))
	Assert_failure("%s\n", str);
}

[[noreturn]] void Assert_failure(const char *fmt, ...) noexcept
{
    std::va_list ap;
    int size = 0;
    int ret = EX_SOFTWARE;

    if (endwin() == ERR) {
	ret = EX_UNAVAILABLE;
	goto out;
    }

    va_start(ap, fmt);
    size = vdprintf(2, fmt, ap);
    va_end(ap);

    if (size <= 0)
	ret = EX_IOERR;

out:
    std::exit(ret);
}
