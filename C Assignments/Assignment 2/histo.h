#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NUM_DIGITS 10 //number of unique "digit" characters

typedef unsigned char byte; //not used

void init_histogram(int histo[]); //set all elements of the histogram to zero

void cons_histogram(const char string[], int histo[]);

void most_frequent(const int histo[], char* ret_val);

void display_histogram(int* const histo);