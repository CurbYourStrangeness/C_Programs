in order to run the utility, run all the below commands as per instructions in the terminal.

1) first compile the code 

	g++ main.c
		or
	gcc main.c	

2) now create an archive file of the given test files by entering the following command

	./a.out -c ./here my_archive

3) to make sure our archive was correct, delete all the files in the ./here folder and then run this command which extracts the archive file. So basically this restores the contents of the folder, contents of the newly file create in the directory should be same as before.

	./a.out -e ./here my_archive

3) To test the append, move the file file4.txt in the ./here folder and run this command!
The new file is added to the archive.

	./a.out -a ./here my_archive

You can test the authenticity of the append command by again deleting all the files in the ./here folder and then again restoring them as before by running the command
	
	./a.out -e ./here my_archive
