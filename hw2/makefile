CC=g++
CFLAGS=-c -Wall 
SOURCE=hw2.o myGet.o myPeek.o myWrites.o

all: hw2

hw2: $(SOURCE)
	$(CC) $(SOURCE) -o a.out

hw2.o: hw2.c
	$(CC) $(CFLAGS) hw2.c

myGet.o: myGet.c
	$(CC) $(CFLAGS) myGet.c

myPeek.o: myPeek.c
	$(CC) $(CFLAGS) myPeek.c

myWrites.o: myWrites.c
	$(CC) $(CFLAGS) myWrites.c

clean:
	rm *.out *.o

reset:
	rm *.o & cp 'nytBestSeller(28.02.15).txt' books.txt
