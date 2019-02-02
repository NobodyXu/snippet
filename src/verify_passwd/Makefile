CFLAGS:=-Oz -pipe -flto
LDFLAGS:=-pipe -flto -Wl,--plugin-opt=O3,--icf=all,-O2,--strip-all,--as-needed,--gc-sections
LIBS:=

.PHONY: clean

path_to_verify_passwd:=
include mk_lib.mk

path_to_getpasswd:=../getpasswd/
include $(path_to_getpasswd)/mk_lib.mk

test: test.o libverify_passwd.a ../getpasswd/libgetpasswd.a
	${CC} $(LDFLAGS) $^ $(LIBS) -o $@
	sudo chown root:root $@
	sudo chmod +s $@
test.o: verify_passwd.h ../getpasswd/getpasswd.h
# cd ../getpasswd && $(MAKE)
clean:
	rm -f --interactive=never test test.o libverify_passwd.a verify_passwd.o verify_passwd.d
