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
      printf ("PID: %li\n", (long int)childPID);
      errNo++;
    }

    printf ("Maximum Resident Set Size: %li\n", 
      myProcess.ru_maxrss);
    printf ("Integral Shared Memory Size: %li\n", 
      myProcess.ru_ixrss);
    printf ("Integral Unshared Data Size: %li\n", 
      myProcess.ru_idrss);
    printf ("Integral Unshared Stack Size: %li\n", 
      myProcess.ru_isrss);
    printf ("Page Reclaims: %li\n", 
      myProcess.ru_minflt);
    printf ("Page Faults: %li\n", 
      myProcess.ru_nswap);
    printf ("Swaps: %li\n", 
      myProcess.ru_inblock);
    printf ("Block Input Operations: %li\n", 
      myProcess.ru_oublock);
    printf ("%li\n", 
      myProcess.ru_msgsnd);
    printf ("%li\n", 
      myProcess.ru_msgrcv);
    printf ("%li\n", 
      myProcess.ru_nsignals);
    printf ("%li\n", 
      myProcess.ru_nvcsw);
    printf ("%li\n", 
      myProcess.ru_nivcsw);

    sleep (1);
  }


  return 0;
}