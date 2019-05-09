#ifndef  __ASSERT_H__
# define __ASSERT_H__

#include <stdio.h>
#include <stdlib.h>

void Assert(bool expr, const char *err_msg) {
	if (!(expr)) {
    	fputs(err_msg, stderr);
		exit(1);
	}
}

#endif
