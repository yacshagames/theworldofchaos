/*
* This is also very easy.
* Why does the operation not give the correct value?
*
* NOTE: I learned this from a C/C++ book, which
* warned about this error;
 */

#include <iostream>

 // ERROR
#define ADD(x,y)    ((x) + (y))
#define SUB(x,y)    ((x) - (y))
#define MUL(x,y)    ((x) * (y))
#define DIV(x,y)    ((x) / (y))


int main(void)
{
	double x, y;
	x = 5;
	y = 2;
	/* (5/2+5*2)*2 = 25 */
	std::cout << "(x/y+x*y)*2 = "<< ADD(DIV(x, y), MUL(x, y)) * 2 << std::endl;
	return 0;
}
