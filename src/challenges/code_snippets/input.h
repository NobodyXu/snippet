#ifndef  __input_H__
# define __input_H__

#include <stdio.h>
#include <assert.h>

char* input(const char *prompt, size_t *size)
{
	char *buffer = NULL;
	size_t n = 0;
	ssize_t ret;

	assert(printf("%s", prompt) > 0);
	assert((ret = getline(&buffer, &n, stdin)) != -1);
	
	if (buffer[ret - 1] == '\n')
		buffer[--ret] = '\0';
	
	if (size != NULL)
		*size = ret;
	
	return buffer;
}

#endif
