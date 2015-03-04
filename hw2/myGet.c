#include "myGet.h"

//From Adriana Wise's notes - read() and returns char from file
/*Function changes offset in open file. Reset the changed offset by calling
off_t value = lseek (int fd, off_t offsetPrior, SEEK_SET)*/
char getChar (int fd) {

	char c = '\0';
	
	if (read (fd, &c, 1) == 1)
		return c;
	else
		return EOF;
}

void getLine (int fd, char container [], int n) {

	char c = '\0';

	for (int i = 0; i < n - 2; i++) {
		if (read (fd, &c, 1) == 1) {
			container[i] = c;
		}
		else {
			container[i] = '\0';
			break;
		}
	}

	container[n-1] = '\0';

	return;	
}

//From Adriana Wise's notes - returns byte position where given row starts.
//Moves offset.
off_t getBytePos (int row, int fd) {
	
	int byte = 1, lines = 1, currChar;

	do {
		currChar = getChar (fd);
		if (currChar == '\n')
			lines++;
	} while (lines < row && currChar != EOF && ++byte);

	return byte;
}
