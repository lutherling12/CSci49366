#include <stdlib.h>
#include <pwd.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
//#include <types.h>

void printHeader ();

int main (int argc, char ** argv) {
  
  struct passwd * temp_pw;
  gid_t temp_gid;
  struct group * temp_gr;

  for (int i=0; i <= INT_MAX; i++) {
    if ((i % 20) == 0) {
      printHeader ();
    }

    temp = getpwuid (i);

    if (temp != NULL) {
      printf ("%*i |", +10, i);
      printf ("%*s", -20, temp_pw->pw_name);
      temp_gid = temp_pw->pw_gid;
      temp_gr = getgrid (temp_gid);
      printf ("%*i |", +10, temp_gid);
      printf ("%*s\n", -20, temp_gr->gr_name);
    }
    else {
      printf ("%*i |", +10, i);
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

  printf ("%*s", +10, "  ID Number|");
  printf ("%*s\n", -20, "Username");

  for (int i = 1; i <= 80; i++) {
    printf ("*");
  }  
}