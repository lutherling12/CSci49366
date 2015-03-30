CC=g++
CFLAGS=-c -Wall
OBJS=hw4.o

all: hw4

hw4: $(OBJS)
	$(CC) $(OBJS) -o a.out

hw4.o: hw4.c
	$(CC) $(CFLAGS) hw4.c

clean:
	rm *.out *.o