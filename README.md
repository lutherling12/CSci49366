#Unix Tools (CSci493.66)
####with Adriana Wise (Spring 2015)

This repository contains assignments done for the Unix Tools, an elective at Hunter College of CUNY, or CSci493.66, taught by Professor Wise during Spring 2015.


The textbook used for this class is:
*Advanced Programming in the Unix Environment, 3rd Edition*
by W. Richard Stevens and Stephen A. Rago.


It can be found [here](http://www.amazon.com/Advanced-Programming-UNIX-Environment-Edition/dp/0321637739).

##Homework 1: myNameIs
Write a small system program that creates a file and writes your name in it,
taking your name as input from the command line. It should use the system
functions creat() and write(). For the synopsis of these functions, consult
section 2 of the man pages on your system

##Homework 2: Book List
Write a C program that replaces or inserts a row in the books.txt file. You can
specify your own row number as the row that needs to be replaced. You can supply
your own record (for instance, your favorite book and its author). The books.txt file
contains book records, each with two fields: a book title field (with no blank spaces
in it) and an author field (again, with no blank spaces in it). You should be able to
replace the record at the row number specified, with your own.

##Homework 3.1: chown
Write a small program that illustrates the use of the chown() system call on a
file.

##Homework 3.2: File Stat
Write a program that displays all the information from the stat structure about a
file in a “formatted” table, with the constant names on the left, and their binary
values on the right. In particular, the st_mode member of the stat structure,
which encodes the file type and the permissions mode, should be broken down into
the values of its components, given that each bit has a meaning. List the meanings
of each bit of st_mode and its values for your file. Convert into binary using the %
operator on the octal value of st_mode, then test against the values obtained by
selecting each bit using bitwise operations.

There are 16 bits for st_mode (no two leading 0 bits as in the mask examples):
+ 1 for set-user-ID
+ 1 for set-group-ID
+ 1 for the sticky bit
+ 4 for the file type
+ 9 for access permissions

##Homework 4: Foward Tree Walk (FTW)
Copy, adapt, and compile the program that traverses a file hierarchy from Chapter
4, Files and Directories. Taking as input a starting pathname, the program
descends the file hierarchy from that point, and returns how many files of each of
the seven types there are, and what percentage of the total that represents. (You will
need to revisit Chapter 2, UNIX Standardizations and Implementations, and
create a *.c and a *.h file for path_alloc().)

##Homework 5.1: UID
Write a program that finds all users on a system. You should test for a large
number of UID numbers, since no function returns that information wholesale.

##Homework 5.2: GID
Modify the program that returns supplementary GIDs for a user to also list
these groups’ names. 

##Homework 6: Signals
Write a simple program showing the system call sigsuspend().
Your program should initialize three sets of signals (oldset, newset, waitset) to the
empty set, using sigemptyset(). It should then add a few signals to this set, using
sigaddset(). It should contain a signal handler, which you can design to be
shared across the few signals you have added to your set. You should then specify a
set of blocked signals, using sigprocmask(). The signals you want triggered and
handled, you should set, and establish handler(s) for, using either signal() or
sigaction(). Then, you want the signals in the blocked mask to suspend until the
signals from the wait mask are triggered and return from their handler, using
sigsuspend(). After the signals in the wait mask have been delivered and
handled, unblock the suspended signals using sigprocmask() again. Insert
printouts of every point in your program where you can show the signal sets, where
the signals are raised, and where the suspended signals get unblocked.

##Homework 7: Threads 
Write a program that starts two threads writing into the same text
file. The threads should be each reading book records from the command line and
populating the text file with these records. Have each thread accumulate the record
entries from the command line into an array of strings. This should be the thread specific
data. Both threads should independently update this array of strings with
their input. By using thread-specific data, the final array of strings should be
consistent and should contain complete entries from both threads. For bonus: Have
the data entry accept as many command line entries as issued until an EOF
character is encountered. Implement this as a signal.

##Homework 8: Daemons
Write a user daemon that outputs the current time every 10 seconds
into a log file at the same level with the source code for the daemon in the directory
hierarchy. Have the configuration file redirect the log file to this place. Then change
the configuration file to output elsewhere. Send the daemon a signal telling it that
the configuration file was changed, forcing it to reread it and start sending the log
messages at the new location.