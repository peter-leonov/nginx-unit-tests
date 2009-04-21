CC=gcc -Wall -O2 -I"$(PATH_TO_NGINX)/objs/" -I"$(PATH_TO_NGINX)/src/core/" -I"$(PATH_TO_NGINX)/src/os/unix/"

test: check_path string_test
	@./string_test

check_path:
ifdef PATH_TO_NGINX
	@echo testing nginx at $(PATH_TO_NGINX)
else
	$(error PATH_TO_NGINX is undefined)
endif

string_test: string_test.o testing.o
	$(CC) -o $@ $@.o $@.o.wrapper.o testing.o

testing.o: testing.c testing.h
	$(CC) -c testing.c

.c.o:
	$(CC) -c $<
	@nm $@ | ./nm2c.pl > $@.wrapper.c
	@cat wrapper.c >> $@.wrapper.c
	@$(CC) -o $@.wrapper.o -c $@.wrapper.c
	@rm $@.wrapper.c
