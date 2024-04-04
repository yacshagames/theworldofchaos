#include <iostream>
#include "conio.h"

using namespace std;

// METODO DE EULER

double f(double x, double y)
{
	// Ecuacion Diferencial y'=y/x+2*x*y
	return y / x + 2 * x*y;	
}

void Euler()
{
	double fa, a, b, x, y, h;
	clrscr();
	cout << "\n\tMETODO DE EULER\n";
	cout << "\n\tIngrese a = "; cin >> a;
	cout << "\tIngrese b = "; cin >> b;
	cout << "\tIngrese f(a) = "; cin >> fa;
	cout << "\tIngrese h = "; cin >> h;
	x = a; y = fa;
	do {
		y = y + h * f(x, y);
		x = x + h;
		cout << "\n\tx = " << x;
		cout << "\t\t\ty = " << y;		
	} while (x <= b);
	cgetch();
}

//METODO DE EULER MODIFICADO

double oper(double x, double y, double h)
{
	return y * (1 + 0.5*h*(1 / x + 2 * x)) / (1 - (1 / (x + h) + 2 * (x + h))*0.5*h);
}

void ModifiedEuler()
{
	double fa, a, b, x, y, h, k1, k2;
	clrscr();
	cout << "\n\tMETODO DE EULER MODIFICADO\n";
	cout << "\n\tIngrese a = "; cin >> a;
	cout << "\tIngrese b = ";   cin >> b;
	cout << "\tIngrese f(a) = "; cin >> fa;
	cout << "\tIngrese h = "; cin >> h;
	x = a; y = fa;
	do {
		//y = oper(x, y, h);

		//Predictor-corrector
		//k1 = f(x, y);
		//k2 = f(x + h, y + h * k1);
		//y = y + 0.5*h*(k1 + k2);

		// Euler modificado (Método del punto medio)
		//y = (y + 0.5*h*f(x, y)) / (1 - f(x + h, y + h) / (y + h)*0.5*h);

		y = y + h * f(x + 0.5*h, y + 0.5*h*f(x, y));

		x = x + h;
		cout << "\n\tx = " << x;
		cout << "\t\ty = " << y;
	} while (x < b);
	cgetch();
}

// METODO DE PREDICTOR CORRECTOR (Improved Euler (Heun's) Method Calculator)
/*
double f(double x, double y)
{
	// Ecuacion Diferencial y'=y/x+2*x*y
	return y / x + 2 * x*y;
	
}*/

void Predictor_Corrector( int iterMax )
{
	double fa, a, b, x, y, y1, h, yo, error = 1e-6, k1;
	int n = 1;
	clrscr();
	cout << "\n\tMETODO DE PREDICTOR CORRECTOR\n";
	cout << "\n\tIngrese a = "; cin >> a;
	cout << "\tIngrese b = "; cin >> b;
	cout << "\tIngrese f(a) = "; cin >> fa;
	cout << "\tIngrese h = "; cin >> h;
	x = a; y = fa;
	do {
		//PREDICTOR: EULER
		yo = y;
		k1 = f(x, yo);
		y = y + h * f(x, y);
		//CORRECTOR: EULER MODIFICADO
		int nn = 0;
		do {

			y1 = y;
			y = yo + 0.5*h*(k1 + f(x + h, y));

		} while (	fabs(y - y1) > error && 
					++nn < iterMax );
		cout << "\t"<<nn;
		cout << "\n\tx = " << x;
		cout << "\t\t\ty = " << yo;
		//		n=n+1;
		x = x + h;
	} while (x <= b + h);
	cgetch();
}


// METODO DE RUNGE KUTTA(ORDEN 2)
/*double f1(double x, double y)
{
	// Ecuacion Diferencial y'=y/x+2*x*y
	return y / x + 2 * x*y;	
}

double K1(double h, double y, double x)
{
	return h * f(x, y); // Ecuacion Diferencial
						// y'=-0.4y+0.2
}
double K2(double h, double y, double x, double k1)
{
	return h * f(x + h, y + k1);
}*/

void Runge_Kutta2()
{
	double fa, a, b, x, y, h, k1, k2;
	clrscr();
	cout << "\n\tMETODO DE RUNGE KUTTA (ORDEN 2)\n";
	cout << "\n\tIngrese a = ";  cin >> a;
	cout << "\tIngrese b = ";    cin >> b;
	cout << "\tIngrese f(a) = "; cin >> fa;
	cout << "\tIngrese h = ";    cin >> h;
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
	cgetch();
}


void Runge_Kutta4()
{
	double fa, a, b, x, y, h, k1, k2, k3, k4;
	clrscr();
	cout << "\n\tMETODO DE RUNGE KUTTA (ORDEN 4)\n";
	cout << "\n\tIngrese a = ";  cin >> a;
	cout << "\tIngrese b = ";    cin >> b;
	cout << "\tIngrese f(a) = "; cin >> fa;
	cout << "\tIngrese h = ";    cin >> h;
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
	
	//Euler();
	//ModifiedEuler();
	Predictor_Corrector(50);
	Runge_Kutta2();
	Runge_Kutta4();

	return 1;
}