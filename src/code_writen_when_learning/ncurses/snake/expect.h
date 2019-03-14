#ifndef  likely
# define likely(EXPR) __builtin_expect((EXPR), true)
#endif

#ifndef  unlikely
# define unlikely(EXPR) __builtin_expect((EXPR), false)
#endif
