CFLAGS += -Oz -pipe
LDFLAGS += -nostartfiles -nostdlib -Wl,--strip-all

.PHONY: all clean test

all: a.out test

a.o: a.c Makefile
	$(CC) $(CFLAGS) -c a.c

a.out: a.o
	$(CC) $(LDFLAGS) a.o

test: a.out
	./a.out
	echo $?
	ls -lh a.out
	wc -c a.out

clean:
	rm a.o a.out
