#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

float *create_q(int size);

float add_q(float* arr1[], float test, int tail, int capacity);

int full_check(int tail, int capacity);

float rem_q(float* arr1, int tail, int capacity);

int empty_check(int tail);

float* shrink_q(float* arr1, int capacity);
 
float* double_q(float* arr1, int capacity);

int half_check(int tail, int capacity);



