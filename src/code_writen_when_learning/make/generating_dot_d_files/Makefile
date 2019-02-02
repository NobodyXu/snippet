%.d: %.c
	$(CC) -MMD $<
	sed -i -e "s/$*.o/$*.o $*.d/g" -e 's/[^ ]*/$$(prefix_for_test)&/g' $@

clean: 
	rm *.d
