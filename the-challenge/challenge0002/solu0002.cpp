/*
 * Esto es muy facil.
 * Cual es el error?
 */

#include <stdio.h>


#define MAX_SIZE   32


int main(void)
{
	// ERROR
	short *buffer = malloc(sizeof(short) * MAX_SIZE);
	int i;

	for (i = 0; i < MAX_SIZE; i++)
		buffer[i] = (i % 224) + ' ';

	for (i = 0; i < MAX_SIZE; i++)
		putchar(buffer[i]);

	putchar('\n');
	return 0;
}

