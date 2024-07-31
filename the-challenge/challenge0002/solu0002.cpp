/*
* This is very easy.
* What is the error?
 */

#include <cstdio>
#include <stdlib.h> 


#define MAX_SIZE   32


int main(void)
{
	// ERROR
	short *buffer = (short*)malloc(sizeof(short) * MAX_SIZE);
	int i;

	for (i = 0; i < MAX_SIZE; i++)
		buffer[i] = (i % 224) + ' ';

	for (i = 0; i < MAX_SIZE; i++)
		putchar(buffer[i]);

	putchar('\n');
	return 0;
}

