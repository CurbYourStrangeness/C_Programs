#include "queue.h"

float *create_q(const int size)
{
  float* darr = (float)malloc(sizeof(float) * size);
  return darr;
}


float* add_q(float* arr1, float test, int tail, int capacity)
{
  arr1[tail] = test;
  tail = tail +1;
  if(full_check(tail, capacity) == 0)
  {  
  double_q(arr1, capacity);
  }
  return arr1;
}

float* rem_q(float* arr1, int tail, int capacity)
{
  int t;
  int cycle = tail;
  for(t = 0; t < cycle; ++t)
  {
  arr1[t] = arr1[t+1];
  }
  tail = tail -1;
  if(half_check(tail, capacity) != 0)
  {
  shrink_q(arr1, capacity);
  }
  return arr1;
}

float* double_q(float* arr1, int capacity)
{
  float* tmp = (float*)malloc(sizeof(float) * (capacity * 2));
  capacity = capacity * 2;
  int i;
  for(i = 0; i < capacity; ++i)
  {
   tmp[i] = (arr1)[i];
  }
  free(arr1);
  arr1 = tmp;
  return arr1;
}

float* shrink_q(float* arr1, int capacity)
{
 float* tmp = (float*)malloc(sizeof(float) * (capacity/2))
 int i;
 for(i = 0; i < capacity; ++i)
 {
  tmp[i] = (arr1)[i];
 }
 free(arr1);
 arr1 = tmp;
 return arr1;
}

int full_check(int tail, int capacity)
{
 if(tail == capacity)
 {
  return 0;
 }
 else
 {
 return 1;
 }
}

int half_check(int tail, int capacity)
{
 if((tail * 2) == capacity)
 {  
 return 0;
 }
 else
 {
 return 1;
 }
}

int empty_check(int tail)
{
 if(tail == 0)
 {  
  return 0;
 } 
 else
 {
 return 1;
 }
}