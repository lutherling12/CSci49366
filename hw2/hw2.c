#include <stdlib.h>
#include <stdio.h>

#include <fcntl.h>

//For lseek()
#include <sys/types.h>
#include <unistd.h>

#include <string.h>

#define TITLE_BUFFER_SIZE 256
#define AUTHOR_BUFFER_SIZE 256
#define TEMP_BUFFER_SIZE 256

void replaceSpaces (char str[], char replacementChar = '_');
char getChar (int fd);
off_t getBytePos (int row, int fd);
off_t countLineByte (int fd, off_t priorOffset);
//bool getnChar (int fd, char buffer [], int n);
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
	oldLineLength = countLineByte (fileDesc, offsetNow);	
	//+2 accounts for space delimiter and '\n'.
	newLineLength = titleLength + authorLength + 2;

	char tempChar = '\0';

	if (oldLineLength == newLineLength) {

		for (int i = 0; i < titleLength; i++) {
			tempChar = title[i];
			write (fileDesc, &tempChar, 1);
		}
		
		tempChar = ' ';
		write (fileDesc, &tempChar, 1);
		
		for (int i = 0; i < authorLength; i++) {
			tempChar = author[i];
			write (fileDesc, &tempChar, 1);
		}

		tempChar = '\n';
		write (fileDesc, &tempChar, 1);
	}

	else if (oldLineLength > newLineLength) {
		
		for (int i = 0; i < titleLength; i++) {
			tempChar = title[i];
			write (fileDesc, &tempChar, 1);
		}
		
		tempChar = ' ';
		write (fileDesc, &tempChar, 1);
		
		for (int i = 0; i < authorLength; i++) {
			tempChar = author[i];
			write (fileDesc, &tempChar, 1);
		}

		tempChar = '\0';
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
		for (int i = 0; i < titleLength; i++) {
			tempChar = title[i];
			write (fileDesc, &tempChar, 1);
		}
		
		tempChar = ' ';
		write (fileDesc, &tempChar, 1);
		
		for (int i = 0; i < authorLength; i++) {
			tempChar = author[i];
			write (fileDesc, &tempChar, 1);
		}

		tempChar = '\n';
		write (fileDesc, &tempChar, 1);

		//Move offset to row after next.
		getBytePos (2, fileDesc);

		do {
			offsetNow = lseek (fileDesc, 0, SEEK_CUR);

			hasTitle = getNextField (fileDesc, tempTitle);
			hasAuthor = getNextField (fileDesc, tempAuthor);

			printf ("%s %s : %s\n", "Next Book: ", tempTitle, tempAuthor);
			printf ("%ld : %ld\n", offsetNow, offsetNext);

			offsetNext = lseek (fileDesc, 0, SEEK_CUR);

			lseek (fileDesc, offsetNow, SEEK_SET);
	
			titleLength = strlen (title);
			authorLength = strlen (author);

			for (int i = 0; i < titleLength; i++) {
				tempChar = title[i];
				write (fileDesc, &tempChar, 1);
			}
		
			tempChar = ' ';
			write (fileDesc, &tempChar, 1);
		
			for (int i = 0; i < authorLength; i++) {
				tempChar = author[i];
				write (fileDesc, &tempChar, 1);
			}

			tempChar = '\n';
			write (fileDesc, &tempChar, 1);
		} while (hasTitle && hasAuthor);
	}

	return 0;
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

//From Adriana Wise's notes - returns byte position where given row starts
off_t getBytePos (int row, int fd) {
	int byte = 1, lines = 1, currChar;

	do {
		currChar = getChar (fd);
		if (currChar == '\n')
			lines++;
	} while (lines < row && currChar != EOF && ++byte);

	return byte;
}

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

//Counts the number of bytes in line. Undoes Offset after.
//When counting the first row of file, excludes first character.
off_t countLineByte (int fd, off_t priorOffset) {
	int bytes = 0;
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