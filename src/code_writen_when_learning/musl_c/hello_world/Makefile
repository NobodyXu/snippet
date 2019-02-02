.PHONY: all clean

all: a.out
a.out: hello.c
	musl-clang -static -Oz hello.c

clean:
	rm -f --interactive=never a.out
