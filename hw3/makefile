CC=g++
CFLAGS=-c -Wall
OBJS=hw3.o

all: hw3

hw3: $(OBJS)
	$(CC) $(OBJS) -o a.out

hw3.o: hw3.c
	$(CC) $(CFLAGS) hw3.c

clean:
	rm *.out *.o notMine
