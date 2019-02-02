$(path_to_getpasswd)libgetpasswd.a: $(path_to_getpasswd)getpasswd.o
	${AR} rcs $@ $<
$(path_to_getpasswd)getpasswd.o: $(path_to_getpasswd)getpasswd.h
