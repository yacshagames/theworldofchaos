/*********************************************************************
FOURIER

A PERIODIC FUNCTION f(t) IS TRANSFORMED INTO ITS RESPECTIVE FOURIER
SERIES (THE SAME FUNCTION BUT REPRESENTED IN A SUM OF SINES AND COSINES)

Programmed by:

	JOSE LUIS DE LA CRUZ LAZARO
	ramondc@hotmail.com

	UNIVERSIDAD NACIONAL DE INGENIERIA
	Faculty of Electrical and Electronic Engineering
	Lima-Peru

 HISTORY...

 >> Version 2 - 26-III-2024
	- Update graphics/fourier - Porting to VC++ 2017 using winbgi
	- The fourier series approximation with up to 15 terms is added 
	  for the following functions: "Step Function", "sqrt(1 - t^2)", 
	  "0.1*(t + 2)*(t + 1)* t*(t - 1)*(t - 3)" and "t^3

>> Version 1 - 8-XI-1999
	- First version for Borland C++ 3.1 and Turbo C 3.0

*********************************************************************/

//#include <conio.h>
//#include <dos.h>
#include "graphics.h"
#include "grafxy.h"
#include <string>
#include <vector>

class CSerieFourier
{

public:
	CSerieFourier();

	void ConstruirSerie(double _a, double _b, int _num_terminos = 10);
	double f(double t);

private:
	double fcos(int n, double t);
	double fsen(int n, double t);
	double Integral_f(double h);
	double Integral_fcos(int n, double h);
	double Integral_fsen(int n, double h);
	void calcular_coeficientes(void);
public:
	double evaluar_serie(double t);
	void Setnum_terminos(int _num_terminos);

private:
	double A[100], B[100]; //coeficientes de fourier
	double T; //periodo de la funcion
	double Wo; //frecuencia
	double a, b; //Intervalo periodico donde se define la funcion T=b-a
	int num_terminos;  //contiene el numero de terminos que se utilizara en
						//la serie
public:
	static unsigned int num_function;
};

unsigned int CSerieFourier::num_function = 0;

CSerieFourier::CSerieFourier() {

}

void CSerieFourier::ConstruirSerie(double _a, double _b, int _num_terminos)
{
	a = _a;
	b = _b;
	num_terminos = _num_terminos;

	T = b - a;
	Wo = (2 * M_PI) / T;
	calcular_coeficientes();
}


double CSerieFourier::f(double t)
{
	switch (CSerieFourier::num_function) {

	case 0:
		// Step Function
		if (t > 0)
			return 1;
		else
			return -1;
	case 1:
		// square root function
		if (fabs(t) <= 1)
			return sqrt(1 - t * t);
		else
			return 0;
	case 2:
		// Polynomial 4rd
		return 0.1*(t + 2)*(t + 1)*t*(t - 1)*(t - 3);
	case 3:
		// Polynomial 3rd
		return t * t * t;
	}
}


double CSerieFourier::fcos(int n, double t)
{
	return f(t)*cos(n*Wo*t);
}

double CSerieFourier::fsen(int n, double t)
{
	return f(t)*sin(n*Wo*t);
}

double CSerieFourier::Integral_f(double h)
{
	// Integra la funcion f(t)
	// por el metodo de Simpsom en [a,b]
	double xi = a, Sum = 0;
	int i = 1;
	Sum = f(a) + f(b);

	for (xi += h; xi < b; xi += (h / 2), i++)
		if (i % 2) Sum += 4 * f(xi);
		else Sum += 2 * f(xi);

	return (h / 6)*Sum;
}


double CSerieFourier::Integral_fcos(int n, double h)
{
	// Integra la funcion f(t)*cos(n*Wo*t)
	// por el metodo de Simpsom en [a,b]
	double xi = a, Sum = 0;
	int i = 1;
	Sum = fcos(n, a) + fcos(n, b);

	for (xi += h; xi < b; xi += (h / 2), i++)
		if (i % 2) Sum += 4 * fcos(n, xi);
		else Sum += 2 * fcos(n, xi);

	return (h / 6)*Sum;
}

double CSerieFourier::Integral_fsen(int n, double h)
{
	// Integra la funcion f(t)*sen(n*Wo*t)
	// por el metodo de Simpsom en [a,b]
	double xi = a, Sum = 0;
	int i = 1;
	Sum = fsen(n, a) + fsen(n, b);

	for (xi += h; xi < b; xi += (h / 2), i++)
		if (i % 2) Sum += 4 * fsen(n, xi);
		else Sum += 2 * fsen(n, xi);

	return (h / 6)*Sum;
}


void CSerieFourier::calcular_coeficientes(void)
{
	A[0] = (2 / T)*Integral_f(0.05);
	B[0] = 0;

	for (int n = 1; n <= num_terminos; n++)
	{
		A[n] = (2 / T)*Integral_fcos(n, 0.05);
		B[n] = (2 / T)*Integral_fsen(n, 0.05);
		//  cout<<A[0]<<" "; getch();
	}

}

double CSerieFourier::evaluar_serie(double t)
{
	double S = 0;
	for (int n = 1; n <= num_terminos; n++)
		S += (A[n] * cos(n*Wo*t) + B[n] * sin(n*Wo*t));
	return A[0] / 2 + S;
}


void CSerieFourier::Setnum_terminos(int _num_terminos)
{
	num_terminos = _num_terminos;
}

int main()
{
	// Init WinBGI window
	initwindow(1024, 768, "The world of chaos in C++ - Unlimited Programming");

	CRegionXY R(-4, 4, -3, 3);

	R.Ejes();

	double t;

	CSerieFourier function;

	std::vector<std::string> vFunctions = { "Step Function", "sqrt(1 - t^2)", "0.1*(t + 2)*(t + 1)*t*(t - 1)*(t - 3)", "t^3" };

	for (CSerieFourier::num_function = 0; CSerieFourier::num_function < 4; CSerieFourier::num_function++) {

		function.ConstruirSerie(-1, 1);

		for (int i = 1; i <= 15; i++)
		{
			function.Setnum_terminos(i);
			cleardevice();
			R.Ejes();

			for (t = R.xmin(); t < R.xmax(); t += 0.01) {
				R.punto(t, function.evaluar_serie(t), LIGHTGREEN/*, CONECTAR*/);
				R.punto(t, function.f(t), LIGHTRED);
			}

			std::string msg = "f(t) = " + vFunctions.at(CSerieFourier::num_function);
			outtextxy(10, 10, msg.c_str());
			outtextxy(10, 30, "Series working interval: [-1,1]");
			msg = "Number of Fourier Terms = " + std::to_string(i);
			outtextxy(10, 50, msg.c_str());
			//getch();
			delay(500);
			//return 1;
		}
	}

	getch();

	closegraph();
}