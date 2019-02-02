#include "verify_passwd.h"

#define _XOPEN_SOURCE// For crypt
#include <unistd.h>

#include <stdbool.h>

/*
 * For accessing 
 *     /etc/passwd
 *     /etc/shadow
 */
#include <sys/types.h>
#include <pwd.h>
#include <shadow.h>

#include <string.h> // For strcmp, memcpy
#include <strings.h>// For rindex
#include <stdlib.h> // For calloc, free
#include <errno.h>

#define likely(EXPR) __builtin_expect((EXPR), true)
#define unlikely(EXPR) __builtin_expect((EXPR), false)

#define RETURN(EXPR)\
    ret = (EXPR);   \
    return ret

#define ASSERT(EXPR, name)	\
    do {			\
        if (unlikely(!(EXPR))) {\
	    *msg = name;	\
	    RETURN(-errno);	\
	}			\
    } while (false)

#define handle_call(EXPR)\
    ret = (EXPR);	 \
    if (ret  < 2)	 \
	return ret

/*
 * Interal API specification 1:
 * 
 *     static int f(..., const char **msg)
 *
 * Returns negative value to indicate operation	    failure;
 *		  0	  to indicate authorization failure;
 *		  1	  to indicate authorization success;
 *		  2	  to proceed (except the last function to be called).
 *
 * *msg can be set whenever needed.
 */

/*
 * Internal API specification 2:
 *
 *     static bool predicate(...)
 *
 * Returns boolean value to indicate whether condition is true or false.
 */

/*
 * verify_passwd depends on the 2 functions below
 */
static int try_passwd(const char *key, char **username, const char **msg);
static int try_shadow(const char *key, const char *username, const char **msg);

extern int verify_passwd(const char *key, const char **msg)
{
    int ret;
    char *username;

    handle_call(try_passwd(key, &username, msg));

    RETURN(try_shadow(key, username, msg));
}

/*!
 * try_passwd tries to get the passwd by using getpwuid from libc.
 *
 * If the passwd field is 'x', it will return 2 and set *username to point to the user name string;
 * otherwise, it will compare and return false (not match) and true (match).
 */
static int try_passwd(const char *key, char **username, const char **msg)
{
    int ret;
    struct passwd *pwdp;

    ASSERT((pwdp = getpwuid(getuid())) != NULL, "getpwuid");

    if (likely(pwdp->pw_passwd[0] == 'x')) {// Modern system usually don't store passwd in plain text
	*username = pwdp->pw_name;
	ret = 2;
    } else {
	ret = (strcmp(pwdp->pw_passwd, key) == 0);
    }

    return ret;
}

/*
 * try_shadow depends on the 2 functions below
 */
static int check_shadow_record_integrity(const char *spwd, const char **msg);
static int make_salt(char **salt, const char *beg_of_salt, size_t len_of_salt, const char **msg);

/*!
 * try_shadow tries to use getspnam to get the hashed passwd.
 *
 * It will first examine them using check_shadow_record_integrity to see whether they anre intergral.
 * Then it will use crypt from libc to hash that and compare with the recorded hashed passwd.
 */
static int try_shadow(const char *key, const char *username, const char **msg)
{
    int ret;
    struct spwd *spwdp;

    ASSERT((spwdp = getspnam(username)) != NULL, "getspnam");

    if (spwdp->sp_pwdp[0] == '\0') {
	if (key[0] == '\0') {
	    *msg = "Blank passwd";
	    return 1;
	} else {
	    return 0;
	}
    }

    handle_call(check_shadow_record_integrity(spwdp->sp_pwdp, msg));

    size_t len_of_salt;

    if (likely(spwdp->sp_pwdp[0] == '$')) {
        char *end_of_salt;

	ASSERT((end_of_salt = rindex(spwdp->sp_pwdp, '$')) != NULL, "rindex");
	len_of_salt = end_of_salt - spwdp->sp_pwdp;
    } else {
	len_of_salt = 2;
    }

    char *salt;       // Will be allocated to store salts.
    make_salt(&salt, spwdp->sp_pwdp, len_of_salt, msg);

    char *result;

    ASSERT((result = crypt(key, salt)) != NULL, "crypt");
    free(salt);

    RETURN(strcmp(result, spwdp->sp_pwdp) == 0);
}

/*!
 * check_for_unknown_char checks whether the record is valid by 
 *     checking whether the first character is within the range of [a-zA-Z0-9./$].
 */
static bool check_for_unknown_char(char first_ch)
{
    return (first_ch < 'a' || first_ch > 'z') &&
	   (first_ch < 'A' || first_ch > 'Z') &&
	   (first_ch < '0' || first_ch > '9') &&
	   (first_ch != '.')		      &&
	   (first_ch != '/')		      &&
	   (first_ch != '$');
}

/*!
 * check_shadow_record_integrity checks whether the record is valid by 
 *     checking whether the first character is '!' and by calling check_for_unknown_char.
 */
static int check_shadow_record_integrity(const char *spwd, const char **msg)
{
    int ret;

    if (spwd[0] == '!') {
	*msg = "Password is locked.";
	RETURN(0);
    }

    if (check_for_unknown_char(spwd[0])) {
	*msg = "Invalid record of passwd, login is not permitted";
	RETURN(0);
    }

    RETURN(2);
}

/*!
 * make_salt allocates the space for salt and copy salt to it.
 */
static int make_salt(char **salt, const char *beg_of_salt, size_t len_of_salt, const char **msg)
{
    int ret;

    ASSERT((*salt = calloc(len_of_salt + 1, sizeof(char))) != NULL, "calloc");

    memcpy((void*) (*salt), (const void*) beg_of_salt, len_of_salt);
    (*salt)[len_of_salt] = '\0';

    RETURN(2);
}
