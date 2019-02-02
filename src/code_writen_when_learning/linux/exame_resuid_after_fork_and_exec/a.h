#ifndef  __a_H__
# define __a_H__

# define _GNU_SOURCE
# include <unistd.h>

# include <assert.h>
# include <stdio.h>

# define UID "%u"

void print_resuid(const char *msg)
{
    uid_t ruid, euid, suid;
    assert(getresuid(&ruid, &euid, &suid) == 0);
    assert(printf("%s ruid = " UID ", euid = " UID ", suid = " UID ".\n", msg, ruid, euid, suid) > 0);

    assert(fflush(stdout) == 0);
}

# undef UID
# undef _GNU_SOURCE
#endif
