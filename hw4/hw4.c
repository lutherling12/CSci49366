/*The original assignment calls for a program that traverses through a file tree, determines the file type for each child, and prints the percentage of children that fit into each file type. However, this program can be found in section 4.22 of Advanced Programming in the UNIX Environment, 3rd edition written by W. Richard Stevens. Since the intent of this is to demonstrate the usage of calling ftw() through his own implementation via myftw(), dopath(), myfunc(), and path_alloc(), I will write a program that utilizes the regular ftw() found in C library.*/

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

static fn forEachChild;

static struct count {
  //There are 9 file types:
  long reg;    //Regular
  long dir;    //Directory
  long blk;    //Block Special
  long chsp;   //Character Special
  long fifo;   //FIFO
  long slink;  //Symbolic Link
  long sock;   //Socket
};

static int fn (const char *path, const struct stat * statptr, int typeflag) {
  if (typeFlag == FTW_F) {

  }
  else if (typeFlag == FTW_D) {

  }
  else if (typeFlag == FTW_DNR) {

  }
  else if (typeFlag == FTWN_NS) {

  }
}