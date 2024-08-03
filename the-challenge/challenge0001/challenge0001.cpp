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


#define ADD(x,y)    ((x) + (y))
#define SUB(x,y)    ((x) - (y))
#define MUL(x,y)    ((x) * (y))
#define DIV(x,y)    ((x) / (y))


int main(void)
{
	int x, y, z;
	x = 5;
	y = 2;
	z = ADD(DIV(x, y), MUL(x, y)) * 2;
	std::cout << "\nThe operation was performed:\n";
	if (z=!0) {
		std::cout << "\n\tIncorrectly.\n";
	}
	else {
		std::cout << "\n\tSuccessfully.\n";
	}

	return 0;
}