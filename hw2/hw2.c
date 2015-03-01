#include <stdlib.h>
#include <stdio.h>

#include <fcntl.h>

int main (int argc, char * argv [])
{
	char title[200];
	char author [200];

	int fd = open ("books.txt", O_RDWR);
	printf ("%s %i", "Books fd is: ", fd);

	return 0;

sdsdds
}
