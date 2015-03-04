#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

//For off_t
#include <sys/types.h>
//For lseek()
#include <unistd.h>

#define TITLE_BUFFER_SIZE 256
#define AUTHOR_BUFFER_SIZE 256
#define TEMP_BUFFER_SIZE 512

#include "myGet.h"
#include "myPeek.h"
#include "myWrites.h"

void replaceSpaces (char str[], char replacementChar = '_');
void writeStr (int fd, char str []);
bool getNextField (int fd, char buffer []);

int main (int argc, char * argv [])
{
	char title[TITLE_BUFFER_SIZE];
	char author [AUTHOR_BUFFER_SIZE];
	char tempTitle [TITLE_BUFFER_SIZE];
	char tempAuthor [AUTHOR_BUFFER_SIZE];
	
	int fileDesc = open ("books.txt", O_RDWR);
	off_t offsetNow, offsetNext;

	int rowNum = 0;
	int titleLength = 0, authorLength = 0;
	int oldLineLength = 0, newLineLength = 0;

	bool hasTitle = false, hasAuthor = false;

	if (argc != 4) {
		printf ("%s\n", 
			"command line arguments are \"<lineNum> <title> <author>\".");
		return 1;
	}

	rowNum = atoi (argv[1]);
	if (rowNum < 2) {
		printf ("%s\n", "first argument invalid row number.");
		return 1;
	}

	if (fileDesc == -1) {
		printf ("%s\n", "books.txt file not found in pwd.");
		return 1;
	}

	strncpy (title, argv[2], TITLE_BUFFER_SIZE);
	strncpy (author, argv[3], AUTHOR_BUFFER_SIZE);
	replaceSpaces (title);
	replaceSpaces (author);

	titleLength = strlen (title);
	authorLength = strlen (author);

	offsetNow = getBytePos (rowNum, fileDesc);
	oldLineLength = countLineByte (fileDesc);	
	//+2 accounts for space delimiter and '\n'.
	newLineLength = titleLength + authorLength + 2;

	char tempChar = '\0';

	if (oldLineLength == newLineLength) {

		writeStr (fileDesc, title);
		
		tempChar = ' ';
		write (fileDesc, &tempChar, 1);
		
		writeStr (fileDesc, author);

		tempChar = '\n';
		write (fileDesc, &tempChar, 1);
	}

	else if (oldLineLength > newLineLength) {
		
		writeStr (fileDesc, title);
		
		tempChar = ' ';
		write (fileDesc, &tempChar, 1);
		
		writeStr (fileDesc, author);

		tempChar = ' ';
		for (int i = 1; i <= (oldLineLength - newLineLength); i++) {
			write (fileDesc, &tempChar, 1);
		}

		tempChar = '\n';
		write (fileDesc, &tempChar, 1);
	}

	else if (oldLineLength < newLineLength) {
		//Move offset to the line after the one to be written over.
		offsetNext = lseek (fileDesc, oldLineLength, SEEK_CUR);
		
		//Get the title and author of the following book.
		getNextField (fileDesc, tempTitle);
		getNextField (fileDesc, tempAuthor);

		printf ("%s %s : %s\n", "Next Book: ", tempTitle, tempAuthor);

		//Move offset back.
		lseek (fileDesc, offsetNow, SEEK_SET);
	
		//Write over offset.
		writeStr (fileDesc, title);

		tempChar = ' ';
		write (fileDesc, &tempChar, 1);
		
		writeStr (fileDesc, author);

		tempChar = '\n';
		write (fileDesc, &tempChar, 1);

		//Move offset to row after next.
		getBytePos (2, fileDesc);

		while (peekChar (fileDesc) != EOF) {
			peekLine (fileDesc, tempTitle, TEMP_BUFFER_SIZE);
			printf ("%s %s : %s\n", "Next Book: ", tempTitle, tempAuthor);
		}

	}

	if (close (fileDesc) != 0) {
		printf ("File closed unsucessfully.");
		return 1;
	}
	else {
		return 0;
	}
}

void replaceSpaces (char str[], char replacementChar) {
	int length = strlen (str);

	for (int i = 0; i < length-1; i++) {
		if (str[i] == ' ') {
			printf("%c", str[i]);
			str[i] = replacementChar;
		}
	}
}

//Gets next string delimited by ' ' or '\n'.
//Moves offset.
bool getNextField (int fd, char buffer []) {

	char c = '\0';
	int bufferSize = TEMP_BUFFER_SIZE;

	for (int i = 0; i < bufferSize - 2; i++) {
		c = getChar(fd);
		if (c == EOF) {
			buffer[i] = '\0';
			return false;
		}
		else if (c == ' ' || c == '\n') {
			buffer [i] = '\0';
			return true;
		}
		else {
			buffer[i] = c;
		}
	}
	buffer[bufferSize -1] = '\0';
	return true;
}