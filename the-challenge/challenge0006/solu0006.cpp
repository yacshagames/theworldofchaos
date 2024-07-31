/* Can you find the error? */
/* It's very easy */
/* To solve it you have to make some small changes */

#include <iostream>

int main()
{
	int num1, num2;
	long long result;
	num1 = 500000;
	num2 = 300000;
	result = (long long)num1 * num2;
	std::cout << "Result = " << result;

	return 0;
}