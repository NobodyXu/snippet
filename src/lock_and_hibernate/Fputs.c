#include "Fputs.h"
#include "ASSERT.h"

void Fputs(const char *str, FILE *stream)
{
    ASSERT_SYSCALL(fputs(str, stream) != EOF);
    ASSERT_SYSCALL(fflush(stream) != EOF);
}
