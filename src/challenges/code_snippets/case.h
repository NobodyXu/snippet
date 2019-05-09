#ifndef  __case_H__
# define __case_H__

#include <stdbool.h>
#include "str.h"

bool is_lower(char c)
{
	return c >= 'a' && c <= 'z';
}

bool is_upper(char c)
{
	return c >= 'A' && c <= 'Z';
}

void to_lower_impl(str *s)
{
	size_t i = 0;
	while (i != s->len)
		if (is_upper(s->str_p[i]))
			s->str_p[i] -= ('A' - 'a');
}

void to_upper_impl(str *s)
{
	size_t i = 0;
	while (i != s->len)
		if (is_upper(s->str_p[i]))
			s->str_p[i] -= ('a' - 'A');
}

// Return s for chaining
str to_lower(str s)
{
	to_lower_impl(&s);
	return s;
}

// Return s for chaining
str to_upper(str s)
{
	to_upper_impl(&s);
	return s;
}

#endif
