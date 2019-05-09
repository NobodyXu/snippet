#ifndef  __input_long_H__
# define __input_long_H__

#include "input.h"
#include "Strtol.h"

long get_height(const char *prompt, const char *err_msg)
{
    char *s = input(prompt, NULL);
    long ret = Strtol(s, err_msg);
    
    free(s);
    return ret;
}

#endif
