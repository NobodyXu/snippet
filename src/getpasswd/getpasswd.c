#define _POSIX_C_SOURCE 200809L

#include "getpasswd.h"

#include <termios.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#include <errno.h>
#include <stdbool.h>

#define likely(EXPR) __builtin_expect((EXPR), true)
#define unlikely(EXPR) __builtin_expect((EXPR), false)

#define RETURN(EXPR)\
    ret = (EXPR);   \
    return ret

#define ASSERT(EXPR, func)	\
    do {			\
        if (unlikely(!(EXPR))) {\
	    *msg = func;	\
	    RETURN(-errno);	\
	}			\
    } while (false)

static void erase_end_of_line(char *p);

/*!
 * getpasswd is adapted from https://stackoverflow.com/questions/1786532/c-command-line-password-input.
 */
extern ssize_t getpasswd(char **password, size_t *n, const char **msg)
{
    ssize_t ret;
    struct termios terminal;

    //get settings of the actual terminal
    ASSERT((tcgetattr(STDIN_FILENO, &terminal) == 0), "tcgetattr");

    // do not echo the characters
    terminal.c_lflag &= ~(ECHO);
    ASSERT((tcsetattr(STDIN_FILENO, TCSANOW, &terminal) == 0), 
	    "tcsetattr -- to turn off echo");
 
    ret = getline(password, n, stdin);
    if (ret == -1) {
	free(*password);
	*msg = "getline -- to read passwd";
	RETURN(-errno);
    }
    erase_end_of_line((*password) + (ret - 1));

    // do echo the characters
    terminal.c_lflag |= ECHO;
    ASSERT((tcsetattr(STDIN_FILENO, TCSANOW, &terminal) == 0), 
	    "tcsetattr -- to turn on echo");

    return ret - 1;
}

/*!
 * erase_end_of_line will assign '\0' to *p if it is '\n'.
 */
static inline void erase_end_of_line(char *p)
{
    if (*p == '\n')
	*p = '\0';
}
