// For stat
#include <sys/types.h>
#include <sys/stat.h>
// For stat, write and _exit
#include <unistd.h>
// For mmap
#include <sys/mman.h>
// For errno
#include <errno.h>
// For strerror and strlen
#include <string.h>

#include <assert.h>
// The following func Write is meant to be only used in this program.
void print_error() {
    char *msg = strerror(errno);
    size_t len = strlen(msg);
    assert(write(2, msg, len) == len);
    _exit(0);
}
ssize_t Write(int fd, const void *buf, size_t count) {
    ssize_t ret;

    while((ret = write(fd, buf, count)) == -1)
	if (errno == EAGAIN || errno == EWOULDBLOCK)
	    continue;
	else
	    print_error();

    return ret;
}

off_t get_len(int fd) {
    struct stat status;
    if (fstat(0, &status) == -1)
	print_error();
    return status.st_size;
}
static const size_t magic_num = (1 << 10) - 1;
size_t round_to_page_size(off_t size) {
    return (size + magic_num) & ~magic_num;
}

void* Mmap(int fd, size_t len, int prot, int flags) {
    void *ret = mmap(NULL, len, prot, flags, fd, 0);
    if (ret == (void*) -1)
	print_error();
    return ret;
}
int main() {
    off_t len = get_len(0);
    void *stream = Mmap(0, round_to_page_size(len), PROT_READ, MAP_SHARED | MAP_POPULATE);
    Write(1, stream, len);
}
