#ifndef  __Input_H__
# define __Input_H__

#include "str.h"
#include "input.h"

str Input(const char *prompt)
{
	str ret;
	ret.str_p = input(prompt, &ret.len);
	
	return ret;
}

#endif
