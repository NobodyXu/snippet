#ifndef  __getpasswd_getpasswd_H__
# define __getpasswd_getpasswd_H__

# include <sys/types.h>

/*!
 * getpasswd get password from stdin without echoing them using getline and termios.h.
 *
 * passwd, n has to point to a valid memory.
 *
 * If *passwd == NULL, then *n has to be 0.
 * Otherwise, *passwd has to point to a malloc-allocated string and *n equals the size of it.
 *
 * After the call, the user is required to free(*passwd).
 *
 * It returns number of characters read (excluding '\0') if succeeded,
 * or a negative value (-errno) with *msg set to an error string.
 */
extern ssize_t getpasswd(char **passwd, size_t *n, const char **msg);

#endif
