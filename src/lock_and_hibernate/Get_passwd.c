#include "Get_passwd.h"
#include "../getpasswd/getpasswd.h"
#include "spawn.h"
#include "readall.h"
#include "ASSERT.h"
#include "Fputs.h"

#include <stdio.h>   // For fputs
#include <stdlib.h>  // For getenv
#include <sys/wait.h>// For waitpid
#include <errno.h>

#define ERR(MSG)	\
    Fputs(MSG, stderr); \
    return NULL

extern char* Get_passwd_by_gui()
{
    char *sudo_askpass_prog_name;
    int in_fd;

    sudo_askpass_prog_name = getenv("SUDO_ASKPASS");

    if (sudo_askpass_prog_name == NULL) {
	ERR("No env variable SUDO_ASKPASS");
    }

    pid_t child_pid = spawn(sudo_askpass_prog_name, false, false, &in_fd);

    char *passwd;
    size_t n;

    passwd = readall(in_fd, &n);

    pid_t waited_child_pid;
    int status;
    
    ASSERT_SYSCALL2(waited_child_pid, (waitpid(child_pid, &status, 0)), -1);

    if (!WIFEXITED(status)) {
	free(passwd);
	ERR("Child process being killed by signal");
    }

    if (WEXITSTATUS(status)) {
	free(passwd);
	ERR("Child exits with non-zero value");
    }

    passwd[n - 1] = '\0';

    return passwd;
}

#undef ERR

extern char* Get_passwd_by_console()
{
    char *passwd = NULL;
    size_t n = 0;
    const char *msg = NULL;
    ssize_t passwd_len = getpasswd(&passwd, &n, &msg);

    if (passwd_len < 0) {
	errno = -passwd_len;
	assert_syscall_failure(msg);
    }

    return passwd;
}
