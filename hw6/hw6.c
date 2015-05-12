/*Wait3() is considered "obsolete" and waitpid/waitid are suggested 
alternatives, but  the assignment calls for usage of wait3() due to
collection of resource usage (rusage) of the child(?) process.*/

//Removes "implicit declaration" warning for kill().
#define _POSIX_SOURCE
//Removes "implicit declaration" warning for vfork() and wait3().
#define _BSD_SOURCE

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
void printSig (int);

int main (int argc, char ** argv)
{
  struct rusage myProcess;
  int ret;
  int status = 0;
  int errNo = 0;
  pid_t childPID;

  /*Signal 9 (SIGKILL) and Signal 17, 19, 23 (SIGSTOP) are buggy 
  and do not produce output, because, according to man 7 signal:
  "The signals SIGKILL and SIGSTOP cannot be caught, blocked, or ignored."*/

  for (int i = 1; i <= 255; i++) {
    //If child
    if ((ret = fork ()) == 0) {
      printf ("%s %i\t", "Iteration:", i);
      childPID = getpid();
      //printf ("%s %li\t", "Child PID:", (long int)getpid());
      
      signal (i, printSig);
      errNo = kill(childPID, i);
      printf ("%s %i\t", "ErrNo:", errNo);

      exit(0);
    }
    //Else parent 
    else {
      sleep (1);
      kill(ret, SIGCONT);
      wait3 (&status, 0, &myProcess);
      getrusage (RUSAGE_CHILDREN, &myProcess);
      //printHeader();

      printf ("%s %li\n", "User CPU Time (sec):", myProcess.ru_utime.tv_usec);
    /*
        Other fields are disabled because time is retrieved
        and is sufficient for proof of concept.
      printf ("%*s %li\n", 35, "System CPU Time (sec):",
        myProcess.ru_stime.tv_sec);
      printf ("%*s %li\n", 35, "Maximum Resident Set Size (kB):",   
        myProcess.ru_maxrss);
      printf ("%*s %li\n", 35, "Integral Shared Memory Size (kB):", 
        myProcess.ru_ixrss);
      printf ("%*s %li\n", 35, "Integral Unshared Data Size (kB):", 
        myProcess.ru_idrss);
      printf ("%*s %li\n", 35, "Integral Unshared Stack Size (kB):", 
        myProcess.ru_isrss);
      printf ("%*s %li\n", 35, "Page Reclaims:", 
        myProcess.ru_minflt);
      printf ("%*s %li\n", 35, "Page Faults:", 
        myProcess.ru_nswap);
      printf ("%*s %li\n", 35, "Swaps:", 
        myProcess.ru_inblock);
      printf ("%*s %li\n", 35, "Block Input Operations:", 
        myProcess.ru_oublock);
      printf ("%*s %li\n", 35, "IPC Messages Sent:", 
        myProcess.ru_msgsnd);
      printf ("%*s %li\n", 35, "IPC Messsages Received:", 
        myProcess.ru_msgrcv);
      printf ("%*s %li\n", 35, "Signals Received:", 
        myProcess.ru_nsignals);
      printf ("%*s %li\n", 35, "Voluntary Context Switches:", 
        myProcess.ru_nvcsw);
      printf ("%*s %li\n", 35, "Involuntary Context Switches:",
        myProcess.ru_nivcsw);
    */

    }

  }

  return 0;
}

void printHeader () {
  for (int i = 1; i <= 80; i++) {
    printf ("*");
  }
  printf ("\n");
}

void printSig (int signum) {
  switch (signum) {
    case SIGABRT:
      printf("%*s %i\n", 25, "SIGABRT: ", SIGABRT);
      break;
    case SIGALRM:
      printf("%*s %i\n", 25, "SIGALRM: ", SIGALRM);
      break;
    case SIGBUS:
      printf("%*s %i\n", 25, "SIGBUS: ", SIGBUS);
      break;
    case SIGCHLD:
      printf("%*s %i\n", 25, "SIGCHLD: ", SIGCHLD);
      break;
    case SIGCONT:
      printf("%*s %i\n", 25, "SIGCONT: ", SIGCONT);
      break;
    case SIGFPE:
      printf("%*s %i\n", 25, "SIGFPE: ", SIGFPE);
      break;
    case SIGHUP:
      printf("%*s %i\n", 25, "SIGHUP: ", SIGHUP);
      break;
    case SIGILL:
      printf("%*s %i\n", 25, "SIGILL: ", SIGILL);
      break;
    case SIGINT:
      printf("%*s %i\n", 25, "SIGINT: ", SIGINT);
      break;
    case SIGIO:
      printf("%*s %i\n", 25, "SIGIO: ", SIGIO);
      break;
    case SIGKILL:
      printf("%*s %i\n", 25, "SIGKILL: ", SIGKILL);
      break;
    case SIGPIPE:
      printf("%*s %i\n", 25, "SIGPIPE: ", SIGPIPE);
      break;
    case SIGPROF:
      printf("%*s %i\n", 25, "SIGPROF: ", SIGPROF);
      break;
    case SIGPWR:
      printf("%*s %i\n", 25, "SIGPWR: ", SIGPWR);
      break;
    case SIGQUIT:
      printf("%*s %i\n", 25, "SIGQUIT: ", SIGQUIT);
      break;
    case SIGSEGV:
      printf("%*s %i\n", 25, "SIGSEGV: ", SIGSEGV);
      break;
    case SIGSTKFLT:
      printf("%*s %i\n", 25, "SIGSTKFLT: ", SIGSTKFLT);
      break;
    case SIGSTOP:
      printf("%*s %i\n", 25, "SIGSTOP: ", SIGSTOP);
      break;
    case SIGSYS:
      printf("%*s %i\n", 25, "SIGSYS: ", SIGSYS);
      break;
    case SIGTERM:
      printf("%*s %i\n", 25, "SIGTERM: ", SIGTERM);
      break;
    case SIGTRAP:
      printf("%*s %i\n", 25, "SIGTRAP: ", SIGTRAP);
      break;
    case SIGTSTP:
      printf("%*s %i\n", 25, "SIGTSTP: ", SIGTSTP);
      break;
    case SIGTTIN:
      printf("%*s %i\n", 25, "SIGTTIN: ", SIGTTIN);
      break;
    case SIGTTOU:
      printf("%*s %i\n", 25, "SIGTTOU: ", SIGTTOU);
      break;
    case SIGURG:
      printf("%*s %i\n", 25, "SIGURG: ", SIGURG);
      break;
    case SIGUSR1:
      printf("%*s %i\n", 25, "SIGUSR1: ", SIGUSR1);
      break;
    case SIGUSR2:
      printf("%*s %i\n", 25, "SIGUSR2: ", SIGUSR2);
      break;
    case SIGVTALRM:
      printf("%*s %i\n", 25, "SIGVTALRM: ", SIGVTALRM);
      break;
    case SIGWINCH:
      printf("%*s %i\n", 25, "SIGWINCH: ", SIGWINCH);
      break;
    case SIGXCPU:
      printf("%*s %i\n", 25, "SIGXCPU: ", SIGXCPU);
      break;
    case SIGXFSZ:
      printf("%*s %i\n", 25, "SIGXFSZ: ", SIGXFSZ);
      break;
  /*
    //The following signals are undefined or (if noted) duplicates.
    case SIGCANCEL:
      printf("%*s %i\n", 25, "SIGCANCEL: ", SIGCANCEL);
      break;
    case SIGEMT:
      printf("%*s %i\n", 25, "SIGEMT: ", SIGEMT);
      break;
    case SIGFREEZE:
      printf("%*s %i\n", 25, "SIGFREEZE: ", SIGFREEZE);
      break;
    case SIGINFO:
      printf("%*s %i\n", 25, "SIGINFO: ", SIGINFO);
      break;
    //SIGIOT is equal to SIGABRT on Ubuntu 14.04.
    case SIGIOT:
      printf("%*s %i\n", 25, "SIGIOT: ", SIGIOT);
      break;
    case SIGJVM1:
      printf("%*s %i\n", 25, "SIGJVM1: ", SIGJVM1);
      break;
    case SIGJVM2:
      printf("%*s %i\n", 25, "SIGJVM2: ", SIGJVM2);
      break;
    case SIGLOST:
      printf("%*s %i\n", 25, "SIGLOST: ", SIGLOST);
      break;
    case SIGLWP:
      printf("%*s %i\n", 25, "SIGLWP: ", SIGLWP);
      break;
    //SIGPOLL is equal to SIGIO on Ubuntu 14.04.
    case SIGPOLL:
      printf("%*s %i\n", 25, "SIGPOLL: ", SIGPOLL);
      break;
    case SIGTHAW:
      printf("%*s %i\n", 25, "SIGTHAW: ", SIGTHAW);
      break;
    case SIGTHR:
      printf("%*s %i\n", 25, "SIGTHR: ", SIGTHR);
      break;
    case SIGWAITING:
      printf("%*s %i\n", 25, "SIGWAITING: ", SIGWAITING);
      break;
    case SIGXRES:
      printf("%*s %i\n", 25, "SIGXRES: ", SIGXRES);
      break;
  */
    default:
      printf("%*s %i\n", 25, "Undefined Signal: ", signum);
      break;
  }
}