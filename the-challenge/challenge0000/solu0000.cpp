/*
 * Esto tambien es muy facil.
 * Por que la operacion no da el valor correcto?
 *
 * NOTA: Esto lo aprendi de un libro de C/C++, el cual
 *       avisaba sobre este error;
 */

#include <stdio.h>


 // ERROR
#define SUMA(x,y)     ((x) + (y))
#define RESTA(x,y)    ((x) - (y))
#define MUL(x,y)      ((x) * (y))
#define DIV(x,y)      ((x) / (y))


int main(void)
{
	int x, y;
	x = 5;
	y = 2;
	/* (5/2+5*2)*2 = 25 */
	printf("(x/y+x*y)*2 = %i\n", SUMA(DIV(x, y), MUL(x, y)) * 2);
	return 0;
}

