.PHONY: test

TEST_SRC:=test_spawn.c test_readall.c test_Get_passwd.c
TEST_OBJ:=$(TEST_SRC:.c=.o)
TEST_DEP_FILES+=$(TEST_OBJ:.o=.d)
TEST_EXE:=$(TEST_OBJ:.o=.out)

# Include dependency files for $(TEST_OBJ)
# Rules are defined in Makefile
ifneq ($(MAKECMDGOALS), clean)
include $(TEST_DEP_FILES)
endif

test: $(TEST_EXE)
test_spawn.out: test_spawn.o spawn.o ASSERT.o Fputs.o
	$(CC) $(LDFLAGS) $^ -o $@
test_readall.out: test_readall.o spawn.o readall.o ASSERT.o Fputs.o
	$(CC) $(LDFLAGS) $^ -o $@
test_Get_passwd.out: test_Get_passwd.o Get_passwd.o spawn.o readall.o ASSERT.o ../getpasswd/libgetpasswd.a Fputs.o
	$(CC) $(LDFLAGS) $^ -o $@
