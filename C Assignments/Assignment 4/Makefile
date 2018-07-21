driver: main.o list1.o
	gcc list1.o main.o -o driver

main.o: main.c
	gcc -Wall -c main.c

list1.o: list1.c list.h
	gcc -Wall -c list1.c

clean:
	rm *.o
	rm driver
