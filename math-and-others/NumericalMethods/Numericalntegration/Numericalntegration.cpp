

//METODO DE EL TRAPECIO

#include "conio.h"
#include "fstream.h"
#include "math.h"
float f(float x)
{
	return exp(-x * x) / sqrt(2 * 3.141592);
}
void main()
{
	float fa, fb, a, b, h, x, I, n;
	clrscr();
	cout << "\tMETODO DEL TRAPECIO\n";
	cout << "\n\tIngrese a = "; cin >> a;
	cout << "\tIngrese b = "; cin >> b;
	cout << "\tIngrese n = "; cin >> n;
	h = (b - a) / n;
	x = a + h; I = 0;
	do {
		I = I + f(x);
		x = x + h;
	} while (x < b);
	fa = f(a); fb = f(b);
	I = h * (fa + 2 * I + fb) / 2;
	cout << "\n\tIntegral I = " << I;
	getch();
}





//METODO DE SIMPSON

#include "conio.h"
#include "fstream.h"
#include "math.h"
float f(float x)
{
	return exp(-x * x) / sqrt(2 * 3.141592);
}
void main()
{
	double n, fx1, fx2, a, b, I, h, x1, x2, fa, fb, I1, I2;
	clrscr();
	cout << "\n\tMETODO DE SIMPSON\n";
	cout << "\n\tIngrese a = "; cin >> a;
	cout << "\tIngrese b = ";   cin >> b;
	cout << "\tIngrese divisiones n(par) = "; cin >> n;
	h = (b - a) / n;
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
	cout << "\n\tIntegral I = " << I;
	getch();
}


