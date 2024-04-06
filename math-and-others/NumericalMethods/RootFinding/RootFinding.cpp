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
#ifdef max
#undef max
#endif
#include <algorithm>

using namespace std;

class CRootFinding {
	struct Solution {
		double x = 0;
		double y = 0;
		unsigned int iterations = 0;
		double error = 0.0;
	};

public:
	CRootFinding();
	~CRootFinding();

	double f(double x);
	double g(double x);
	double fderivada(double x);

	// METHOD (1 VARIABLE)
	double Newton_Raphson();
	double Bisection();
	void False_Position();
	void Secant();
	void Fixed_Point();

	// NEWTON METHOD(2 VARIABLES)
	double F(double x, double y);
	double G(double x, double y);
	double Fx(double x, double y);
	double Fy(double x, double y);
	double Gx(double x, double y);
	double Gy(double x, double y);
	void Newton2Variables(double x, double y);

	void InitVariables();
	//void InitFunction();
	void VisualizeSystem();
	void SaveSolutions(const unsigned int& iteration, const double& currentError, const double& x, const double& y = 0 );
	void ShowSolutions(bool ShowY=false);

public:

	// parameters for numerical methods
	double xmin, xmax, Xo, error;

	// Root solutions
	list<Solution> rootSolutions;
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
	double x = Xo, currentError;

	double x_anterior;

	unsigned int iteration = 1;

	do
	{
		x_anterior = x;
		x = x - f(x) / fderivada(x);

		currentError = std::abs(x - x_anterior);
		SaveSolutions(iteration++, currentError, x);

	} while (currentError > error);

	return x;

}

//Metodo de la bisecci¢n
double CRootFinding::Bisection()
{
	double a = xmin, b = xmax, currentError;

	double m;
	unsigned int iteration = 1;
	do
	{
		m = (a + b) / 2;
		if (f(a)*f(m) < 0)b = m;
		else a = m;
		
		currentError = std::abs(a - b);
		SaveSolutions(iteration++, currentError, (a + b) / 2);

	} while (currentError > error);

	return (a + b) / 2;
}

//Metodo de la falsa posici¢n
void CRootFinding::False_Position()
{
	double a = xmin, b = xmax, currentError;

	double x1, x2, fa, fx2;
	unsigned int iteration = 1;
	x2 = a;
	do
	{
		x1 = x2;
		x2 = a - (b - a)*f(a) / (f(b) - f(a));
		fa = f(a);
		fx2 = f(x2);
		if ((fa*fx2) > 0) a = x2; else b = x2;

		currentError = std::abs(x2 - x1);
		SaveSolutions(iteration++, currentError, x2);

	} while (currentError > error);
}

//Metodo de la secante
void CRootFinding::Secant()
{
	double x1 = xmin, x2 = xmax, currentError;

	double fx1, fx2, x;
	unsigned int iteration = 1;
	do
	{
		fx1 = f(x1); fx2 = f(x2);
		x = x2 - fx2 * (x2 - x1) / (fx2 - fx1);
		x1 = x2; x2 = x;
		
		currentError = std::abs(x2 - x1);
		SaveSolutions(iteration++, currentError, x2);

	} while (currentError > error);
}

void CRootFinding::Fixed_Point()
{
	double x = Xo, currentError;

	double x1;
	unsigned int iteration = 1;
	do
	{
		x1 = x;
		x = g(x);

		currentError = std::abs(x1 - x);
		SaveSolutions(iteration++, currentError, x);

	} while (currentError > error);
}

//-----------------------------------------------------------------
// NEWTON METHOD(2 VARIABLES)
// If you have 2 functions: F(x,y)=0 and G(x,y)=0, you can find
// the solution sets (x,y) that simultaneously verify this pair
// of equations using this method
// Example for:
//  F(x) = xy^2-y-2 = 0 and  G(x) = x^3y-6x-9 = 0

double CRootFinding::F(double x, double y)
{
	//  F(x) = xy^2-y-2 = 0
	return x * y*y - y - 2;          
}									
double CRootFinding::G(double x, double y)
{
	//  G(x) = x^3y-6x-9 = 0
	return x*x*x * y - 6 * x - 9;
}
double CRootFinding::Fx(double x, double y)
{
	// Fx = d/dx( F(x,y) ) = y^2 // partial derivative of F(x,y) with respect to x
	return y * y;
}
double CRootFinding::Fy(double x, double y)
{
	// Fy = d/dy( F(x,y) ) = 2xy-1 // partial derivative of F(x,y) with respect to y
	return 2 * x * y - 1;
}
double CRootFinding::Gx(double x, double y)
{
	// Gx = d/dx( G(x,y) ) = 3x^2y-6 // partial derivative of G(x,y) with respect to x
	return 3 * x*x*y - 6;
}
double CRootFinding::Gy(double x, double y)
{
	// Gy = d/dy( G(x,y) ) = x^3 // partial derivative of G(x,y) with respect to y
	return x * x * x;
}
void CRootFinding::Newton2Variables(double x, double y)
{		
	/*------------------------------------------------------
	
	J=  Jacobian matrix (matrix of partial derivatives of F and G)
	
	J = | dF/dx dF/dy |
		| dG/dx dG/dy |
	
	J^-1 = inverse of the Jacobian matrix

       k+1      k       k     k      
	|x|   =  |x|  + J^-1 * |F|       .... Newton Raphson for 2 variables algorimth
	|y|      |y|           |G|

	If

	f = F(x, y), g = G(x, y)
	
	Partial derivative of F(x,y) and G(x,y) with respect to x and y
	fx = d/dx (F(x, y)), fy = d/dy (F(x, y))
	gx = d/dx (G(x, y)), gy = d/dy (G(x, y))

	then

	J = | fx fy |  and J^-1 = 1 / DJ *  |  gy -fy |
		| gx gy |                       | -gx  fx |

	DJ = determinant of J
	DJ = (fx * gy - gx * fy);

	 k+1   k                     k    k
	x   = x - ( gy * f - fy * g ) / DJ

	 k+1   k                      k    k
	y   = y - ( -gx * f + fx * g ) / DJ

	------------------------------------------------------*/
	
	double f, g, fx, fy, gx, gy, x1, y1, DJ, currentError;

	unsigned int iteration = 0;	
	SaveSolutions(iteration++, 0, x, y);
	do {		
		x1 = x; y1 = y;
		f = F(x, y); g = G(x, y);
		fx = Fx(x, y); fy = Fy(x, y);
		gx = Gx(x, y); gy = Gy(x, y);
		
		DJ = (fx * gy - gx * fy);
		x = x - (  gy * f - fy * g ) / DJ;
		y = y - ( -gx * f + fx * g ) / DJ;

		currentError = std::max(std::abs(x1 - x), std::abs(y1 - y));
		SaveSolutions(iteration++, currentError, x, y);

	} while (currentError > error);


}
//-----------------------------------------------------------------

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
	cout << "Interval [a,b] where you want to search for the root = [ " << std::defaultfloat << xmin << " , " << xmax << " ]";
	cout << "\n\n";
	textcolor(LIGHTCYAN);
	cout << "For Newton's Method and Fixed Point" << endl;
	cout << "Initial value of x = " << std::defaultfloat << Xo << endl << endl;
	textcolor(LIGHTRED);
	cout << "Approximation error (in decimal value) = " << std::defaultfloat << error;
	cgetch();
}

void CRootFinding::SaveSolutions(const unsigned int& iteration, const double& currentError, const double& x, const double& y )
{
	Solution sol;
	sol.x = x;
	sol.y = y;
	sol.iterations = iteration;
	sol.error = currentError;
	rootSolutions.push_back(sol);
}

void CRootFinding::ShowSolutions(bool ShowY)
{
	textcolor(WHITE);
	cout << "\n\nRoots table:\n";

	for (auto& sol : rootSolutions) {
		cout << "\nIteration " << sol.iterations << "\tx = " << sol.x;

		if( ShowY )
			cout << "\ty = " << sol.y;

		cout << "\tError = " << sol.error;
	}

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
		"NEWTON METHOD(2 VARIABLES)",
		"Exit" }; //inicializacion del menu

	char opc = 0; //definicion de variables	

	clrscr();
	while (opc != -1)
	{
		clrscr();
		menu.DrawBox(12, 6, 52, 16, LIGHTRED);
		gotoxy(14, 8);
		textcolor(LIGHTCYAN);
		cout << "NUMERICAL METHODS FOR FINDING ROOTS OF A FUNCTION";
		gotoxy(25, 9); 
		cout << "f(x)=xtan(x)-x^2-0.168=0";

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
		case  8:
			clrscr();
			gotoxy(25, 12);
			cout << "Are you sure you want to leave Y/N?: ";
			
			if (toupper(cgetch()) == 'Y')
				opc = -1;
			else
				opc = 0;

			break;

		}

		if ( opc > 1 )
		{
			clrscr();
			rf.rootSolutions.clear();
			cout << rootFinding[opc] << endl;

			bool ShowY = false;
			AddOns::chronoStart(); // Init chronometer	
			
			switch (opc)
			{
			case 2: rf.Bisection(); break;
			case 3: rf.False_Position(); break;
			case 4: rf.Secant(); break;
			case 5: rf.Newton_Raphson(); break;
			case 6: rf.Fixed_Point(); break;
			case 7: 
			{
				textcolor(LIGHTCYAN);
				cout << endl;
				cout << "If you have 2 functions: F(x,y)=0 and G(x,y)=0, you can find" << endl;
				cout << "the solution sets (x,y) that simultaneously verify this pair" << endl;
				cout << "of equations using this method" << endl;
				cout << "Example for:" << endl;
				cout << "F(x) = xy^2-y-2 = 0 and  G(x) = x^3y-6x-9 = 0" << endl << endl;

				textcolor(LIGHTGRAY);
				cout << "Recommended test values so that they do not diverge: Xo = 4, Yo = 5" << endl;

				textcolor(WHITE);
				double x, y;
				cout << "\nEnter Xo = "; cin >> x;
				cout << "Enter Yo = "; cin >> y;

				AddOns::chronoStart(); // Init chronometer	

				rf.Newton2Variables(x, y);
				ShowY = true;
			}
			break;
			}

			AddOns::chronoEnd(); // End chronometer and show elapsed time

			rf.ShowSolutions(ShowY);
			cgetch();
		}

	}
	return 1;
}



