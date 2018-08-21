For this assignment, you need only write a single-file C program (You must also include a Makefile with your submission however).  Your program will:
Perform the functions of a simple shell (command line interpreter) by repeating the following:
Display a simple command line prompt, that includes the absolute path of the current working directory of the parent process (  /home/USERS/rds ? )
Once the user responds - read in the users' single line of input ( directive )
Parse the directive
If the directive is exit your shell program ends
If the directive is not exit your shell program must (for each underlying UNIX command – see Multi below):
fork a child process, that uses an exec... call to handle the underlying UNIX command
wait for that child to terminate – Note: it will not return

A non-exit directive (obtained from the user via your shell's “command line”) must be:
Exactly one of the following :
<command> <arg1> ... <argn>
A single command and its command line arguments, to be executed by your shell
multi  <path/file_name>
Specifies a (text) file that exists and contains a sequence of commands (see above) to be executed (in order) by your shell.
You may assume that the file will not contain “nested” multi commands.

Proper care (error reporting / program termination) when opening, creating files and directories, and using the fork command is required.

You may not use the system() call or popen() call in this program.  You must limit your self to fork(), wait(), the exec..() family and the file handling functions we discussed in class prior to the assignment.  
 Hint on how to get the prompt path:
NAME
getcwd - get the pathname of the current working directory
SYNOPSIS
#include < HYPERLINK "http://pubs.opengroup.org/onlinepubs/009695399/basedefs/unistd.h.html"unistd.h>  char *getcwd(char *buf, size_t size);
DESCRIPTION
The getcwd() function shall place an absolute pathname of the current working directory in the array pointed to by buf, and return buf. The pathname copied to the array shall contain no components that are symbolic links. The size argument is the size in bytes of the character array pointed to by the buf argument. If buf is a null pointer, the behavior of getcwd() is unspecified.



Sample Run:

Welcome to myShell

/home/USERS/rds ? ls -l
< an ls -l listing of the files in the current working directory >

/home/USERS/rds ? multi mycoms.txt 
< the result of “iterating” the commands specified in mycoms.txt >

/home/USERS/rds ? exit


myShell out

