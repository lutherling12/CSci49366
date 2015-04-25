/******************************************************************************
Title:    Unix Tools - Assignment 2 - Book List
Author:   Luther Ling

Build:    make all
Usage:    ./a.out lineNumber newTitle newAuthor

Description:
Building off the last assignment of writing to file, this takes an existing
file called "books.txt" in the present working directory, and replaces 
a designated line with newTitle and newAuthor via lseeking. The first line
in the file cannot be replaced, as I had trouble getting the first 
character of the file replaced via lseeking methods. 

The expected format of each line in "books.txt" is:
Line 1: Title Author
Line n: "author_of_the_book title_of_the_book\n"
i.e. both fields are separated via spaces.

To clarify, if "example string" is typed in as newTitle or new Author, the 
spaces are replaced with underscores ("example_string") in the resulting 
document. newTitle and newAuthor arguments have a size limit set to
(TITLE/AUTHOR)_BUFFER_SIZE.

Extra:
The terminal command "make all" builds the program, while make clean will 
remove the executable and .o files, there is the command, "make reset".
which is meant to be used when user is done testing by overwriting lines 
in "books.txt". Changes to "books.txt" can be undone through "make reset",
which overwrites "books.txt" with the file "nytBestSeller(28.02.15).txt".
******************************************************************************/
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

/*Replaces all whitespaces in string str with char replacementChar.*/
void replaceSpaces (char str[], char replacementChar = '_');
/*Write a string into file with file descriptor fd*/
void writeStr (int fd, char str []);
/*From file with file descriptor fd's current offset, put the next field
(either title or author) into buffer.*/
bool getNextField (int fd, char buffer []);

int main (int argc, char * argv [])
{
	char title[TITLE_BUFFER_SIZE];
	char author [AUTHOR_BUFFER_SIZE];
	
	int fileDesc = open ("books.txt", O_RDWR);
	off_t offsetNow;

	int rowNum = 0;
	int titleLength = 0, authorLength = 0;
	int oldLineLength = 0, newLineLength = 0;

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

  /*If the byte count of the content being replaced is equal to the
  byte count of newTitle and newAuthor, overwrite the line.*/
	if (oldLineLength == newLineLength) {

		writeStr (fileDesc, title);
		
		tempChar = ' ';
		write (fileDesc, &tempChar, 1);
		
		writeStr (fileDesc, author);

		tempChar = '\n';
		write (fileDesc, &tempChar, 1);
	}

  /*If the byte count of the line being replaced is greater than the
  byte count of newTitle and newAuthor, write the new contents, then
  pad it with spaces.*/
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

  /*If the byte count of the line being replaced is less than the byte
  count of the newTitle and newAuthor, write the content via tail recursion
  such that each line shifts over however many bytes and makes space 
  for the new content.*/
	else if (oldLineLength < newLineLength) {

		lseek (fileDesc, oldLineLength, SEEK_CUR);

		shiftWrite (fileDesc, (int)(newLineLength - oldLineLength));

		//Move offset to the line after the one to be written over.
		lseek (fileDesc, offsetNow, SEEK_SET);

		//Write over offset.
		writeStr (fileDesc, title);

		tempChar = ' ';
		write (fileDesc, &tempChar, 1);
		
		writeStr (fileDesc, author);

		tempChar = '\n';
		write (fileDesc, &tempChar, 1);
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