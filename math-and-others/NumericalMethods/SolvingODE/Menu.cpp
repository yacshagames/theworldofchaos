#include "Menu.h"
#include <string>
#include <iostream>
#include "conio.h"


Menu::Menu() {
}

Menu::~Menu()
{
}

int Menu::DrawOptions(std::vector<std::string>& vec, int x, int y, int col)
{
	textcolor(col);
	int k, con, dim = static_cast<int>(vec.size());
	for (k = 0; k < dim; k++) {
		gotoxy(x, y + k);
		cout << k + 1 << ") " << vec[k];
	}
	gotoxy(x, y + k + 1);
	cout << "Enter a option: ";
	cin >> con;

	return con - 1;
}


// Print a picture in console text mode
void Menu::DrawBox(int x1, int y1, int ancho, int largo, int col)
{

	if (x1 >= 0 && y1 >= 0 && (x1 + ancho) <= 128 && (y1 + largo) <= 25)
	{
		textcolor(col);
		for (int i = x1 + 1; i <= x1 + ancho - 1; i++)
		{
			gotoxy(i, y1); cout << "Í";
			gotoxy(i, y1 + largo); cout << "Í";
		}
		for (int k = y1 + 1; k <= y1 + largo - 1; k++)
		{
			gotoxy(x1, k); cout << "º";
			gotoxy(x1 + ancho, k); cout << "º";
		}
		gotoxy(x1, y1); cout << "É";
		gotoxy(x1, y1 + largo); cout << "È";
		gotoxy(x1 + ancho, y1 + largo); cout << "¼";
		gotoxy(x1 + ancho, y1); cout << "»";
	}
	else
	{
		gotoxy(x1, y1); cout << "Box off screen";
		cgetch();
	}
}

