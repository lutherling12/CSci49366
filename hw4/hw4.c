/*The original assignment calls for a program that traverses through 
a file tree, determines the file type for each child, and prints the 
percentage of children that fit into each file type. However, this 
program can be found in section 4.22 of Advanced Programming 
in the UNIX Environment, 3rd edition written by W. Richard Stevens. 

Since the intent of this is to demonstrate the usage of calling ftw()
through his own implementation via myftw(), dopath(), myfunc(), and 
path_alloc(), I will write a program that utilizes the regular ftw() 
found in C library.*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <dirent.h>
#include <limits.h>
#include <ftw.h>

/*From "man ftw":
To avoid using up all of the calling process's file descriptors,
nopenfd specifies the maximum number of directories that ftw() will
hold open simultaneously. When the search depth exceeds this, ftw()
will become slower because directories have to be closed and reopened.*/
#define MAXDIROPEN 4

/*From "man ftw":
For each entry found in the tree, ftw() calls fn() with three arguments: fpath, sb, and typeflag.  

fpath is the pathname of the entry, expressed either as a pathname relative to the calling process's current working directory at the time of
the call to ftw(), or as an absolute pathname. 

sb is a pointer to the stat structure returned by a call to stat(2) for fpath.  typeflag is an integer that has one of the following values:
FTW_F, FTW_D, FTW_DNR, FTW_NS.*/
typedef int fn (const char *, const struct stat *, int);
static fn countEachChild;

struct fileTypes {
  //There are 9 file types:
  long reg;    //Regular
  long dir;    //Directory
  long blk;    //Block Special
  long chsp;   //Character Special
  long fifo;   //FIFO
  long slink;  //Symbolic Link
  long sock;   //Socket
};

static struct fileTypes count = (struct fileTypes){.reg = 0, .dir = 0, .blk = 0, .chsp = 0, .fifo = 0, .slink = 0, .sock = 0};
double sum (const struct fileTypes counter) {
  return counter.reg + counter.dir + counter.blk + counter.chsp + counter.fifo + counter.slink + counter.sock;
}

static int fromPath (char *, fn *);

int main (int argc, char ** argv) 
{
  double totalFiles = 0xDEADBEEF;

  if (argc != 2) {
    printf ("Usage: prog parent_directory");
  }

  fromPath(argv[1], countEachChild);
  totalFiles = sum (count);

  printf ("\t%li (%.2f%%) were directories.\n", count.dir, (count.dir/totalFiles) * 100);
  printf ("\t%li (%.2f%%) were regular files.\n", count.reg, (count.reg/totalFiles) * 100);
  printf ("\t%li (%.2f%%) were block specials.\n", count.blk, (count.blk/totalFiles)* 100);
  printf ("\t%li (%.2f%%) were character specials.\n", count.chsp, (count.chsp/totalFiles) * 100);
  printf ("\t%li (%.2f%%) were FIFOs.\n", count.fifo, (count.fifo/totalFiles) * 100);
  printf ("\t%li (%.2f%%) were symbolic links.\n", count.slink, (count.slink/totalFiles) * 100);
  printf ("\t%li (%.2f%%) were sockets.\n", count.sock, (count.sock/totalFiles) * 100);
  printf ("\t%i files total.\n", (int)totalFiles);

  return 0;
}

static int fromPath (char * path, fn * doFunction) {
  return ftw (path, doFunction, MAXDIROPEN);
}

static int countEachChild (const char * path, const struct stat * statptr, int typeFlag) {

  if (typeFlag == FTW_F) {
    printf ("%*s", -60, path);

    switch (statptr->st_mode & S_IFMT) {
      case S_IFREG:   
        count.reg++;
        printf(" Regular file\n");
        break;
      case S_IFBLK:   
        count.blk++;
        printf(" Block Special\n");
        break;
      case S_IFCHR:
        count.chsp++;
        printf(" Character Special\n");
        break;
      case S_IFIFO:
        count.fifo++;
        printf(" FIFO\n");
        break;
      case S_IFLNK:
        count.slink++;
        printf(" Symbolic Link\n");
        break;
      case S_IFSOCK:
        count.sock++;
        printf(" Socket\n");
        break;
      case S_IFDIR:   
        printf(" Directory Error\n");
        break;
    }
  }
  else if (typeFlag == FTW_D) {
    printf ("%*s", -60, path);
    count.dir++;
    printf (" Directory\n");
  }
  else if (typeFlag == FTW_DNR) {
    printf("! ERROR Cannot access directory %s\n", path);
  }
  else if (typeFlag == FTW_NS) {
    printf("! ERROR Cannot call stat() on %s\n", path);
  }
  else {
    printf("! ERROR Unknown file type for %s\n", path);
  }

  return 0;
}