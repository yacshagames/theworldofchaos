#include <iostream>
#include <list>
#include "conio.h"
#include "Menu.h"
#include "FormulaParser.h"
#include "AddOns.h"

using namespace std;

class CNumericalIntegration {

	struct Solution {
		double x = 0;
		double y = 0;
		unsigned int iterations = 0;
		double error = 0.0;
	};
	
public:
	CNumericalIntegration();
	~CNumericalIntegration();


	double f(double x);

	void TrapezoidalRule();
	void SimpsonsRule();

	void InitVariables();
	void InitFunction();

	void VisualizeSystem();
	void ShowSolutions();

public:

	// Root solutions
	list<Solution> rootSolutions;

	string formulaFX; // Formula for the function f(x)
private:

	double a, b, I;
	unsigned int n;

	CFormulaParser fpFX;
};

CNumericalIntegration::CNumericalIntegration()
	: fpFX("", "x")
{
	a = 0;
	b = 10;
	n = 1000.0;
	I = 0.0;
}

CNumericalIntegration::~CNumericalIntegration()
{
}

//METODO DE EL TRAPECIO
double CNumericalIntegration::f(double x)
{
	if (formulaFX.empty())
		// Deault f(x) =  exp(-x^2) / sqr(2 * 3.141592)
		return exp(-x * x) / sqrt(2 * 3.141592);
	else
		return fpFX.f(x);
}

void CNumericalIntegration::TrapezoidalRule()
{
	double fa, fb, h, x;
	
	h = (b - a) / double(n);
	x = a + h; I = 0;
	do {
		I = I + f(x);
		x = x + h;
	} while (x < b);
	fa = f(a); fb = f(b);
	I = h * (fa + 2 * I + fb) / 2;

}


//METODO DE SIMPSON
void CNumericalIntegration::SimpsonsRule()
{
	double fx1, fx2, I, h, x1, x2, fa, fb, I1, I2;
	
	h = (b - a) / double(n);
	x1 = a + h; x2 = a + 2 * h; I1 = 0; I2 = 0;
	do {
		fx1 = f(x1);
		I1 = I1 + 4 * fx1;
		x1 = x1 + 2 * h;
	} while (x1 < b);
	do {
		fx2 = f(x2);
		I2 = I2 + 2 * fx2;
		x2 = x2 + 2 * h;
	} while (x2 < b);
	fa = f(a); fb = f(b);
	I = h * (fa + I1 + I2 + fb) / 3;
}


void CNumericalIntegration::InitVariables()
{
	textcolor(WHITE);
	clrscr();

	int _n;

	cout << "\n\tEnter a = "; cin >> a;
	cout << "\tEnter b = ";   cin >> b;
	cout << "\tEnter the number of divisions: n = "; cin >> _n;

	if (n > 0) {
		n = double(_n);
	}
	else {
		textcolor(LIGHTRED);
		cout << "\n\nThe 'n' must be a number greater than zero";
		cgetch();
	}
}

void CNumericalIntegration::InitFunction()
{
	clrscr();

	textcolor(LIGHTGRAY);

	cout << "If you enter Y it will ask you to enter a string with the function f(x)," << endl
		<< "the processing of the algorithms will be slower, if you enter N the formula " << endl
		<< "parser will be deactivated, the default function f(x) = exp(-x^2) / sqr(2 * 3.141592) will be used," << endl
		<< "and the processing of the algorithms will be faster." << endl;

	textcolor(WHITE);
	cout << "\nActivate parser formula for the f(x) Y/N? ";

	char subOption = toupper(cgetch());

	if (subOption == 'Y') {
		textcolor(LIGHTCYAN);
		cout << endl << endl << fpFX.ExampleOfUse() << endl;

		textcolor(WHITE);
		cout << "\n\tEnter f(x) = ";
		cin >> formulaFX;
	}
	else
		formulaFX.clear();

	fpFX = CFormulaParser(formulaFX, "x");
}

void CNumericalIntegration::VisualizeSystem()
{
	clrscr();

	if (formulaFX.empty()) {

		cout << "f(x) without formula parser: f(x) = exp(-x^2) / sqr(2 * 3.141592)  --> Unknown: x" << endl << endl;
	}
	else {

		cout << "f(x) WITH formula parser: f(x) = " << formulaFX << " --> Unknown: x" << endl << endl;
	}

	cout << "\n";
	textcolor(YELLOW);
	cout << "Interval [a,b] where you want to search for the root = [ " << std::defaultfloat << a << " , " << b << " ]";
	cout << "\n\n";
	textcolor(LIGHTRED);
	cout << "umber of divisions: n = " << std::defaultfloat << n;
	cgetch();
}

void CNumericalIntegration::ShowSolutions()
{
	textcolor(WHITE);
	cout << "\n\tIntegral I = " << I;	

}


int main() {

	CNumericalIntegration ni;
	Menu menu;

	vector<string> numericalIntegration = {
		"Enter initial values",
		"Enter f(x) function",
		"View initial values",
		"TRAPEZOIDAL RULE",
		"SIMPSON'S RULE",		
		"Exit" }; //inicializacion del menu

	char opc = 0; //definicion de variables	

	clrscr();
	while (opc != -1)
	{
		clrscr();
		menu.DrawBox(12, 6, 52, 17, YELLOW);
		gotoxy(14, 8);
		textcolor(LIGHTCYAN);
		cout << "NUMERICAL INTEGRATION";
		gotoxy(23, 9);
		cout << "f(x) = " << (ni.formulaFX.empty() ? "exp(-x^2) / sqr(2 * 3.141592)" : ni.formulaFX);
		textcolor(LIGHTGREEN);
		gotoxy(37, 24);
		cout << "Developed by Yacsha Software";

		opc = menu.DrawOptions(numericalIntegration, 20, 11, WHITE);//se crea el menu de opciones

		switch (opc)
		{
		case 0:
			ni.InitVariables();
			break;

		case 1:
			ni.InitFunction();
			break;

		case 2:
			ni.VisualizeSystem();
			break;

		case -1:
		case  5:
			clrscr();
			gotoxy(25, 12);
			cout << "Are you sure you want to leave Y/N?: ";

			if (toupper(cgetch()) == 'Y')
				opc = -1;
			else
				opc = 0;

			break;

		}

		if (opc > 2)
		{
			clrscr();
			ni.rootSolutions.clear();
			cout << numericalIntegration[opc] << endl;

			bool ShowY = false;
			AddOns::chronoStart(); // Init chronometer	

			switch (opc)
			{
			case 3: ni.TrapezoidalRule(); break;
			case 4: ni.SimpsonsRule(); break;			
			}

			AddOns::chronoEnd(); // End chronometer and show elapsed time

			ni.ShowSolutions();
			cgetch();
		}

	}
	return 1;
}