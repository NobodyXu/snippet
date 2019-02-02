#ifndef  __lock_and_hibernate_ASSERT_H__
#define  __lock_and_hibernate_ASSERT_H__

# include "expect.h"
# include <errno.h>

_Noreturn void assert_syscall_failure(const char *expr);

#define ASSERT_SYSCALL(EXPR)\
    if (unlikely(!(EXPR)))  \
	assert_syscall_failure(#EXPR " fails")

/*!
 * ASSERT_SYSCALL2 is intended for syscall which can set errno to EINTR.
 */
#define ASSERT_SYSCALL2(ret, call, failure_code)	\
    do {						\
	ret = call;					\
    } while ((ret == (failure_code)) && errno == EINTR);\
    if (unlikely(ret == failure_code))			\
	assert_syscall_failure(#call " != " #failure_code " fails.")

#endif
