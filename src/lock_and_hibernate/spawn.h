#ifndef  __lock_and_hibernate_spawn_H__
#define  __lock_and_hibernate_spawn_H__

# include <stddef.h>
# include <stdbool.h>
# include <sys/types.h>

/*!
 * spawn does vfork + change privilege/Replace stdout with a pipe + execl adn returns the pid of the new 
 * process
 *
 * path	         is the path to the executable.
 * privileged    decides whether the new process should be privileged or not
 * shares_parent decides whether the new process shares the same parent as this process
 * 
 * If in_fd != NULL, then the output of the new process will be redirected to a pipe
 * and *in_fd will point to the read fd of the pipe.
 */
extern pid_t spawn(const char *path, bool privileged, bool shares_parent, int *in_fd);
#endif
