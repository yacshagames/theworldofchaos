/*
* This is very easy.
* What is the error?
 */

#include <cstdio>
#include <cstdlib> 


#define MAX_SIZE   32


int main(void)
{
	// ERROR
	short *buffer = (short*)std::malloc(sizeof(short) * MAX_SIZE);
	int i;

	for (i = 0; i < MAX_SIZE; i++)
		buffer[i] = (i % 224) + ' ';

	for (i = 0; i < MAX_SIZE; i++)
		std::putchar(buffer[i]);

	std::putchar('\n');
	return 0;
}

