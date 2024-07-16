/****************************************************************
GRAFICAD - Function Plotter for DOS

2D and 3D Function plotter.

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

>> Version 2 - 22-III-2024
	- Update: Porting to VC++ 2017 using winbgi
	- Unifies grafxy (2D Plotter) and grafxyz (3D Plotter)
	  into a single program

>> Version 1 - 26-VI-1999
	- First version for Borland C++ 3.1 and Turbo C 3.0
	- GrafXY version 1.1 is developed
	- GrafXYZ version 1.2 is developed

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