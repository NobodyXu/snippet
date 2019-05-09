#ifndef  __Strtol_H__
# define __Strtol_H__

#include "Assert.h"

long Strtol(const char *str, const char *err_msg)
{
    char *end;
    
    long ret = strtol(str, &end, 10);
    Assert(*str != '\0' && *end == '\0', err_msg);
    
    return ret;
}

#endif
