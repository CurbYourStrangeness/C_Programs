
soln: histo.o main.o
	gcc histo.o main.o -o soln

histo.o: histo.h histo.c
	gcc -c -Wall histo.c

main.o: histo.h main.c
	gcc -c -Wall main.c
