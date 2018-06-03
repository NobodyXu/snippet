#ifndef likely
# define likely(x) builtin_expect(!!(x), true)
#endif
#ifndef unlikely
# define unlikely(x) builtin_expect(!!(x), false)
#endif
