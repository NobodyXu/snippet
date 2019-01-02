CFLAGS = -Oz -pipe -flto
LDFLAGS = -pipe -flto -Wl,--plugin-opt=O3 -Wl,--icf=all -Wl,-O2 -Wl,--discard-all -Wl,--strip-all -Wl,--as-needed -Wl,--gc-sections

.PHONY: all

all: a.out

a.out: main.o f1.o Makefile
	$(CC) $(LDFLAGS) main.o f1.o -o a.out

main.o: main.c Makefile
	$(CC) $(CFLAGS) -c main.c

f1.o: f1.c Makefile
	$(CC) $(CFLAGS) -c f1.c
