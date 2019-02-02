#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include <assert.h>

void* Calloc(size_t cnt, size_t size)
{
    void *ret = calloc(cnt, size);
    assert(ret);
    return ret;
}

size_t GetSaltLen(const char *salt)
{
    size_t salt_len = strlen(salt);
    assert(salt_len >  0);
    assert(salt_len <= 16);
    return salt_len;
}

char* GetSaltAndVersion(const char version, const char *salt)
{
    size_t saltlen = GetSaltLen(salt);
    /*
     * The format of salt:
     *	   $one_digit_number$up_to_16_character\0
     * For more info, check man crypt.
     */
    char *ret = (char*) Calloc(1 + 1 + 1 + saltlen + 1, sizeof(char));

    char *beg = ret;

    *beg++ = '$';
    *beg++ = version;
    *beg++ = '$';
    memcpy((void*) beg, (const void*) salt, saltlen + 1);

    return ret;
}

void crypt_and_print(const char *passwd, const char *salt_and_version)
{
    char *result = crypt(passwd, salt_and_version);
    assert(puts(result) != EOF);
}

int main(int argc, char* argv[])
{
    if (argc != 4) {
	fprintf(stderr, "argc = %d\n", argc);
	return 1;
    }

    char *salt_and_version = GetSaltAndVersion(argv[2][0], argv[3]);
    crypt_and_print(argv[1], salt_and_version);
    free(salt_and_version);

    return 0;
}
