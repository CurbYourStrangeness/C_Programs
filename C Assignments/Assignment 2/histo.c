#include "histo.h"

void init_histogram(int histo[])
{
	int value;
	int total = NUM_DIGITS;
	for(value = 0; value < total; ++value)
	{
           histo[value] = 0;
	}
}

void cons_histogram(const char string [], int histo[])
{
	int t = 0;
	int s = strlen(string);
	while(t <= s)
	{
	   if(isdigit(string[t])){
		if(string[t] == '0')
		{
		  ++histo[0];
		}
		if(string[t] == '1')
		{
		  ++histo[1];
		}
		if(string[t] == '2')
		{
		  ++histo[2];
		}
		if(string[t] == '3')
		{
		  ++histo[3];
		}
		if(string[t] == '4')
		{
		  ++histo[4];
		}
		if(string[t] == '5')
		{
		  ++histo[5];
		}
		if(string[t] == '6')
		{
		  ++histo[6];
		}
		if(string[t] == '7')
		{
		  ++histo[7];
		}
		if(string[t] == '8')
		{
		  ++histo[8];
		}
		if(string[t] == '9')
		{
		  ++histo[9];
		}
	}
	  ++t;
	}			
}

void most_frequent(const int histo[], char* ret_val)
{
	int t = 0;
	int moi = 0;
	++t;
	int total = NUM_DIGITS;
	while(t < total)
	{
		if(histo[t] > histo[moi])
		{
		  moi = t;
		}
		++t;
	}
	*ret_val = moi + '0';
}

void display_histogram(int* const histo)
{
	int t;
	char test = '\0';
	int total = NUM_DIGITS;
	
	for(t = 0; t < total; ++t)
	{
		if(histo[t] > 1)
		{
		 char index = t + '0';
		 char value = histo[t] + '0';
		 printf("%c appeared %c times\n", index, value);
		}
		else if(histo[t] > 0)
		{
		 char index = t+ '0';
		 char value = histo[t] +'0';
		 printf("%c appeared %c time\n", index, value);
		}
	}
	printf("\n\n");
	most_frequent(histo, &test);
	printf("%c occurred most often\n", test);

}
