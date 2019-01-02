CFLAGS = -Oz -pipe -flto
LDFLAGS = -pipe -flto -Wl,--plugin-opt=O3 -Wl,--icf=all -Wl,-O2 -Wl,--discard-all -Wl,--strip-all -Wl,--as-needed -Wl,--gc-sections

.PHONY: all

all: a.out

a.o: a.c Makefile
	$(CC) $(CFLAGS) -c a.c

a.out: a.o Makefile
	$(CC) $(LDFLAGS) a.o
