/*********************************************************************
NUMERICAL METHODS FOR FINDING ROOTS OF A FUNCTION

Is solved using the following numerical method algorithms:

	- Bisection
	- False position
	- Secant method
	- Newton-Raphson
	- Fixed point
	
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

  >> Version 1 - 30-XI-1999
	- First version for Borland C++ 3.1 and Turbo C 3.0

**********************************************************************/
#include <iostream>
#include <string>
#include <list>
#include "conio.h"
#include "Menu.h"
#include "AddOns.h"
#include "FormulaParser.h"

using namespace std;

class CRootFinding {
	struct Solution {
		double root = 0;
		unsigned int iterations = 0;
	};

public:
	CRootFinding();
	~CRootFinding();

	double f(double x);
	double g(double x);
	double fderivada(double x);

	double Newton_Raphson();
	double Bisection();
	void False_Position();
	void Secant();
	void Fixed_Point();

	void InitVariables();
	//void InitFunction();
	void VisualizeSystem();
	void SaveSolutions(const unsigned int& iteration, const double& root);

public:

	// parameters for numerical methods
	double xmin, xmax, Xo, error;

	// Root solutions
	list<Solution> xSolutions;
};



CRootFinding::CRootFinding()
{
	xmin = 1;
	xmax = 5;
	Xo = 2;
	error = 1e-6;
}

CRootFinding::~CRootFinding()
{
}

//definicion de la funcion f(x)
double CRootFinding::f(double x)
{
	//f(x)=xtan(x)-x^2-0.168=0
	return x * tan(x) - x * x - 0.168;
}

//definicion de la funcion g(x)
//para obtener g(x) se despeja convenientemente f(x)
//de forma que quede x=g(x) donde g'(x)<1 ( derivada de g(x) <1 )
//esta funcion se utiliza en el metodo del punto fijo
double CRootFinding::g(double x)
{
	//x=g(x)=(x^2+0.168)/tan(x);
	return (x*x + 0.168) / tan(x);
}

double CRootFinding::fderivada(double x)
{	
	/*
	derivamos por definicion
	 lim  ( f(x+h)-f(x) )/h
	h->0
	*/
	double h = 1e-6;
	return (f(x + h) - f(x)) / h;

}

//Metodo de Newton-Raphson
double CRootFinding::Newton_Raphson()
{
	double x = Xo;

	double x_anterior;

	int iteracion = 1;

	do
	{
		x_anterior = x;
		x = x - f(x) / fderivada(x);		
		SaveSolutions(iteracion++, x);
	} while (fabs(x - x_anterior) > error);

	return x;

}

//Metodo de la bisecci¢n
double CRootFinding::Bisection()
{
	double a = xmin, b = xmax;

	double m;
	int iteracion = 1;
	do
	{
		m = (a + b) / 2;
		if (f(a)*f(m) < 0)b = m;
		else a = m;
		SaveSolutions(iteracion++, (a + b) / 2);
	} while (fabs(a - b) > error);

	return (a + b) / 2;
}

//Metodo de la falsa posici¢n
void CRootFinding::False_Position()
{
	double a = xmin, b = xmax;

	double x1, x2, fa, fx2;
	int iteracion = 1;
	x2 = a;
	do
	{
		x1 = x2;
		x2 = a - (b - a)*f(a) / (f(b) - f(a));
		fa = f(a);
		fx2 = f(x2);
		if ((fa*fx2) > 0) a = x2; else b = x2;
		SaveSolutions(iteracion++, x2);
	} while (fabs(x2 - x1) > error);
}

//Metodo de la secante
void CRootFinding::Secant()
{
	double x1 = xmin, x2 = xmax;

	double fx1, fx2, x;
	int iteracion = 1;
	do
	{
		fx1 = f(x1); fx2 = f(x2);
		x = x2 - fx2 * (x2 - x1) / (fx2 - fx1);
		x1 = x2; x2 = x;
		SaveSolutions(iteracion++, x2);
	} while (fabs(x2 - x1) > error);
}

void CRootFinding::Fixed_Point()
{
	double x = Xo;

	double x1;
	unsigned int iteration = 1;
	do
	{
		x1 = x;
		x = g(x);
		SaveSolutions(iteration++, x);
	} while (fabs(x1 - x) > error);
}

void CRootFinding::InitVariables()
{
	textcolor(WHITE);
	clrscr();

	cout	<< "\n\nEnter the interval [A,B] where you want to search for the root\n"
			<< "Enter A (Real Number):";
	cin >> xmin;
	cout << "Enter B (Real Number):";
	cin >> xmax;
	cout << "\n\nFor Newton's Method and Fixed Point\nEnter initial value of the root (Real Number): ";
	cin >> Xo;

	cout << "\n\nEnter the approximation error ( \"Small number\" 0<error<=0.1 ): ";
	double _error;
	cin >> _error;

	if (_error > 0) {
		error = _error;
	} else {
		textcolor(LIGHTRED);
		cout << "\n\nThe error must be a number greater than zero";
		cgetch();		
	}
}

void CRootFinding::VisualizeSystem()
{
	clrscr();
	cout << "\n\n";
	textcolor(YELLOW);
	printf("Interval [a,b] where you want to search for the root = [ %g , %g ]", xmin, xmax);
	cout << "\n\n";
	textcolor(LIGHTCYAN);
	printf("For Newton's Method and Fixed Point");
	cout << "\n";
	printf("Initial value of x = %g", Xo);
	cout << "\n\n";
	textcolor(LIGHTRED);
	printf("Approximation error (in decimal value) = %g ", error);
	cgetch();
}

void CRootFinding::SaveSolutions(const unsigned int& iteration, const double& root)
{
	//cout << "\nIteration " << iteracion << "\tRoot = " << raiz;

	Solution sol;
	sol.root = root;
	sol.iterations = iteration;
	xSolutions.push_back(sol);
}

int main()
{
	CRootFinding rf;
	Menu menu;

	vector<string> rootFinding = {
		"Enter initial values",		
		"View initial values",
		"BISECTION METHOD",
		"FALSE POSITION METHOD",
		"SECANT METHOD",
		"NEWTON-RAPHSON METHOD",
		"FIXED POINT METHOD",
		"Exit" }; //inicializacion del menu

	char opc = 0; //definicion de variables	

	clrscr();
	while (opc != -1)
	{
		clrscr();
		menu.DrawBox(12, 6, 52, 15, LIGHTRED);
		gotoxy(14, 8);
		textcolor(LIGHTCYAN);
		printf("NUMERICAL METHODS FOR FINDING ROOTS OF A FUNCTION");
		gotoxy(25, 9); printf("f(x)=xtan(x)-x^2-0.168=0");

		opc = menu.DrawOptions(rootFinding, 20, 11, WHITE);//se crea el menu de opciones

		switch (opc)
		{
		case 0:
			rf.InitVariables();
			break;

		case 1:
			rf.VisualizeSystem();
			break;

		case -1:
		case  7:
			clrscr();
			gotoxy(25, 12);
			printf("Are you sure you want to leave Y/N?: ");
			opc = toupper(cgetch());
			if (opc == 'Y')
			{
				opc = -1;
			}
			break;

		}

		if ( opc > 1 )
		{
			clrscr();
			cout << rootFinding[opc];
			cout << "\n\nTabla de Raices:\n";
			switch (opc)
			{
			case 2: rf.Bisection(); break;
			case 3: rf.False_Position(); break;
			case 4: rf.Secant(); break;
			case 5: rf.Newton_Raphson(); break;
			case 6: rf.Fixed_Point(); break;
			}
			cgetch();
		}

		/*
		if (error == 0)
		{
			textcolor(LIGHTCYAN);
			clrscr();
			gotoxy(20, 12);
			printf("Initial values have not been entered");
			gotoxy(17, 13);
			printf("Please select the option ");
			textcolor(LIGHTGREEN);
			printf("Enter initial values");
			cgetch();
		}*/

	}
	return 1;
}


//METODO DE NEWTON(2 VARIABLES)
// Si se tiene 2 funciones: F(x,y)=0 y G(x,y)=0
// se puede hallar los conjuntos de solución (x,y)
//que verifiquen simultaneamente este par de ecuaciones
//utilizando este método 

double F(double x, double y)
{
	return x * y*y - y - 2;          //  F(x) = xy^2-y-2 = 0
}                            //  G(x) = x^3y-6x-9 = 0
double G(double x, double y)
{
	return x * x*x*y - 6 * x - 9;
}
double Fx(double x, double y)
{
	return y * y;
}
double Fy(double x, double y)
{
	return 2 * y*x - 1;
}
double Gx(double x, double y)
{
	return 3 * x*x*y - 6;
}
double Gy(double x, double y)
{
	return x * x*x;
}
void Newton2Variables()
{
	double x, y, e, f, g, fx, fy, gx, gy, x1, y1;
	clrscr();
	cout << "\n\tMETODO DE NEWTON (2 VARIABLES)\n";
	cout << "\n\tIngrese Xo = "; cin >> x;
	cout << "\tIngrese Yo = "; cin >> y;
	cout << "\tIngrese Error = "; cin >> e;
	do {
		x1 = x; y1 = y;
		f = F(x, y); g = G(x, y);
		fx = Fx(x, y); fy = Fy(x, y);
		gx = Gx(x, y); gy = Gy(x, y);
		x = x + (-f * gy + g * fy) / (fx*gy - gx * fy);
		y = y + (-g * fx + gx * f) / (fx*gy - gx * fy);
		cout << "\n\tSoluci¢n X = " << x;
		cout << "\tSoluci¢n Y = " << y;
	} while (sqrt((x1 - x)*(x1 - x) + (y1 - y)*(y1 - y)) > e);
	cgetch();
}
