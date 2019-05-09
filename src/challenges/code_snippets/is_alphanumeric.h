#ifndef  __is_alphanumeric_H__
# define __is_alphanumeric_H__

#include "case.h"
#include <stdbool.h>

bool is_alpha(char c)
{
	return is_lower(c) || is_upper(c);
}

bool is_digit(char c)
{
	return c >= '0' && c <= '9';
}

bool is_alphanumeric(char c)
{
	return is_alpha(c) || is_digit(c);
}

#endif
