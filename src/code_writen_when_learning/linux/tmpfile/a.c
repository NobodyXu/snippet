#include <stdio.h>
#include <errno.h>

#define FWRITE(STRING, nmemb, stream)\
    fwrite(STRING, sizeof(STRING) - 1, nmemb, stream)

int main(int argc, char* argv[])
{
    FILE *tmp = tmpfile();
    if (!tmp) {
	perror("tmpfile");
	return 1;
    }
    tmpfile();

    FWRITE("HAHAHA", 2, tmp);

    getchar();

    return 0;
}
