#include <stdio.h>
#include <stddef.h>
#include <sys/mman.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
int main() {
    size_t s = 4096, max_size = ((size_t) 1) << 33;

    void *ptr;

    // Replace the following line with a less aggressive memory request increasement to make sure the call to mmap will succeed.
    //for( ; s <= max_size; s <<= 1) {
    for( ; s <= max_size; s += 4096) {
	ptr = mmap(NULL, s, PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	fprintf(stderr, "Call to mmap to request %lu GB, %lu MB, %lu KB memory", s >>30, s >> 20, s >> 10);

	if (ptr == (void*) -1)
	    fprintf(stderr, " failed due to %s.\n", strerror(errno));
	else {
	    fprintf(stderr, " succeeded, now write to the memory.\nPress enter to continue");
	    fgetc(stdin);
	    memset(ptr, 111111, s);
	    // Don't free them.
	    // Create a case where memory is not enough.
	    // Because vm.overcommit = 0 on my system, I can't directly allocate 8 GB to create such a sencior.
	    // However, before I comment the following line, I can already experience that part of the memory had been swapped out due to the delay happened when I switched windows.
	    //assert(munmap(ptr, s) == 0);
	}
    }//End of loop.
}
