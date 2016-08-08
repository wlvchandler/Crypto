CC=gcc
CFLAGS=-std=c99 -c -Wall -Wextra -pedantic

all: rc4

rc4: rc4.o argutils.o
	$(CC) rc4.o argutils.o -o rc4

rc4.o: rc4.c
	$(CC) $(CFLAGS) rc4.c

argutils.o: argutils.c
	$(CC) $(CFLAGS) argutils.c

