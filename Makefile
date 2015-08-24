CC=gcc
CFLAGS=-Wall -Wextra

all:
	$(CC) $(CFLAGS) high_level.c test.c -o test

clean:
	rm test
