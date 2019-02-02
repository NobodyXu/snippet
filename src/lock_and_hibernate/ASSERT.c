#define _POSIX_C_SOURCE 200809L// dprintf
#include "ASSERT.h"

#include <stdio.h> // dprintf
#include <string.h>// strerror
#include <errno.h> // errno
#include <stdlib.h>// exit

_Noreturn void assert_syscall_failure(const char *expr)
{
    // Attempt to print error message
    // If dprintf fails (should be rare), then there is nothing else to do except exit.
    dprintf(2, "%s: %s\n", expr, strerror(errno));
    exit(1);
}
