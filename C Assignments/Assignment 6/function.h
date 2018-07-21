
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct 
{
char* name;
int list_len;
float* value_list;	
}sample;


void construct_output(FILE* arr1, sample* samples[]);

void print_structs(sample* samples[]);

void write_func(sample* samples[]);

void read_for_out();

void free_it(sample* samples[]);