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

  >> Version 2 - 06-IV-2024
	- Change project name from "metodos\raices de funciones f(x)=0"
	  to "NumericalMethods\RootFinding"
	- Merges all numerical methods that Root Finding in a single file
	- Porting to VC++ 2017 using winbgi
	- Fixed some errors that prevented compilation
	- Removed old files after change project name from
	  "metodos\raices de funciones f(x)=0" to "NumericalMethods\RootFinding"
	- The code is modernized, converting it into the CRootFinding class
	- Add FormulaParser Library and AddOns Library
	- The Newton Raphson method is added to solve a system of nonlinear
	  equations with 2 unknowns
	- The FormulaParser library is added to define an y=f(x) from a
	  text string entered by the user, and in this way the user will
	  be able to customize the f(x) equation that will be solved by
	  the numerical methods implemented
	- Update version history

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
	void InitFunction();
	void VisualizeSystem();
	void SaveSolutions(const unsigned int& iteration, const double& currentError, const double& x, const double& y = 0 );
	void ShowSolutions(bool ShowY=false);

public:

	// parameters for numerical methods
	double xmin, xmax, Xo, error;

	// Root solutions
	list<Solution> rootSolutions;

	string formulaFX; // Formula for the function f(x)
private:

	CFormulaParser fpFX;
};



CRootFinding::CRootFinding()
	: fpFX("", "x")
{
	xmin = 1;
	xmax = 5;
	Xo = 1.5;
	error = 1e-6;
}

CRootFinding::~CRootFinding()
{
}

//definicion de la funcion f(x)
double CRootFinding::f(double x)
{
	if (formulaFX.empty())
		// Deault f(x) = xtan(x)- x^2 - 0.168 = 0
		return x * tan(x) - x * x - 0.168;
	else
		return fpFX.f(x);
}

// definition of the function g(x) to obtain g(x) conveniently
// solve for f(x) so that x=g(x) where 
// g'(x)<1 (derivative of g(x) <1 ) this function
// is used in the fixed point method
double CRootFinding::g(double x)
{
	//x=g(x)=(x^2+0.168)/tan(x);
	return (x*x + 0.168) / tan(x);
}

double CRootFinding::fderivada(double x)
{	
	
	// we derive by definition
	//
	// lim  ( f(x+h)-f(x) )/h
	// h->0
	
	double h = 1e-6;
	return (f(x + h) - f(x)) / h;

}

// Newton-Raphson method
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

// Bisection method
double CRootFinding::Bisection()
{
	double a = xmin, b = xmax, currentError;

	double m, fm, errormaxfx = 1e-6;
	unsigned int iteration = 1;
	do
	{
		m = (a + b) / 2;
		fm = f(m);

		if (f(a)*fm < 0)						// f(a)*f(m) < 0
			b = m;
		else if ( std::abs(fm) < errormaxfx) {	// f(n)==0
			SaveSolutions(iteration++, errormaxfx, m);
			break; // Find solution
		}
		else									// f(a)*f(m) < 0
			a = m; 
		
		currentError = std::abs(a - b);
		SaveSolutions(iteration++, currentError, (a + b) / 2);

	} while (currentError > error);

	//return (a + b) / 2;
	return m;
}

// False position method
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

// Secant method
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

// Fixed Point method
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

void CRootFinding::InitFunction()
{
	clrscr();

	textcolor(LIGHTGRAY);

	cout << "If you enter Y it will ask you to enter a string with the function f(x)," << endl
		<< "the processing of the algorithms will be slower, if you enter N the formula " << endl
		<< "parser will be deactivated, the default function f(x) = xtan(x)- x^2 - 0.168 = 0 will be used," << endl
		<< "and the processing of the algorithms will be faster." << endl;

	textcolor(WHITE);
	cout << "\nActivate parser formula for the f(x) Y/N? ";

	char subOption = toupper(cgetch());

	if (subOption == 'Y') {
		cout << "\n\tEnter f(x) = ";
		cin >> formulaFX;
	}
	else
		formulaFX.clear();

	fpFX = CFormulaParser(formulaFX, "x");
}

void CRootFinding::VisualizeSystem()
{
	clrscr();

	if (formulaFX.empty()) {

		cout << "f(x) without formula parser: f(x) = xtan(x)- x^2 - 0.168 = 0  --> Unknown: x" << endl << endl;
	}
	else {

		cout << "f(x) WITH formula parser: f(x) = " << formulaFX << " --> Unknown: x" << endl << endl;
	}

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
		"Enter f(x) function",
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
		menu.DrawBox(12, 6, 52, 17, LIGHTRED);
		gotoxy(14, 8);
		textcolor(LIGHTCYAN);
		cout << "NUMERICAL METHODS FOR FINDING ROOTS OF A FUNCTION";
		gotoxy(23, 9); 
		cout << "f(x) = " << (rf.formulaFX.empty() ? "xtan(x) -x^2 - 0.168 = 0 " : rf.formulaFX);
		textcolor(LIGHTGREEN);
		gotoxy(37, 24);
		cout << "Developed by Yacsha Software";

		opc = menu.DrawOptions(rootFinding, 20, 11, WHITE);//se crea el menu de opciones

		switch (opc)
		{
		case 0:
			rf.InitVariables();
			break;
		
		case 1:
			rf.InitFunction();
		break;

		case 2:
			rf.VisualizeSystem();
			break;

		case -1:
		case  9:
			clrscr();
			gotoxy(25, 12);
			cout << "Are you sure you want to leave Y/N?: ";
			
			if (toupper(cgetch()) == 'Y')
				opc = -1;
			else
				opc = 0;

			break;

		}

		if ( opc > 2 )
		{
			clrscr();
			rf.rootSolutions.clear();
			cout << rootFinding[opc] << endl;

			bool ShowY = false;
			AddOns::chronoStart(); // Init chronometer	
			
			switch (opc)
			{
			case 3: rf.Bisection(); break;
			case 4: rf.False_Position(); break;
			case 5: rf.Secant(); break;
			case 6: rf.Newton_Raphson(); break;
			case 7: 
				if (rf.formulaFX.empty())
					rf.Fixed_Point();
				else
					cout << "This method cannot be used when a formula for f(x) has been customized" << endl;
				break;
			case 8: 
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



