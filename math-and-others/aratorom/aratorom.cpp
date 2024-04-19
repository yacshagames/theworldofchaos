/***********************************************************************
 :::CONVERTIDOR DE ARABIGOS A ROMANOS:::

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

 >> Version 1 - 31-X-2000
	- First version for Borland C++ 3.1 and Turbo C 3.0

***********************************************************************/

#include <iostream>

using namespace std;

void transf(int cifra, int orden) {

	char  ui, um, uf;

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

	case 1: cout << ui; break;
	case 2: cout << ui << ui;  break;
	case 3: cout << ui << ui << ui; break;
	case 4: cout << ui << um; break;
	case 5: cout << um; break;
	case 6: cout << um << ui; break;
	case 7: cout << um << ui << ui; break;
	case 8: cout << um << ui << ui << ui; break;
	case 9: cout << ui << uf; break;
	}
}

int main() {

	int N, a, b, c, d;

	cout << "Ingrese un numero arabigo: "; cin >> N;

	d = N % 10;
	c = N % 100 / 10;
	b = N % 1000 / 100;
	a = N / 1000;

	transf(a, 3);
	transf(b, 2);
	transf(c, 1);
	transf(d, 0);
	
	return 1;
}
