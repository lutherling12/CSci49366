#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>

#include <sys/types.h>
#include <grp.h>

void printHeader ();

int main (int argc, char ** argv) {
  
  struct group * temp_gr;

  for (int i=0; i <= INT_MAX; i++) {
    if ((i % 20) == 0) {
      printHeader ();
    }

    temp_gr = getgrgid ((gid_t)i);
      
    if (temp_gr != NULL) {
      printf ("%*i |", 10, i);
      printf ("%*s\n", -20, temp_gr->gr_name);
    }
    else {
      printf ("%*i |", 10, i);
      printf ("%*s\n", -20, "");
    }
    sleep (1);
  }

  return 0;
}

void printHeader () {

  for (int i = 1; i <= 80; i++) {
    printf ("*");
  }

  printf ("%*s", 10, "   Group ID|");
  printf ("%*s\n", -20, "Group Name");

  for (int i = 1; i <= 80; i++) {
    printf ("*");
  }  
}