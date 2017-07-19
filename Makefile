CC = gcc
CFLAGS = -std=c99 -g -Wall

main: mem.o main_test.c
	$(CC) $(CFLAGS) -o $@ $^

mem.o: mem.c mem.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f main mem.o
