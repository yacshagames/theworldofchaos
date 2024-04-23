#include"fstream.h"
#include"conio.h"

int a[30], n;

int MCD()
{

	int S = 1, i, j, salir;

	for (i = 0; i < n; i++)
		if (a[i] == 1) { salir = 1; break; }
		else salir = 0;

	i = 2;

	if (!salir) {

		while (S != 0) {
			S = 0;
			for (j = 0; j < n; j++)
				S += a[j] % i;
			i++;
		}
		i--;

		if (!S) {
			for (j = 0; j < n; j++)
				a[j] /= i;
			return i * MCD();
		}

	}
	else return 1;

}

void main()
{
	clrscr();
	int i;
	cout << "Ingrese n:"; cin >> n;

	cout << "Ingrese los numeros: ";

	for (i = 0; i < n; i++)
		cin >> a[i];

	cout << "El MCD es :" << MCD();
	getch();
}