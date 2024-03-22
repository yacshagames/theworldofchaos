/****************************************************************
GRAFICAD - Function Plotter for DOS

JOSE LUIS DE LA CRUZ LAZARO UNI - FIEE
ramondc@hotmail.com

>> Version 2 - 22 - III - 2024
- Update: Porting to VC++ 2017 using winbgi
- Unifies grafxy and grafxyz into a single program

****************************************************************/

#include <iostream>
#include "Grafxy.H"
#include "Grafxyz.H"
using namespace std;

int main()
{
	// Handle to console
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, LIGHTGREEN); // Console font color
	cout << "GRAFICAD - Function Plotter for DOS" << endl << endl;

	SetConsoleTextAttribute(hConsole, LIGHTGRAY); // Console font color
	cout << "1) Go to XY plotter (2D Plotter)" << endl;
	cout << "2) Go to XYZ plotter (3D Plotter)" << endl;
	cout << "Enter the option: ";

	int nOption;
	cin >> nOption;

	if (nOption == 1)
		grafxy();
	else
		grafxyz();
		
	return 1;
}