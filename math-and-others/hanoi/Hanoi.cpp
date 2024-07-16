/***********************************************************************
::: THE TOWERS OF HANOI ::: LAS TORRES DE HANOI :::

Classic Tower of Hanoi algorithm solved using a recursive function.
  
Clásico algoritmo de las torres de hanoi solucionado mediante una
función recursiva.

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
 >> Version 2 - 19-IV-2024
	- Update math-and-others\hanoi - Porting to VC++ 2017

>> Version 1 - 19-X-2000
	- First version for Borland C++ 3.1 and Turbo C 3.0

***********************************************************************/

#include <iostream>

using namespace std;

void Hanoi(int n, char A, char B, char C)
{
	if (n > 0)
	{
		Hanoi(n - 1, A, C, B);
		cout << "\nMover el disco " << n << " de " << A << " a " << C;
		Hanoi(n - 1, B, A, C);
	}
}

int main()
{
	int n;
	cout << "\n\nIngrese el n£mero de discos por torre: ";
	cin >> n;
	Hanoi(n, 'A', 'B', 'C');

	return 1;
}
