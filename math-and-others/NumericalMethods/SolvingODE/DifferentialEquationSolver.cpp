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
	- The visualization of the x and y calculation tables is improved,
	  in each method, always showing the values in the range [a, b]
	- A chronometer is added to measure the time that each method takes,
	  and the seconds that each method has taken to process the solution
	  are shown, in order to obtain a point of comparison between the
	  efficiency of the algorithms.
	- The ShowSolutions method is added to display the solutions after
	  the numerical method algorithm code has finished. In such a way
	  that the time of each algorithm can be measured correctly and
	  then display the results on the screen.
	- The FormulaParser library is added to define an ODE y'=f(x,y) from
	  a text string entered by the user, and in this way the user will
	  be able to customize the ODE equation that will be solved by the
	  numerical methods implemented.
	- Added ExampleOfUse to the "Enter ODE: y' = f(x,y)" option, to inform
	  the user how to enter the formulation of the mathematical function

  >> Version 1 - 30-XI-1999
	- First version for Borland C++ 3.1 and Turbo C 3.0

**********************************************************************/
#include <iostream>
#include <string>
#include "conio.h"
#include "Menu.h"
#include "AddOns.h"
#include "FormulaParser.h"

using namespace std;

// NUMERICAL METHODS FOR SOLVING ORDINARY DIFFERENTIAL EQUATIONS - ODEs
class CNumericalMethodsSolvingODE{
	struct Solution {
		double x = 0;
		double y = 0;
		double k1 = 0;
		double k2 = 0;
		double k3 = 0;
		double k4 = 0;
		unsigned int iterations;
	};

public:

	CNumericalMethodsSolvingODE();
	~CNumericalMethodsSolvingODE();

private:
	double f(double x, double y);

public:

	void InitVariables();
	void InitODE();
	void VisualizeSystem();

	void Euler();
	void ModifiedEuler();
	void Predictor_Corrector(int iterMax);
	void Runge_Kutta2();
	void Runge_Kutta4();

	void ShowSolutions( bool show_k1_k2=false, bool show_k3_k4 =false, bool show_iterations=false);

public:
	double fa, a, b, x, y, h;

	vector<Solution> ySolutions;

	string formulaODE;
private:

	CFormulaParser fpODE;
};

CNumericalMethodsSolvingODE::CNumericalMethodsSolvingODE()
	: fpODE("","xy")
{
	fa = 3;
	a = 1;
	b = 2;
	x = a;
	y = b;
	h = 0.1;

	unsigned int ySolutionsSize = static_cast<unsigned int>(std::ceil((b - a) / h)) + 1;
	ySolutions.resize(ySolutionsSize);
}

CNumericalMethodsSolvingODE::~CNumericalMethodsSolvingODE()
{
}

// Default Ordinary differential equation - Default ODE
double CNumericalMethodsSolvingODE::f(double x, double y)
{
	//Default ODE: y'= f(x,y) = y/x+2*x*y
	if (formulaODE.empty())
		return y / x + 2 * x*y;
	else
		return fpODE.f(x, y);
}

void CNumericalMethodsSolvingODE::InitVariables()
{
	clrscr();

	cout << "\n\tEnter Xmin = "; cin >> a;
	cout << "\tEnter Xmax = ";   cin >> b;
	cout << "\tEnter Ymin = g(Xmin) = "; cin >> fa;
	cout << "\tEnter step h = "; cin >> h;
	x = a; y = fa;

	unsigned int ySolutionsSize = static_cast<unsigned int>(std::ceil((b - a) / h)) + 1;
	ySolutions.resize(ySolutionsSize);
}

void CNumericalMethodsSolvingODE::InitODE()
{
	clrscr();

	textcolor(LIGHTGRAY);
	
	cout << "If you enter Y it will ask you to enter a string with the function f(x, y)," << endl
		<< "the processing of the algorithms will be slower, if you enter N the formula " << endl
		<< "parser will be deactivated, the default function f(x,y) = y/x + 2*x*y will be used," << endl
		<< "and the processing of the algorithms will be faster." << endl;

	textcolor(WHITE);
	cout << "\nActivate parser formula for the ODE Y/N? ";
	
	char subOption = toupper(cgetch());

	if (subOption == 'Y') {
		textcolor(LIGHTCYAN);
		cout << endl << endl << fpODE.ExampleOfUse() << endl;

		textcolor(WHITE);
		cout << "\n\tEnter ODE: y' = f(x,y) = ";
		cin >> formulaODE;
	}
	else
		formulaODE.clear();

	fpODE = CFormulaParser(formulaODE, "xy");	
}

void CNumericalMethodsSolvingODE::VisualizeSystem()
{
	clrscr();

	
	if (formulaODE.empty()) {

		cout << "ODE without formula parser: y' = f(x,y) = y/x + 2*x*y --> Unknown: y = g(x)" << endl << endl;
	}
	else {

		cout << "ODE WITH formula parser: y' = f(x,y) = " << formulaODE << " --> Unknown: y = g(x)" << endl << endl;
	}
	cout << "Xmin = " << a << endl;
	cout << "Xmax = " << b << endl;
	cout << "Ymin = f(Xmin) = " << fa << endl;
	cout << "step h = " << h << endl;

	cgetch();
}


// EULER'S METHOD
void CNumericalMethodsSolvingODE::Euler()
{
	x = a; y = fa;

	unsigned int i, nYSolutionsSize = static_cast<unsigned int>(ySolutions.size());
	for (i = 0; i < nYSolutionsSize; i++) {

		//cout << "\n\tx = " << x;
		//cout << "\t\t\ty = " << y;		
		// Store the solutions for y
		auto& ys = ySolutions[i];
		ys.x = x;
		ys.y = y;

		y = y + h * f(x, y);
		x = x + h;		
	}
}

// MODIFIED EULER METHOD (MIDPOINT METHOD)
void CNumericalMethodsSolvingODE::ModifiedEuler()
{
	x = a; y = fa;

	unsigned int i, nYSolutionsSize = static_cast<unsigned int>(ySolutions.size());
	for (i = 0; i < nYSolutionsSize; i++) {
		
		//cout << "\n\tx = " << x;
		//cout << "\t\ty = " << y;
		// Store the solutions for y
		auto& ys = ySolutions[i];
		ys.x = x;
		ys.y = y;

		y = y + h * f(x + 0.5*h, y + 0.5*h*f(x, y));
		x = x + h;
	
	}
}

// PREDICTOR - CORRECTOR METHOD - IMPROVED EULER(HEUN'S) METHOD
void CNumericalMethodsSolvingODE::Predictor_Corrector( int iterMax )
{
	double  y1, yo, error = 1e-6, k1;
	int n;

	x = a; y = fa;

	unsigned int i, nYSolutionsSize = static_cast<unsigned int>(ySolutions.size());
	for (i = 0; i < nYSolutionsSize; i++) {

		//cout << "\n\tx = " << x;
		//cout << "\t\t\ty = " << y;
		//if( x>a )
		//	cout << "\t\tIterations: " << n;

		// Store the solutions for y
		auto& ys = ySolutions[i];
		ys.x = x;
		ys.y = y;
		if(i > 0)
			ys.iterations = n;

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
		
		x = x + h;		

	}
}


// RUNGE KUTTA METHOD (ORDER 2)
void CNumericalMethodsSolvingODE::Runge_Kutta2()
{
	double k1=0, k2=0;

	x = a; y = fa;

	unsigned int i, nYSolutionsSize = static_cast<unsigned int>(ySolutions.size());
	for (i = 0; i < nYSolutionsSize; i++) {

		//if (x > a) {
		//	cout << "\n\tk1 = " << k1;
		//	cout << "\tk2 = " << k2;
		//}
		//else
		//	cout << endl;
		//cout << "\tx = " << x;
		//cout << "\ty = " << y;
		// Store the solutions for y
		auto& ys = ySolutions[i];
		ys.x = x;
		ys.y = y;
		ys.k1 = k1;
		ys.k2 = k2;		

		k1 = f(x, y);
		k2 = f(x + h, y + h * k1);

		y = y + 0.5*h*(k1 + k2);
		x = x + h;
	
	}
}

// RUNGE KUTTA METHOD (ORDER 4)
void CNumericalMethodsSolvingODE::Runge_Kutta4()
{
	double  k1=0, k2=0, k3=0, k4=0;

	x = a; y = fa;

	unsigned int i, nYSolutionsSize = static_cast<unsigned int>(ySolutions.size());
	for (i = 0; i < nYSolutionsSize; i++) {

		//if (x > a) {
		//	cout << "\n\tk1 = " << k1;
		//	cout << "\tk2 = " << k2;
		//	cout << "\tk3 = " << k3;
		//	cout << "\tk4 = " << k4;
		//}
		//else
		//	cout << endl;
		//cout << "\tx = " << x;
		//cout << "\ty = " << y;
		// Store the solutions for y
		auto& ys = ySolutions[i];
		ys.x = x;
		ys.y = y;
		ys.k1 = k1;
		ys.k2 = k2;
		ys.k3 = k3;
		ys.k4 = k4;

		k1 = f(x, y);
		k2 = f(x + 0.5*h, y + 0.5*h*k1);
		k3 = f(x + 0.5*h, y + 0.5*h*k2);
		k4 = f(x + h, y + h*k3);

		y = y + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6;
		x = x + h;
		
	}
}

void CNumericalMethodsSolvingODE::ShowSolutions(bool show_k1_k2, bool show_k3_k4, bool show_iterations)
{
	textcolor(WHITE);	

	unsigned int i, nYSolutionsSize = static_cast<unsigned int>(ySolutions.size());	

	for (i = 0; i < nYSolutionsSize; i++) {
		auto& ys = ySolutions[i];

		cout << endl;

		if (i>0) {	

			if (show_k1_k2) {
				cout << "k1 = " << ys.k1;
				cout << "\tk2 = " << ys.k2;
			}

			if (show_k3_k4) {
				cout << "\tk3 = " << ys.k3;
				cout << "\tk4 = " << ys.k4;
			}

			if (show_k1_k2 || show_k3_k4 )
				cout << '\t';
		}
		cout << "x = " << ys.x;
		cout << "\ty = " << ys.y;	

		if(show_iterations)
			cout << "\titerations = " << ys.iterations;
	}
}

int main() {

	CNumericalMethodsSolvingODE ode;
	Menu menu;

	std::vector<std::string> Metodo_Matricial = {
	"Enter initial ODE values",
	"Enter ODE: y' = f(x,y)",
	"View initial ODE values",
	"EULER",
	"MODIFIED EULER (MIDPOINT)",
	"PREDICTOR-CORRECTOR (HEUN'S)",
	"RUNGE KUTTA (ORDER2)",
	"RUNGE KUTTA (ORDER4)",
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
			
			ode.InitODE();

			break;
		case 2:

			ode.VisualizeSystem();			

			break;
		case  3:

			clrscr();
			textcolor(LIGHTCYAN);
			cout << Metodo_Matricial[opc] << endl;
			textcolor(WHITE);

			AddOns::chronoStart(); // Init chronometer			

			ode.Euler();

			AddOns::chronoEnd(); // End chronometer and show elapsed time

			ode.ShowSolutions();

			cgetch();

			break;
		case  4:

			clrscr();
			textcolor(LIGHTCYAN);
			cout << Metodo_Matricial[opc] << endl;
			textcolor(WHITE);

			AddOns::chronoStart(); // Init chronometer			
			
			ode.ModifiedEuler();

			AddOns::chronoEnd(); // End chronometer and show elapsed time

			ode.ShowSolutions();

			cgetch();

			break;
		case  5:

			clrscr();
			textcolor(LIGHTCYAN);
			cout << Metodo_Matricial[opc] << endl;
			textcolor(WHITE);

			{
				cout << "\n\nUse iterative method (Y/N)? ";
				char subOption = toupper(cgetch());

				cout << endl;

				AddOns::chronoStart(); // Init chronometer	

				ode.Predictor_Corrector(subOption != 'Y' ? 1 : 1000);

				AddOns::chronoEnd(); // End chronometer and show elapsed time
			}

			ode.ShowSolutions(false, false, true);

			cgetch();

			break;
		case  6:

			clrscr();
			textcolor(LIGHTCYAN);
			cout << Metodo_Matricial[opc] << endl;
			textcolor(WHITE);

			AddOns::chronoStart(); // Init chronometer	

			ode.Runge_Kutta2();

			AddOns::chronoEnd(); // End chronometer and show elapsed time
			
			ode.ShowSolutions(true);

			cgetch();

			break;

		case  7:

			clrscr();
			textcolor(LIGHTCYAN);
			cout << Metodo_Matricial[opc] << endl;
			textcolor(WHITE);

			AddOns::chronoStart(); // Init chronometer	

			ode.Runge_Kutta4();

			AddOns::chronoEnd(); // End chronometer and show elapsed time

			ode.ShowSolutions(true, true);

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