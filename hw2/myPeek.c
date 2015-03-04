#include "myPeek.h"

char peekChar (int fd) {

	off_t priorOffset = lseek (fd, 0, SEEK_CUR);
	char c = '\0';

	if (read (fd, &c, 1) == 1) {
		lseek (fd, priorOffset, SEEK_SET);
		return c;
	}
	else {
		lseek (fd, priorOffset, SEEK_SET);
		return EOF;
	}

} 

//Gets next line.
//Does NOT move offset.
void peekLine (int fd, char container [], int n) {

	off_t offsetPrior = lseek (fd, -1, SEEK_CUR);
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



	lseek (fd, offsetPrior, SEEK_CUR);

	return;
}

//Counts the number of bytes until next '\n'.
//When counting from first row, excludes the first character.
//Does NOT move offset.
off_t countLineByte (int fd) {

	off_t priorOffset = lseek (fd, 0, SEEK_CUR);
	off_t bytes = 0;
	char c = '\0';

	while (read (fd, &c, 1) == 1) {
		bytes++;
		//Counts the '\n'.
		if (c == '\n') {
			break;
		}
	}

	lseek (fd, priorOffset, SEEK_SET);

	return bytes++;
}