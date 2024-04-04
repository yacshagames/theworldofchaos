/*********************************************************************
NUMERICAL METHODS FOR SOLVING ORDINARY DIFFERENTIAL EQUATIONS - ODEs

An ordinary differential equation - ODE, is solved using the
following numerical method algorithms:

	- Euler
	- Modified Euler
	- Predictor-Corrector
	- Runge Kutta (Order2)
	- Runge Kutta (Order4)

Developed by:

	JOSE LUIS DE LA CRUZ LAZARO
	ramondc@hotmail.com

	UNIVERSIDAD NACIONAL DE INGENIERIA
	Faculty of Electrical and Electronic Engineering
	Lima-Peru

	YACSHA - Software & Desing
	>> The World of chaos - EL MUNDO DEL CAOS - Unlimited Programming

HISTORY...

  >> Version 2 - 04-IV-2024
	- Code is updated and improved
	- Merges all numerical methods that solve differential equations
	  in a single file
	- Porting to VC++ 2017
	- Translate functions name
	- Change float variables to double
	- The function y' = f(x,y) is unified into a single function that
	  is reused in all methods
	- Unused variables are eliminated
	- The ModifiedEuler and Predictor_Corrector method is corrected
	- Order 4 Runge Kutta method added
	- A menu is added in text mode to select the numerical method to
	  use in the solution
	- Unnecessary files are removed
	- The code is modernized, converting it into the
	  CNumericalMethodsSolvingODE class
	- Traces of old C function fabs, etc... are removed and replaced
	  with their modern equivalents
	- The maximum width at which a menu box can be created is increased
	- Change project name to SolvingODE
	- Comments are translated from Spanish to English
	- Credits are added

  >> Version 1 - 30-XI-1999
	- First version for Borland C++ 3.1 and Turbo C 3.0

**********************************************************************/
#include <iostream>
#include "conio.h"
#include "Menu.h"

using namespace std;

// NUMERICAL METHODS FOR SOLVING ORDINARY DIFFERENTIAL EQUATIONS - ODEs
class CNumericalMethodsSolvingODE{

public:

	CNumericalMethodsSolvingODE();
	~CNumericalMethodsSolvingODE();

private:
	double f(double x, double y);

public:

	void InitVariables();
	void Visualize_System();

	void Euler();
	void ModifiedEuler();
	void Predictor_Corrector(int iterMax);
	void Runge_Kutta2();
	void Runge_Kutta4();

public:
	double fa, a, b, x, y, h;
};

CNumericalMethodsSolvingODE::CNumericalMethodsSolvingODE()
{
	fa = 0;
	a = 0;
	b = 1;
	x = a;
	y = b;
	h = 0.1;
}

CNumericalMethodsSolvingODE::~CNumericalMethodsSolvingODE()
{
}

// Default Ordinary differential equation - Default ODE
double CNumericalMethodsSolvingODE::f(double x, double y)
{
	//Default ODE: y'= f(x,y) = y/x+2*x*y
	return y / x + 2 * x*y;	
}

void CNumericalMethodsSolvingODE::InitVariables()
{
	clrscr();

	cout << "\n\tIngrese a = "; cin >> a;
	cout << "\tIngrese b = ";   cin >> b;
	cout << "\tIngrese f(a) = "; cin >> fa;
	cout << "\tIngrese h = "; cin >> h;
	x = a; y = fa;
}

void CNumericalMethodsSolvingODE::Visualize_System()
{
	clrscr();

	cout << "ODE: y' = f(x,y) = y/x + 2*x*y" << endl << endl;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	cout << "f(a) = " << fa << endl;
	cout << "h = " << h << endl;

	cgetch();
}


// EULER'S METHOD
void CNumericalMethodsSolvingODE::Euler()
{
	x = a; y = fa;
	do {
		y = y + h * f(x, y);
		x = x + h;
		cout << "\n\tx = " << x;
		cout << "\t\t\ty = " << y;		
	} while (x <= b);
}

// MODIFIED EULER METHOD (MIDPOINT METHOD)
void CNumericalMethodsSolvingODE::ModifiedEuler()
{

	x = a; y = fa;
	do {

		y = y + h * f(x + 0.5*h, y + 0.5*h*f(x, y));

		x = x + h;
		cout << "\n\tx = " << x;
		cout << "\t\ty = " << y;
	} while (x < b);
}

// PREDICTOR - CORRECTOR METHOD - IMPROVED EULER(HEUN'S) METHOD
void CNumericalMethodsSolvingODE::Predictor_Corrector( int iterMax )
{
	double  y1, yo, error = 1e-6, k1;
	int n;

	x = a; y = fa;
	do {
		//PREDICTOR: EULER
		yo = y;
		k1 = f(x, yo);
		y = y + h * f(x, y);
		
		//CORRECTOR: EULER MEJORADO
		n = 0;
		do {

			y1 = y;
			y = yo + 0.5*h*(k1 + f(x + h, y));

		} while (	std::abs(y - y1) > error && 
					++n < iterMax );
		cout << "\t"<<n;
		cout << "\n\tx = " << x;
		cout << "\t\t\ty = " << yo;
		x = x + h;

	} while (x <= b + h);
}


// RUNGE KUTTA METHOD (ORDER 2)
void CNumericalMethodsSolvingODE::Runge_Kutta2()
{
	double k1, k2;

	x = a; y = fa;
	do {

		k1 = f(x, y);
		k2 = f(x + h, y + h * k1);

		y = y + 0.5*h*(k1 + k2);
		x = x + h;

		cout << "\n\tk1 = " << k1;
		cout << "\tk2 = " << k2;
		cout << "\tx = " << x;
		cout << "\ty = " << y;
	} while (x < b);
}

// RUNGE KUTTA METHOD (ORDER 4)
void CNumericalMethodsSolvingODE::Runge_Kutta4()
{
	double  k1, k2, k3, k4;

	x = a; y = fa;
	do {

		k1 = f(x, y);
		k2 = f(x + 0.5*h, y + 0.5*h*k1);
		k3 = f(x + 0.5*h, y + 0.5*h*k2);
		k4 = f(x + h, y + h*k3);

		y = y + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6;
		x = x + h;

		cout << "\n\tk1 = " << k1;
		cout << "\tk2 = " << k2;
		cout << "\tk3 = " << k3;
		cout << "\tk4 = " << k4;
		cout << "\tx = " << x;
		cout << "\ty = " << y;
	} while (x < b);
	cgetch();
}

int main() {

	CNumericalMethodsSolvingODE ode;
	Menu menu;

	std::vector<std::string> Metodo_Matricial = {
	"Enter initial ODE values",
	"Enter ODE: y' = f(x,y)",
	"View initial ODE values",
	"Euler",
	"Modified Euler",
	"Predictor-Corrector",
	"Runge Kutta (Order2)",
	"Runge Kutta (Order4)",
	"Exit" }; //menu initialization

	// Init constans project
	char opc = 0;
	clrscr();
	while (opc != -1)
	{
		clrscr();
		menu.DrawBox(12, 6, 71, 17, LIGHTBLUE);
		gotoxy(14, 8);
		textcolor(LIGHTRED);
		cout << "NUMERICAL METHODS FOR SOLVING ORDINARY DIFFERENTIAL EQUATIONS - ODEs";
		textcolor(LIGHTGREEN);
		gotoxy(56, 24);
		cout << "Developed by Yacsha Software";
		opc = menu.DrawOptions(Metodo_Matricial, 20, 11, 15); // create the options menu
		gotoxy(1, 1);


		// Init matrix W from Wo
		//if (msle.Initialize_Work_Matrix() == false)
		//	if (opc != 0 && opc != 1 && opc != 7)
		//		continue;	// Does not execute numeric methods		

		switch (opc)
		{
		case 0:

			ode.InitVariables();			

			break;
		case 1:
			

			break;
		case 2:

			ode.Visualize_System();			

			break;
		case  3:

			clrscr();
			cout << Metodo_Matricial[opc];

			ode.Euler();

			cgetch();

			break;
		case  4:

			clrscr();
			cout << Metodo_Matricial[opc];

			ode.ModifiedEuler();

			cgetch();

			break;
		case  5:

			clrscr();
			cout << Metodo_Matricial[opc];

			ode.Predictor_Corrector(50);
			
			cgetch();

			break;
		case  6:

			clrscr();
			cout << Metodo_Matricial[opc];

			ode.Runge_Kutta2();


			cgetch();

			break;

		case  7:

			clrscr();
			cout << Metodo_Matricial[opc];

			ode.Runge_Kutta4();


			cgetch();

			break;
		case -1:
		case  8:

			clrscr();
			gotoxy(25, 12);
			cout << "Are you sure you want to leave Y/N?: ";
			opc = toupper(cgetch());
			if (opc == 'Y')
				opc = -1;

			break;
		}
	}

	return 1;
}