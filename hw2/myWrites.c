#include "myWrites.h"

//Writes given string. 
//Moves offset.
void writeStr (int fd, char str []) {
	
	int length = strlen (str);
	char c = '\0';

	for (int i = 0; i < length; i++) {
		c = str[i];
		write (fd, &c, 1);
	}

	return; 
}

bool shiftWrite (int fd, off_t shiftBytes) {

	char buffer[BUFFER_SIZE];
	off_t priorOffset = lseek (fd, 0, SEEK_CUR);

	char c = getChar (fd);

	//Assume getLine moves offset.
	getALine (fd, buffer, BUFFER_SIZE);	

	if (peekChar (fd) != EOF) {
		shiftWrite (fd, shiftBytes);
		priorOffset = lseek (fd, (off_t)(priorOffset + shiftBytes), SEEK_SET);
		//Assumes writeStr moves offset.
		writeStr (fd, buffer);

	//printf ("\'%s\'\n", buffer);

		lseek (fd, priorOffset, SEEK_SET);
		return true;
	}
	else {
		buffer[strlen(buffer)-1] = '\0';
		priorOffset = lseek (fd, (off_t)(priorOffset + shiftBytes), SEEK_SET);
		//Assumes writeStr moves offset.
		writeStr (fd, buffer);

	//printf ("\'%s\'\n", buffer);

		lseek (fd, priorOffset, SEEK_SET);
		return false;
	}

}