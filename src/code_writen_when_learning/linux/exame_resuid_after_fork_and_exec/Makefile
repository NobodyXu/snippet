.PHONY: all clean

all: a.out b.out

b.out: b.c a.h
	${CC} b.c -o b.out

a.out: a.c a.h
	${CC} a.c -o a.out
	sudo chown root:root ./a.out
	sudo chmod +s ./a.out

clean: a.out b.out
	sudo rm a.out b.out
