#include <iostream>
#include "conio.h"
#include "Menu.h"

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
}

//METODO DE EULER MODIFICADO

double oper(double x, double y, double h)
{
	return y * (1 + 0.5*h*(1 / x + 2 * x)) / (1 - (1 / (x + h) + 2 * (x + h))*0.5*h);
}

void ModifiedEuler()
{
	double fa, a, b, x, y, h, k1, k2;

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
	/*
	Euler();
	ModifiedEuler();
	Predictor_Corrector(50);
	Runge_Kutta2();
	Runge_Kutta4();
	*/

	//CDifferentialEqSolver des;
	Menu menu;

	std::vector<std::string> Metodo_Matricial = {
	"EULER",
	"EULER MODIFICADO",
	"PREDICTOR-CORRECTOR",
	"RUNGE KUTTA (ORDEN 2)",
	"RUNGE KUTTA (ORDEN 4)",
	"Exit" }; //menu initialization

	// Init constans project
	char opc = 0;
	clrscr();
	while (opc != -1)
	{
		clrscr();
		menu.DrawBox(12, 6, 57, 16, 9);
		gotoxy(14, 8);
		textcolor(LIGHTRED);
		cout << "MATRIX METHODS FOR SOLVING SYSTEMS OF LINEAR EQUATIONS";
		textcolor(LIGHTGREEN);
		gotoxy(42, 23);
		cout << "Developed by Yacsha Software";
		opc = menu.DrawOptions(Metodo_Matricial, 20, 11, 15); // create the options menu
		gotoxy(1, 1);


		// Init matrix W from Wo
		//if (msle.Initialize_Work_Matrix() == false)
		//	if (opc != 0 && opc != 1 && opc != 7)
		//		continue;	// Does not execute numeric methods

		switch (opc)
		{
		/*case 0:

			if (msle.SetNumberUnknownsVariables())
				msle.Enter_System();

			break;
		case 1:
			if (msle.SetNumberUnknownsVariables()) {

				textcolor(LIGHTGRAY);
				cout << "\nIf you create a diagonally dominant matrix, it can be successfully processed" << endl;
				cout << "by the Cholesky and Gauss-Seidel algorithms." << endl << endl;

				textcolor(WHITE);
				cout << "Generate diagonally dominant matrix (Y/N)? ";
				char subOption = toupper(cgetch());

				msle.GenerateRandomMatrices(subOption == 'Y');
			}

			break;
		case 2:

			msle.Visualize_System();

			break;*/
		case  0:

			clrscr();
			cout << Metodo_Matricial[opc];

			Euler();

			cgetch();

			break;
		case  1:

			clrscr();
			cout << Metodo_Matricial[opc];

			ModifiedEuler();

			cgetch();

			break;
		case  2:

			clrscr();
			cout << Metodo_Matricial[opc];

			Predictor_Corrector(50);
			
			cgetch();

			break;
		case  3:

			clrscr();
			cout << Metodo_Matricial[opc];

			Runge_Kutta2();


			cgetch();

			break;

		case  4:

			clrscr();
			cout << Metodo_Matricial[opc];

			Runge_Kutta4();


			cgetch();

			break;
		case -1:
		case  5:

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