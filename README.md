#Unix Tools (CSci493.66)
###with Adriana Wise (Spring 2015)

This repository contains assignments done for the Unix Tools, an elective at Hunter College of CUNY, or CSci493.66, taught by Professor Wise during Spring 2015.


The textbook used for this class is:
*Advanced Programming in the Unix Environment, 3rd Edition*
by W. Richard Stevens and Stephen A. Rago.


It can be found [here](http://www.amazon.com/Advanced-Programming-UNIX-Environment-Edition/dp/0321637739).


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