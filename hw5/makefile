CC=gcc
CFLAGS=-c -Wall -std=c99
OBJS=hw5.o

all: hw5

hw5: $(OBJS)
	$(CC) $(OBJS) -o a.out

hw5.o: hw5.c
	$(CC) $(CFLAGS) hw5.c

clean:
	rm *.out *.o
