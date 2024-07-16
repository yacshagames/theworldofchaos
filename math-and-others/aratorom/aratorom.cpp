/***********************************************************************
 :: ROMAN TO ARABIC NUMBERS CONVERTER :: 
 :: CONVERTIDOR DE NUMEROS ROMANOS A ARABIGOS ::

 ROMTOARA:
 Converts a Roman numeral to an Arabic numeral (ordinary numbering).

 Example:
 If I enter LIX, it returns 59.

 ARATOROM:
 Converts a 4-digit Arabic number (ordinary numbering)
 to Roman numerals.

 Example:
 If I enter 59 and LIX returns.
 ----------------------------------------------------------------------
 ROMTOARA:
 Convierte un número Romano a un número Arabigo (numeración ordinaria).

 Ejemplo:
 Si ingreso LIX, retorna 59.

 ARATOROM:
 Convierte un nímero Arabigo (numeración ordinaria) de 4 cifras
 a números Romanos.

 Ejemplo:
 Si ingreso 59 y retorna LIX.

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
	- Update math-and-others\aratorom - Porting to VC++ 2017 using winbgi
	- It merges with the aratorom project with romtoara, to convert
	  from Arabic to Roman numerals and vice versa in a single program
	- Update code to C++17
	- The program is translated from Spanish to English.
	- The romtoara algorithm is optimized to perform the conversion within a loop
	- Update credits and version historyu in Spanish and English
	- In the aratorom GUI, a validation is added indicating that only Arabic
	  numerals less than 4000 can be entered, because the maximum Roman numeral
	  is M (1000).

 >> Version 1 - 31-X-2000
	- First version for Borland C++ 3.1 and Turbo C 3.0

***********************************************************************/

#include <iostream>
#include <string>

using std::cout;
using std::cin;

std::string aratorom_1unit(const unsigned int& digit, const unsigned int& order) {

	char  ui, um, uf;
	std::string roman;

	switch (order) {

	case 0: ui = 'I';
		um = 'V';
		uf = 'X';
		break;
	case 1: ui = 'X';
		um = 'L';
		uf = 'C';
		break;
	case 2: ui = 'C';
		um = 'D';
		uf = 'M';
		break;
	case 3: ui = 'M';
		break;
	default:
		// Arabic number should only have digits up to order 3
		return "";
	}

	// Arabic number must be less than 4000
	if( order==3 && digit>=4)
		return "";

	switch (digit) {

	case 1: roman = std::string(1,ui); break;
	case 2: roman = std::string(1, ui) + ui;  break;
	case 3: roman = std::string(1, ui) + ui + ui; break;
	case 4: roman = std::string(1, ui) + um; break;
	case 5: roman = std::string(1, um); break;
	case 6: roman = std::string(1, um) + ui; break;
	case 7: roman = std::string(1, um) + ui + ui; break;
	case 8: roman = std::string(1, um) + ui + ui + ui; break;
	case 9: roman = std::string(1, ui) + uf; break;
	}

	return roman;
}

std::string aratorom(const unsigned int& arabicNumber) {

	std::string roman;
	unsigned int digit, N = arabicNumber, order = 0;

	while (N > 0)
	{
		digit = N % 10;
		N /= 10;
		roman.insert(0, aratorom_1unit(digit, order++));
	}

	return roman;
}

int romtoara_2unit(const int& leftDigit, const int& rightDigit)
{
	if (leftDigit >= rightDigit)
		return leftDigit;
	else
		return -leftDigit;
}

//retorna el equivalente decimal de la cifra romana ingresada
unsigned int romtoara_1unit(const char& romanDigit)
{
	switch (romanDigit)
	{
	case 'I':  return 1;
	case 'V':  return 5;
	case 'X':  return 10;
	case 'L':  return 50;
	case 'C':  return 100;
	case 'D':  return 500;
	case 'M':  return 1000;
	default:  return 0;
	}
}

unsigned int romtoara(const std::string& sRomanNumber) {

	unsigned int  i, n = static_cast<unsigned int>(sRomanNumber.size()) - 1, Arab = 0;

	for (i = 0; i < n; i++)
		Arab += romtoara_2unit(romtoara_1unit(sRomanNumber[i]), romtoara_1unit(sRomanNumber[i + 1]));

	Arab += romtoara_1unit(sRomanNumber[n]);
	
	return Arab;
}


int main() {

	unsigned int arabicNumber, option;
	std::string romanNumber;

	cout << ":: ROMAN TO ARABIC NUMBERS CONVERTER ::" << std::endl;
	cout << ":: CONVERTIDOR DE NUMEROS ROMANOS A ARABIGOS ::" << std::endl << std::endl;


	cout << "1) Arabic to Roman" << std::endl;
	cout << "2) Romans to Arabic" << std::endl << std::endl;
	cout << "Enter an option: ";
	cin >> option;

	cout << std::endl;

	if (option == 1) {
		
		cout << "Enter an Arabic number: ";
		cin >> arabicNumber;

		cout << std::endl;

		if (arabicNumber<4000)
			cout << "The Roman equivalent is: " << aratorom(arabicNumber);
		else
			cout << "Enter a number less than 4000";

	}
	else {

		cout << "Enter an Roman number: ";
		cin >> romanNumber;

		cout << std::endl;
		cout << "The Arabic equivalent is: " << romtoara(romanNumber);
	}

	cout << std::endl;
	
	return 1;
}

