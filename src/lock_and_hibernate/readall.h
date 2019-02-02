#ifndef  __lock_and_hibernate_readall_H__
# define __lock_and_hibernate_readall_H__

# include <stddef.h>

/*!
 * readall read the pipe/FIFO/socket/file pointed to by fd into a string allocated on heap and returns
 * a pointer pointed to it.
 *
 * used should not be NULL and the size of the string read in (excluding the trailing '\0' ) 
 * will be writen to *used.
 */
extern char* readall(int fd, size_t *used);

#endif
