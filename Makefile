CC=gcc -W -Wall -Wpointer-arith -Wno-unused-parameter -Wno-unused-function -Wunused-variable -Wunused-value -Werror \
	-O2 -I"$(PATH_TO_NGINX)/objs/" -I"$(PATH_TO_NGINX)/src/core/" -I"$(PATH_TO_NGINX)/src/os/unix/"

NGX_OBJS=$(PATH_TO_NGINX)/objs
NGX_ALL_OBJS= -lpcre -lcrypto -lz $(NGX_OBJS)/src/core/ngx_*.o $(NGX_OBJS)/src/os/unix/ngx_*.o $(NGX_OBJS)/src/event/ngx_*.o $(NGX_OBJS)/src/http/ngx_*.o $(NGX_OBJS)/src/http/modules/ngx_*.o $(NGX_OBJS)/src/event/modules/ngx_*.o $(NGX_OBJS)/ngx_*.o

test: check_path string_test
	@./string_test

check_path:
ifdef PATH_TO_NGINX
	@echo testing nginx at $(PATH_TO_NGINX)
else
	$(error PATH_TO_NGINX is undefined)
endif

string_test: string_test.o testing.o
	@$(CC) -o $@ $@.o $@.o.wrapper.o $(NGX_OBJS)/src/core/ngx_string.o $(NGX_OBJS)/src/core/ngx_palloc.o testing.o # $(NGX_OBJS)/src/os/unix/ngx_alloc.o -e testing_main -S

testing.o: testing.c testing.h
	@$(CC) -c testing.c

.c.o:
	@$(CC) -c $<
	@nm $@ | ./nm2c.pl > $@.wrapper.c
	@cat wrapper.c >> $@.wrapper.c
	@$(CC) -o $@.wrapper.o -c $@.wrapper.c
	@rm $@.wrapper.c
