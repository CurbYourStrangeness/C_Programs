#include "Hmwrk1-1.h"

int main() 
{
	printf("\n\n");
	int inThis = 0;
	while (inThis <= 1)
	{
		printf("Enter an integer greater than 1: ");
		scanf("%d", &inThis);
	}
	printf("\n\n");

  	int power;
	int prime = 2; // first prime number
	while (inThis >= prime)
	{
		if (inThis % prime == 0)
		{
			power = factor_power(inThis, prime);
			inThis /= (int)pow(prime, power);
			printf("%d^%d * ", prime, power);
		}

		++prime;
	}
	printf("1");
	printf("\n\n");
	return 0;
}
