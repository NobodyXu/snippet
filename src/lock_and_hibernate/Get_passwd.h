#ifndef  __lock_and_hibernate_Get_passwd_H__
# define __lock_and_hibernate_Get_passwd_H__

/*!
 * Get_passwd_by_gui returns a string.
 *
 * It returns a pointer to string allocated on heap on success and NULL on failure 
 * (also message printed on stderr).
 */
extern char* Get_passwd_by_gui();

/*!
 * Get_passwd_by_gui returns a string.
 *
 * It returns a pointer to string allocated on heap on success.
 * On failure, it prints to stderr and call exit.
 */
extern char* Get_passwd_by_console();

#endif
