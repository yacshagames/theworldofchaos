/***********************************************************************
 ::: PRIME NUMBER - NUMERO PRIMO :::
  
Program that determines if an entered number is a prime number.

Programa que determina si un número ingresado es un número primo.

Developed by:

	JOSE LUIS DE LA CRUZ LAZARO
	contact@theworldofchaos.com

	YACSHA - Software & Desing, since 1999, Lima-Peru
	>> The World of Chaos - EL MUNDO DEL CAOS - Unlimited Programming
	www.theworldofchaos.com

LICENSE
	This file is released under the terms of the BSD 3-Clause License.
	Read LICENSE.txt file for more information.

HISTORY...

 >> Version 2 - 24-IV-2024
	- Update math-and-others\prime - Porting to VC++ 2017
	- Update code to C++17
	- To determine the prime number the modified Eratosthenes Algorithm
	  is now used. Only go through odd numbers to speed up the calculation
	- It works with unsigned long long values, which allows the program
	  to work with natural numbers less than or equal to 18446744073709551615
	- The program GUI informs if the number entered is greater than the
	  maximum supported value
	- If the number entered is not prime, the first divisor found is
	  displayed.

 >> Version 1.0 - 17-IV-2001
	- First version for Borland C++ 3.1 and Turbo C 3.0

***********************************************************************/

#include <iostream>
#include <limits>

using std::cout;
using std::cin;

int main()
{
	unsigned long long N, k=0, sqroot, first_divisor;

	cout << "Enter a natural number: ";
	if (!(cin >> N)) {
		cout << std::endl << "The value entered must be less than " 
			 << std::numeric_limits<unsigned long long>::max() << std::endl;
		return 2;
	}


	// YOU FIND OUT IF A NUMBER IS PRIME USING THE
	// ERATOSTENES ALGORITHM

	// Square root of the number to analyze
	sqroot = (unsigned long long)std::sqrt(N);


	// Definition: 
	// N will be a prime, if it is only divisible by N or by unity.

	// Eratostenes Algorimth modified
	// Only go through odd numbers to speed up the calculation	

	if (N % 2 != 0) { // First check if the number is even

		// Check all odd numbers from 3 to the square root of N
		for (k = 3; N%k && k <= sqroot; k += 2);

		// Get a first divisor
		first_divisor = k;

	} else
		// First divisor is 2
		first_divisor = 2;

	// If the previous loop is not traversed completely (k <= sqroot)
	// then the number is prime
	bool bIsNotPrime = (k <= sqroot);
	cout << std::endl << "The number " << (bIsNotPrime ? "is not" : "is") << " prime" << std::endl;

	if(bIsNotPrime)
		// Se muestra el primer divisor de N
		cout << "The first divisor found is: " << first_divisor << std::endl;

	return 1;

}
