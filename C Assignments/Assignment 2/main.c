#include "histo.h"

int main(int args, char *argv[])
{
	int histo[NUM_DIGITS];
	
	if (args == 2)
	{
	init_histogram(histo);
	cons_histogram(argv[1], histo);
	display_histogram(histo);
	}
	else
	exit(1);

	return 0;
}