#ifndef  __snake_Assert_HPP__
# define __snake_Assert_HPP__

[[noreturn]] void Assert_failure(const char *fmt, ...) noexcept;
inline void Assert_internal(bool val, const char *str) noexcept;

/*!
 * Assert should be treat as a function call
 */
# define Assert(cond)				    \
    Assert_internal((cond), "Assertion " #cond " fails.")

# define Assert_curses(cond) Assert((cond) != ERR)

#endif
