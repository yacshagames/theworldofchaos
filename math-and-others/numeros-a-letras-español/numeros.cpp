/*********************************************************************
::: READING NUMBERS - Spanish ::: LECTURA DE NUMEROS - Español :::

This program reads an integer number and returns its equivalent in letters.
Ex:
If I enter 3465
the program returns "tres mil cuatrocientos sesenta y cinco"

Este programa lee un numero entero y retorna su equivalente en letras.
Ejm:
Si ingreso 3465
el programa retorna "tres mil cuatrocientos sesenta y cinco"

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

  >> Version 2 - 23-IV-2024
	- The code is updated to the new C++ 17 standard
	- The credits and version history are updated
	- Function parameters are ordered to constants, to indicate that
	  the variables passed as reference parameters will not be modified
	- Accents are removed so that the text appears correct in the
	  console window

  >> Version 1.1 - 09-II-2000
	- Se supero el error de que cuando ingresabas un numero que terminaba
	  en tres ceros, se escribia "cero" al final de la cadena.

  >> Version 1.0 - 02-XII-1999
	- Lectura de numeros menores que 100000.
	
**********************************************************************/

#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::cin;

std::vector<std::string> Unidad = {	"cero", "uno", "dos","tres","cuatro","cinco", "seis",
									"siete", "ocho", "nueve" };

std::vector<std::string> Diez = {	"diez", "once", "doce", "trece", "catorce", "quince",
									"dieciseis", "diecisiete", "dieciocho", "diecinueve" };

std::vector<std::string> Decena = { "cero","diez","veinte","treinta","cuarenta","cincuenta",
									"sesenta","setenta","ochenta","noventa" };

std::vector<std::string> Centena = {	"cien", "ciento", "doscientos", "trescientos","cuatrocientos",
										"quinientos", "seiscientos", "setecientos",
										"ochocientos", "novecientos" };
std::string Millar = "mil";

void Nombrar_Centena(const unsigned int& Num)
{
	//Num es una centena de la forma abc
	//descomponemos num en: a, b y c
	int a, b, c;
	c = Num % 10;
	b = (Num % 100 - c) / 10;
	a = (Num - 10 * b - c) / 100;

	if (a > 0)
		if (b == 0 && c == 0)       //si el Num = 100
			cout << Centena[0] << " ";
		else
			cout << Centena[a] << " "; ///si 100<Num<200


	if (b > 0)
		if (b == 1)
			cout << Diez[c] << " "; //si 10<Num<20
		else
			cout << Decena[b] << " "; //si 1<b<10

	if (c > 0)                 //imprime las unidades
	{
		if (b > 1)
			cout << "y ";
		
		if (b != 1)
			cout << Unidad[c] << " ";
	}

}

void Nombrar_Numero(const unsigned int& Num)
{
	//Num es un numero menor que 100000
	if (Num == 0)
		cout << Unidad[0]; //si Num=0
	
	if (Num < 100000) //si Num 1<
	{
		int Num_mil = (Num - Num % 1000) / 1000;
		
		if (Num_mil > 1)
			Nombrar_Centena(Num_mil);
		
		if (Num >= 1000) 
			cout << Millar << " ";
		
		Nombrar_Centena(Num % 1000);

	}else 
		cout << "Lo siento, el numero ingresado es mayor o igual a 100000";

}

int main()
{
	unsigned int Num;
	cout << "Ingrese un numero menor que 100000: ";
	cin >> Num;

	cout << "\nEl numero en letras ingresado es:\n\n";
	Nombrar_Numero(Num);

	cout << std::endl;

	return 1;

}