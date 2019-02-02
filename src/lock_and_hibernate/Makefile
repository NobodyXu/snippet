CFLAGS:=-Oz -pipe -flto
CFLAGS+=-MMD # When a recompile is needed, the *.d files is probably invalidated as well.
LDFLAGS:=-pipe -flto -Wl,--plugin-opt=O3,--icf=all,-O2,--as-needed,--strip-all

# Library dependency
LIBS:=
STATIC_LIBS:=../verify_passwd/libverify_passwd.a ../getpasswd/libgetpasswd.a

INSTALL_PREFIX=/usr/local/bin

.PHONY: clean install

# source files that lock_and_hibernate depends on
src:=lock_and_hibernate.c ASSERT.c spawn.c readall.c Get_passwd.c Fputs.c
# object files that lock_and_hibernate depends on
OBJ:=$(src:.c=.o)
DEP_FILES:=$(OBJ:.o=.d)

# Files generated during testing (target test)
# Recorded for target clean
TEST_OBJ:=
TEST_EXE:=
TEST_DEP_FILES:=

lock_and_hibernate: $(OBJ) $(STATIC_LIBS)
	$(CC) $(LDFLAGS) $^ $(LIBS) -o $@
	sudo chown root:root $@
	sudo chmod +s $@
	sudo chmod -w $@

# Automatically generate dependency files for *.c
# Rules for *.d
%.d: %.c
	$(CC) -c $(CFLAGS) $<
	sed -i 's/$*.o/$*.o $*.d/g' $@

ifneq ($(MAKECMDGOALS), clean)
include $(DEP_FILES)

# Include makefile of $(STATIC_LIBS)
path_to_getpasswd:=../getpasswd/
include $(path_to_getpasswd)/mk_lib.mk

path_to_verify_passwd:=../verify_passwd/
include $(path_to_verify_passwd)/mk_lib.mk
endif

include test.mk

clean:
	rm -f --interactive=never lock_and_hibernate $(OBJ) $(DEP_FILES) $(TEST_EXE) $(TEST_OBJ) $(TEST_DEP_FILES)

install: lock_and_hibernate Lock_and_hibernate.sh
	cp $< $(INSTALL_PREFIX)
	chmod +s $(INSTALL_PREFIX)/lock_and_hibernate
	cp Lock_and_hibernate.sh $(INSTALL_PREFIX)/Lock_and_hibernate
