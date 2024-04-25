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
 Convierte un número Arabigo (numeración ordinaria) de 4 cifras
 a números Romanos.

 Ejemplo:
 Si ingreso 59 y retorna LIX.

Programmed by:

	JOSE LUIS DE LA CRUZ LAZARO
	ramondc@hotmail.com

	UNIVERSIDAD NACIONAL DE INGENIERIA
	Faculty of Electrical and Electronic Engineering
	Lima-Peru

	YACSHA - Software & Desing
	>> The World of chaos - EL MUNDO DEL CAOS - Unlimited Programming

 HISTORY...

 >> Version 2 - 19-IV-2024
	- Update math-and-others\aratorom - Porting to VC++ 2017 using winbgi
	- It merges with the aratorom project with romtoara, to convert
	  from Arabic to Roman numerals and vice versa in a single program
	- Update code to C++17
	- The program is translated from Spanish to English.

 >> Version 1 - 31-X-2000
	- First version for Borland C++ 3.1 and Turbo C 3.0

***********************************************************************/

#include <iostream>
#include <string>

using std::cout;
using std::cin;

std::string aratorom_1unit(const unsigned int& cifra, const unsigned int& orden) {

	char  ui, um, uf;
	std::string roman;

	switch (orden) {

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
	}
	switch (cifra) {

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

std::string aratorom(const unsigned int& N) {

	unsigned int a, b, c, d;

	d = N % 10;
	c = N % 100 / 10;
	b = N % 1000 / 100;
	a = N / 1000;

	return	aratorom_1unit(a, 3) + 
			aratorom_1unit(b, 2) +
			aratorom_1unit(c, 1) +
			aratorom_1unit(d, 0);

}

int romtoara_2unit(const int& cifraIZQ, const int& cifraDER)
{
	if (cifraIZQ >= cifraDER)
		return cifraIZQ;
	else
		return -cifraIZQ;
}

//retorna el equivalente decimal de la cifra romana ingresada
unsigned int romtoara_1unit(const char& cifraROMANA)
{
	switch (cifraROMANA)
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

	cout << ":: ROMAN TO ARABIC NUMBERS CONVERTER ::" << std::endl << std::endl;

	cout << "1) Arabic to Roman" << std::endl;
	cout << "2) Romans to Arabic" << std::endl << std::endl;
	cout << "Enter an option: ";
	cin >> option;

	cout << std::endl;

	if (option == 1) {
		
		cout << "Enter an Arabic number: ";
		cin >> arabicNumber;

		cout << std::endl;
		cout << "The Roman equivalent is: " << aratorom(arabicNumber);

	}
	else {

		cout << "Enter an Arabic number: ";
		cin >> romanNumber;

		cout << std::endl;
		cout << "The Arabic equivalent is: " << romtoara(romanNumber);
	}

	cout << std::endl;
	
	return 1;
}

