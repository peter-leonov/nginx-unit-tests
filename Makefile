CC=gcc -Wall -O2

test: string_test
	@./string_test

string_test: string_test.o testing.o
	$(CC) -o $@ $@.o $@.o.wrapper.o testing.o
	@rm $@.o.wrapper.o

testing.o: testing.c testing.h
	$(CC) -c testing.c

.c.o:
	$(CC) -c $<
	@nm $@ | ./nm2c.pl > $@.wrapper.c
	@cat wrapper.c >> $@.wrapper.c
	@$(CC) -o $@.wrapper.o -c $@.wrapper.c
	@rm $@.wrapper.c