#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>

#define BUFSIZE 4096

int main (int argc, char * argv [])
{
   char str[BUFSIZE];
   int length = 0;
   int newfd = 0;

   if (argc > 2) {
      printf ("Please use only first name. \n");
      exit (1);
   }

   if (argc == 1) {
      printf ("What is your name? \n");
      fgets (str, BUFSIZE, stdin);
      length = strlen (str);

      newfd = creat ("myNameIs", S_IRWXU);
      if (length <= BUFSIZE) {
        write (newfd, str, length);
      }
      else {
        printf ("Your name is too long. \n");
      }
   }
 
   if (argc == 2) {
      length = strlen (argv[1]);

      newfd = creat ("myNameIs", S_IRWXU);
      if (length <= BUFSIZE) {
         write (newfd, argv[1], length);
      }
      else {
         printf ("Your name is too long. \n");
      }
   }

   close (newfd);

   return 0;
}
