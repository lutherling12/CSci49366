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

	off_t offsetPrior = lseek (fd, 0, SEEK_CUR);
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
	lseek (fd, offsetPrior, SEEK_CUR);

	return;
}

//Counts the number of bytes until next '\n'.
//When counting the first row of file, excludes first character.
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

	return bytes;
}