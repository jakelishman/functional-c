CC=gcc
CFLAGS=-Wall -Wextra

all:
	$(CC) $(CFLAGS) functional.c demo.c -o demo

clean:
	rm demo
