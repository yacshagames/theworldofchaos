#include "conio.h"
#include <iostream>
#include <string>
using std::cout;

//Float Text Class
class CTF {

public:
	int x, y, xant, yant;
	CTF(const std::string& Texto);
	void Desplazar(int x, int y);

private:
	std::string texto;
	int longitud;
};

CTF::CTF(const std::string&  Texto) {	
	texto = Texto;
	longitud = texto.length();
	xant = yant = 1;
}

void CTF::Desplazar(int x, int y) {
	gotoxy(xant, yant);
	for (int i = 0; i < longitud; i++)
		cout << " ";
	gotoxy(xant = x, yant = y);
	cout << texto;
}

void EfectText(CTF *texto)
{
	int x, y;
	for (y = 1, x = 1; y <= 12; y++, x += 3) {
		texto[0].Desplazar(40, y);
		texto[1].Desplazar(x+3, 13);
		texto[2].Desplazar(80 - x-3, 13);
		Sleep(100);
	}

	for (y = 1, x = 1; y <= 11; y++, x += 3) {
		texto[3].Desplazar(x, 14);
		texto[4].Desplazar(40, 25 - y);
		texto[5].Desplazar(80 - x, 14);
		Sleep(80);
	}
}

int main()
{
	CTF texto[6] = { CTF("The"), CTF("C++"), CTF("Language"),
					 CTF("Is"), CTF("The"), CTF("Best!!!") };

	char tecla;
	do
	{
		clrscr();
		EfectText(texto); //show the effect
		gotoxy(10, 25);
		cout << "RETURN: Exit";
		gotoxy(52, 25);
		cout << "SPACE: Repeat...";

		do //only ENTER and SPACE keys are filtered
			tecla = cgetch();
		while (tecla != 13 && tecla != 32);

	} while (tecla != 13); //Exit with ENTER

	return 0;
}