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

void getALine (int fd, char container [], int n) {

	lseek (fd, -1, SEEK_CUR);

	char c = '\0';
	int i = 0;

	do {	

		c = getChar (fd);

		if ((c == '\n') || (c == EOF)) {
			container[i] = '\n';
			container[i+1] = '\0';
			return;
		}
		else {
			container[i] = c;
			i++;
		}

	} while (i < n - 2);

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
