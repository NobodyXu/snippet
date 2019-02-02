#include "Get_passwd.h"
#include "Fputs.h"

#include <stdio.h> // For fputs
#include <stdlib.h>// For free

int main(int argc, char* argv[])
{
    char *passwd;

    int cnt;

    for (cnt = 0; cnt != 3; ++cnt) {
        passwd = Get_passwd_by_gui();

	if (passwd) {
	    Fputs(passwd, stdout);
	    free(passwd);
	} else {
	    Fputs("Get_passwd_by_gui fails", stderr);
	}
    }

    for (cnt = 0; cnt != 3; ++cnt) {
	passwd = Get_passwd_by_console();
        Fputs(passwd, stdout);
	free(passwd);
    }

    return 0;
}
