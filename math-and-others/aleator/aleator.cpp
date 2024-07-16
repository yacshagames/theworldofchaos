/***********************************************************************
::: DEFINING OUR OWN RANDOM FUNCTION :::

Three different ways to define a function that returns random numbers,
in the same style as the random function. This is a great way to
define random if your compiler does not have the random
function (non-ANSI C).

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
	- Update math-and-others\aleator - Porting to VC++ 2017 using winbgi

>> Version 1 - 25-V-2001
	- First version for Borland C++ 3.1 and Turbo C 3.0

***********************************************************************/

#include <iostream>
#include <time.h>

using namespace std;

int main()
{
	//1ra forma ( Sugerida por un seguidor de The World of Chaos )

	long N, No = 2254, X;
	do
		N = (No++,       //Incrementamos la semilla
			N = No * No,   // elevamos N al cuadrado
			X = N / 100L, // quitamos las 2 últimas cifras
			X - (X / 10000L) * 10000L); //quitamos las 2 primeras cifras
	while (N < 1000); //mientras N<1000

	cout << "\nAleatorio 1: " << N;

	//2da forma (similar al algoritmo de random )
	//(genera un pseudoaletorio en funcion del tiempo actual,
	// comprendido entre 1000 y 9999

	N = 1000 + (long)time(NULL) % 9000;

	cout << "\nAleatorio 2: " << N;

	//3ra forma (la que mas me gusta, a pesar de ser mas lenta)
	//( Una combinacion de ambos metodos )

	No = 1000 + (long)time(NULL) % 9000; //semilla

	do
		N = (No++,       //Incrementamos la semilla
			N = No * No,   // elevamos N al cuadrado
			X = N / 100L, // quitamos las 2 ultimas cifras
			X - (X / 10000L) * 10000L); //quitamos las 2 primeras cifras
	while (N < 1000); //mientras N<1000

	cout << "\nAleatorio 3: " << N;

	return 1;
}
