/*
* FMMD 3-8-2000
* The challenge
* Why don't we get:
*
* The operation was performed:
* Correctly.
*
* Is it very easy?
 */

#include <iostream>


#define SUMA(x,y)     ((x) + (y))
#define RESTA(x,y)    ((x) - (y))
#define MUL(x,y)      ((x) * (y))
#define DIV(x,y)      ((x) / (y))


int main(void)
{
	double x, y, z;
	x = 5;
	y = 2;
	z = SUMA(DIV(x, y), MUL(x, y)) * 2;
	std::cout << "\nLa operacion se realizo:\n";
	if (z == 0) {
		std::cout << "\n\tIncorrectamente.\n";
	}
	else {
		std::cout << "\n\tCorrectamente.\n";
	}

	return 0;
}
