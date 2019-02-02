#ifndef  __verify_passwd_verify_passwd_H__
# define __verify_passwd_verify_passwd_H__

/*!
 * verify_passwd checks whether the passwd equals the password of the real user of the process.
 *
 * passwd and msg has to point to a valid memory.
 *
 * verify_passwd returns	1	  if the passwd is the password;
 *				0	  if not;
 *			 -errno(negative) if there is an error.
 *
 * If 1 is returned and *msg != NULL, then it is a special case that the user can login and *msg will
 *     point to an explanation string.
 * If 0 is returned and *msg != NULL, it will point to an string explaning why it failed.
 * If a negative value is returned, *msg will pointed to the name of the function that fails.
 *
 * In order to use this function, "-lcrypt" need to pass to the compiler during link time
 *
 * This function is not reentrantable.
 */
extern int verify_passwd(const char *passwd, const char **msg);

#endif
