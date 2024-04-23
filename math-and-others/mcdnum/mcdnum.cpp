/***********************************************************************
 ::: GREATEST COMMON DIVISOR :::

Function to solve the greatest common divisor of a group of numbers

Programmed by:

	JOSE LUIS DE LA CRUZ LAZARO
	ramondc@hotmail.com

	UNIVERSIDAD NACIONAL DE INGENIERIA
	Faculty of Electrical and Electronic Engineering
	Lima-Peru

	YACSHA - Software & Desing
	>> The World of chaos - EL MUNDO DEL CAOS - Unlimited Programming

 HISTORY...

 >> Version 2 - 23-IV-2024
	- Update math-and-others\mcdnum - Porting to VC++ 2017

>> Version 1 - 19-IV-2000
	- First version for Borland C++ 3.1 and Turbo C 3.0

***********************************************************************/

#include <iostream>
#include <vector>

using std::cout;
using std::cin;

int GCD(std::vector<int>& a )
{

	int S = 1, i, j, salir, n = static_cast<int>(a.size());

	for (i = 0; i < n; i++)
		if (a[i] == 1){
			salir = 1;
			break;
		}else
			salir = 0;

	i = 2;

	bool ThereAreNoMoreDividers = true;

	if (!salir) {

		while (S != 0 && ThereAreNoMoreDividers) {
			S = 0;
			ThereAreNoMoreDividers = true;
			for (j = 0; j < n; j++) {
				ThereAreNoMoreDividers &= (i <= a[j]);
				S += a[j] % i;
			}

			i++;
		}
		i--;

		if ( S==0 ) {
			for (j = 0; j < n; j++)
				a[j] /= i;
			return i * GCD(a);
		}

	}	
	
	return 1;
}

int main()
{
	int i, n; 
	
	std::vector<int> a;

	cout << "GREATEST COMMON DIVISOR:" << std::endl << std::endl;

	cout << "Enter the number of numbers to calculate: ";

	cin >> n;

	a.resize(n, 0);

	cout << std::endl << "Enter the numbers:" << std::endl << std::endl;

	for (i = 0; i < n; i++) {
		cout << "Number " << i + 1 << " : ";
		cin >> a[i];
	}

	cout << std::endl << "The GCD is : " << GCD(a) << std::endl;
	

	return 1;
}