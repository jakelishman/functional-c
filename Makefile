CC=gcc
CFLAGS=-Wall -Wextra

all:
	$(CC) $(CFLAGS) high_level.c demo.c -o demo

clean:
	rm demo
