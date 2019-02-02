CFLAGS:=-Oz -pipe -flto
LDFLAGS:=-pipe -flto -Wl,--plugin-opt=O3,--icf=all,-O2,--strip-all,--as-needed,--gc-sections
LIBS:=

.PHONY: clean

path_to_getpasswd:=

include mk_lib.mk

test: test.o libgetpasswd.a
	$(CC) $(LDFLAGS) $^ -o $@
test.o: getpasswd.h
clean:
	rm -f --interactive=never test test.o libgetpasswd.a getpasswd.o getpasswd.d
