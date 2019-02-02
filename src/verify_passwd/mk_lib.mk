LIBS+=-lcrypt

$(path_to_verify_passwd)libverify_passwd.a: $(path_to_verify_passwd)verify_passwd.o
	${AR} rcs $@ $<
$(path_to_verify_passwd)verify_passwd.o: $(path_to_verify_passwd)verify_passwd.h
