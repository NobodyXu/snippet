#ifndef  __find_first_alphanumeric_H__
# define __find_first_alphanumeric_H__

#include <stddef.h>
#include "str.h"
#include "is_alphanumeric.h"

// If nothing is found, len is returned.
size_t find_first_alphanumeric(str s)
{
	size_t i = 0;
	while (i != s.len && !is_alphanumeric((s.str_p)[i]))
		++i;
	return i;
}

#endif
