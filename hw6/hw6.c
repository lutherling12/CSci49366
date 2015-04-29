/*Wait3() is considered "obsolete" and waitpid/waitid are suggested 
alternatives, but  the assignment calls for usage of wait3() due to
collection of resource usage (rusage) of the child(?) process.*/
#include <stdlib.h>
#include <stdio.h>

#include <signal.h>

//Needed for fork().
#include <unistd.h>
//All needed for getrusage() and wait3().
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>

#include <limits.h>

void printHeader ();

int main (int argc, char ** argv[])
{
  struct rusage myProcess;
  int errNo = 0;
  int ret = fork ();
  int status = 0;
  pid_t childPID = 0;

  for (int i = 0; i <= INT_MAX; i++) {
    //If child
    if (ret == 0) {
      exit (errNo);
    }
    //Else parent 
    else {
      childPID = wait3 (status, 0, myProcess);
      getrusage (RUSAGE_CHILDREN, &myProcess);
      errNo++;
    }

    printHeader();

    //The disabled fields are "unmaintained" on Linux.
    printf ("%*s %i\n", 35, "Error Number:",
      errNo);

    printf ("%*s %li\n", 35, "User CPU Time (sec):",
      myProcess.ru_utime.tv_sec);
    printf ("%*s %li\n", 35, "System CPU Time (sec):",
      myProcess.ru_stime.tv_sec);
    printf ("%*s %li\n", 35, "Maximum Resident Set Size (kB):",   
      myProcess.ru_maxrss);
    /*
      printf ("%*s %li\n", 35, "Integral Shared Memory Size (kB):", 
        myProcess.ru_ixrss);
      printf ("%*s %li\n", 35, "Integral Unshared Data Size (kB):", 
        myProcess.ru_idrss);
      printf ("%*s %li\n", 35, "Integral Unshared Stack Size (kB):", 
        myProcess.ru_isrss);
    */
    printf ("%*s %li\n", 35, "Page Reclaims:", 
      myProcess.ru_minflt);
    printf ("%*s %li\n", 35, "Page Faults:", 
      myProcess.ru_nswap);
    /*
      printf ("%*s %li\n", 35, "Swaps:", 
        myProcess.ru_inblock);
    */
    printf ("%*s %li\n", 35, "Block Input Operations:", 
      myProcess.ru_oublock);
    /*
      printf ("%*s %li\n", 35, "IPC Messages Sent:", 
        myProcess.ru_msgsnd);
      printf ("%*s %li\n", 35, "IPC Messsages Received:", 
        myProcess.ru_msgrcv);
      printf ("%*s %li\n", 35, "Signals Received:", 
        myProcess.ru_nsignals);
    */
    printf ("%*s %li\n", 35, "Voluntary Context Switches:", 
      myProcess.ru_nvcsw);
    printf ("%*s %li\n", 35, "Involuntary Context Switches:",
      myProcess.ru_nivcsw);

    sleep (1);
  }


  return 0;
}

void printHeader () {
  for (int i = 1; i <= 80; i++) {
    printf ("*");
  }
  printf ("\n");
}