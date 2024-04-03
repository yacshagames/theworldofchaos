#include <iostream>
#include "conio.h"

using namespace std;

// METODO DE EULER

float Df(float x, float y)
{
	return y / x + 2 * x*y;
	// Ecuacion Diferencial y'=y/x+2*x*y
}

void Euler()
{
	float fa, a, b, x, y, h, df;
	clrscr();
	cout << "\n\tMETODO DE EULER\n";
	cout << "\n\tIngrese a = "; cin >> a;
	cout << "\tIngrese b = "; cin >> b;
	cout << "\tIngrese f(a) = "; cin >> fa;
	cout << "\tIngrese h = "; cin >> h;
	x = a; y = fa;
	do {
		y = y + h * Df(x, y);
		cout << "\n\tx = " << x;
		cout << "\t\t\ty = " << y;
		x = x + h;
	} while (x <= b + h);
	cgetch();
}

//METODO DE EULER MODIFICADO

double oper(double x, double y, double h)
{
	return y * (1 + 0.5*h*(1 / x + 2 * x)) / (1 - (1 / (x + h) + 2 * (x + h))*0.5*h);
}

void ModifiedEuler()
{
	double fa, a, b, x, y, h, df;
	clrscr();
	cout << "\n\tMETODO DE EULER MODIFICADO\n";
	cout << "\n\tIngrese a = "; cin >> a;
	cout << "\tIngrese b = ";   cin >> b;
	cout << "\tIngrese f(a) = "; cin >> fa;
	cout << "\tIngrese h = "; cin >> h;
	x = a; y = fa;
	do {
		y = oper(x, y, h);
		x = x + h;
		cout << "\n\tx = " << x;
		cout << "\t\ty = " << y;
	} while (x < b);
	cgetch();
}

// METODO DE PREDICTOR CORRECTOR

double f(double x, double y)
{
	return y / x + 2 * x*y;
	// Ecuacion Diferencial y'=y/x+2*x*y
}

void Predictor_Corrector()
{
	double fa, a, b, x, y, y1, h, df, yo, error = 1e-6;
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
		y = y + h * f(x, y);
		//CORRECTOR: EULER MODIFICADO
		do {
			y1 = y;
			y = yo + 0.5*h*(f(x, yo) + f(x + h, y));
		} while (fabs(y - y1) < error);

		cout << "\n\tx = " << x;
		cout << "\t\t\ty = " << yo;
		//		n=n+1;
		x = x + h;
	} while (x <= b + h);
	cgetch();
}


// METODO DE RUNGE KUTTA(ORDEN 2)
double f1(double x, double y)
{
	return y / x + 2 * x*y;
	// Ecuacion Diferencial y'=y/x+2*x*y
}


double K1(double h, double y, double x)
{
	return h * f1(x, y); // Ecuacion Diferencial
			   // y'=-0.4y+0.2
}
double K2(double h, double y, double x, double k1)
{
	return h * f1(x + h, y + k1);
}
void Runge_Kutta2ndOrder()
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
		k1 = K1(h, y, x);
		k2 = K2(h, y, x, k1);
		x = x + h;
		y = y + (k1 + k2) / 2;
		cout << "\n\tk1 = " << k1;
		cout << "\tk2 = " << k2;
		cout << "\tx = " << x;
		cout << "\ty = " << y;
	} while (x < b);
	cgetch();
}

int main() {
	
	Euler();
	ModifiedEuler();
	Predictor_Corrector();
	Runge_Kutta2ndOrder();

	return 1;
}