#define _POSIX_C_SOURCE 200809L

#include "readall.h"
#include "ASSERT.h"

#include <stdio.h>  // For fdopen, fread
#include <stdlib.h> // For calloc, realloc
#include <stddef.h> // For size_t

static char* Calloc(size_t nmemb)
{
    char *ret;
    ASSERT_SYSCALL(ret = (char*) calloc(nmemb, sizeof(char)));
    return ret;
}

static char* Realloc(char *ptr, size_t size)
{
    char *ret;
    ASSERT_SYSCALL(ret = (char*) realloc((void*) ptr, size));
    return ret;
}

extern char* readall(int fd, size_t *used)
{
    FILE *pipe;
    char *buffer = Calloc(200);
    size_t n = 200;
    *used = 0;
    size_t ret;

    ASSERT_SYSCALL(pipe = fdopen(fd, "r"));

    while ((ret = fread(buffer + *used, sizeof(char), n - *used, pipe))) {
	(*used) += ret;

	if (unlikely(*used == n)) {
	    n *= 1.5;
	    buffer = Realloc(buffer, n);
	}
    }

    ASSERT_SYSCALL(ferror(pipe) == 0);
    ASSERT_SYSCALL(fclose(pipe) == 0);

    buffer[*used] = '\0';

    return buffer;
}
