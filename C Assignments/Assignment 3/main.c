#include queue.h

int main()
{
	int size = 1;
	int capacity = size;
	int tail = 0;
	int cycle1;
	int cycle2;
	int cycle3;	

	float* arr1 = create_q(size);
	float test = 3.14f;
	float test2 = 4.13f;

	add_q(arr1, test, tail, capacity);
	
	for(cycle1 = 0; cycle1 <= tail; ++cycle1)
	{
	printf("%f,", arr1[cycle1]);
	}
	
	add_q(arr1, test2, tail, capacity);
	
	for(cycle2 = 0; cycle2 <= tail; ++cycle2)
	{
	printf("%f,", arr1[cycle2]);
	}
	printf("\n\n");
	
	int out = empty_check(tail);
	if(out != 0)
	{
	rem_q(arr1, tail, capacity);
	}
	
	for(cycle3 = 0; cycle3 <= tail; ++cycle3)
	{		
	printf("%f,", arr1[cycle3]);
	}	
	printf("\n\n");
	return 0;
}