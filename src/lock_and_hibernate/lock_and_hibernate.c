#include "../verify_passwd/verify_passwd.h"

#include "ASSERT.h"
#include "spawn.h"
#include "Get_passwd.h"
#include "Fputs.h"

#include <sysexits.h>// For EX_NOPERM
#include <stdio.h>   // For puts
#include <stdlib.h>  // For free
#include <unistd.h>  // For execl, sleep
#include <errno.h>   // For errno

/*!
 * Sleep hangs up the process for secs seconds.
 * It assumes secs > 0.
 */
void Sleep(unsigned int secs)
{
    do {
	secs = sleep(secs);
    } while (secs > 0);
}

bool Verify_passwd(const char *passwd)
{
    const char *msg = NULL;
    int ret = verify_passwd(passwd, &msg);

    if (ret < 0) {	  // If an error occurs
	errno = -ret;
	assert_syscall_failure(msg);
    } else if (ret == 0) {// Or the authorisation fails
	ASSERT_SYSCALL(printf("Authroisation fails %s %s\n", msg ? "due to" : "", msg ? msg : "") > 0);
	
	return false;
    } else
	return true;
}

/*!
 * get_and_verify_passwd get and verify passwd.
 *
 * It either use $SUDO_ASKPASS (if present), or getpasswd (command line).
 */
bool get_and_verify_passwd()
{
    char *passwd = NULL;
    passwd = Get_passwd_by_gui();

    if (passwd == NULL) {
	Fputs("\nEnter your passwd here:", stdout);
	passwd = Get_passwd_by_console();
    }

    bool ret = Verify_passwd(passwd);

    free(passwd);
    return ret;
}

int main(int argc, char* argv[])
{
    int cnt = 0;

    while (true) {
	if (cnt >= 3) {
	    Fputs("You have been keeping entering wrong password for 3 times.\n", stderr);
	    return EX_NOPERM;
	}

	if (get_and_verify_passwd()) {
	    Fputs("Password verified...\n", stdout);
	    break;
	}

	++cnt;
    }

    spawn("/usr/bin/i3lock", false, true, NULL);
    
    Sleep(1);

    ASSERT_SYSCALL(execl("/usr/sbin/s2disk", "/usr/sbin/s2disk", (char*) NULL));

    __builtin_unreachable();
}
