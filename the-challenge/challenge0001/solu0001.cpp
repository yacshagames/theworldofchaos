/*
 * FMMD 3-8-2000
 * El reto
 * Por que no obtenemos:
 *
 *   La operacion se realizo:
 *   	Correctamente.
 *
 * Es muy facil?
 */

#include <stdio.h>


#define SUMA(x,y)     ((x) + (y))
#define RESTA(x,y)    ((x) - (y))
#define MUL(x,y)      ((x) * (y))
#define DIV(x,y)      ((x) / (y))


int main(void)
{
	int x, y, z;
	x = 5;
	y = 2;
	z = SUMA(DIV(x, y), MUL(x, y)) * 2;
	printf("\nLa operacion se realizo:\n");
	// ERROR
	if (z == 0) {
		printf("\n\tIncorrectamente.\n");
	}
	else {
		printf("\n\tCorrectamente.\n");
	}

	return 0;
}


