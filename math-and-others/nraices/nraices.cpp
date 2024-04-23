/***********************************************************************
 NRAICES
 CALCULA TODAS LAS RAICES REALES Y COMPLEJAS DE UN POLINOMIO DE GRADO N

 AUTOR: JOSE LUIS DE LA CRUZ LAZARO
	ramondc@hotmail.com
 visita mi pagina web:
  http://www.geocities.com/SiliconValley/Screen/2767/jldl.htm
 Ahi encontraras varios programas en c++, que puedes incluir en tus
 aplicaciones.

 version 1.0 17/09/1999
 calcula todas las raices reales y complejas de un polinomio
 de grado n por el metodo de Newton en variable compleja.
 El algoritmo es sencillo: solo se encuentra una raiz cualquiera de P(x) por el Metodo de Newton, luego se divide P(x) por el metodo de Horner entre el monomio (x-raiz), obteniendo un polinomio de grado n-1, luego se vuelve a repetir la operacion con este polinomio resultante hasta llegar a un monomio.

***********************************************************************/

#include <iostream.h>
#include <math.h>
#include <conio.h>
#include <complex.h>

complex fx(int iter, complex x, int n, double A[]) {
	if (n != 0)return A[iter] * pow(x, n) + fx(iter + 1, x, n - 1, A);
	else return A[iter];
}

complex fder(int iter, complex x, int n, double A[]) {
	if (n != 0)return A[iter] * n*pow(x, n - 1) + fder(iter + 1, x, n - 1, A);
	else return 0;
}

//divide 2 polinomios Pm Qn por el metodo de Horner
double *horner(int iter, int m, int n, double P[], double Q[], double D[]) {

	int i;

	double a = P[0] / Q[0], tmp[30];
	D[iter] = a;

	for (i = 0; i < n; i++)tmp[i] = a * Q[i];
	for (i = n; i < m; i++)tmp[i] = 0;

	for (i = 0; i < m; i++)P[i] = P[i] - tmp[i];

	i = 1;
	while (!P[i]) {
		D[++iter] = 0;
		i++;
	}

	int k;

	m = m - i;

	for (k = 0; k < m; k++)P[k] = P[k + i];

	if (m >= n)horner(iter + 1, m, n, P, Q, D);

}


void main()
{


	clrscr();
	int m, i, j;
	double A[30];
	cout << "Ingrese grado del polinomio: "; cin >> m;
	cout << "\nIngrese los coefiecientes comenzando por Cn hasta Co:";
	cout << "\nP(x)=Cnx^n+Cn-1x^n-1+....+Co ; es decir x^3-x+8 = 1 0 -1 -8\n\n";
	for (i = 0; i <= m; i++) {
		cout << "Ingrese C" << m - i << " : "; cin >> A[i];
	}


	double *P, D[30][30];
	int k, n;

	P = A;

	int filaD = 0;	//Escoge la fila en que se va a llenar los valores de los
			//coeficientes del polinomio cociente
	do {

		complex x = complex(1, 1);	//Valor inicial para iteracion de NEWTON R.
					//UTILIZANDO ALGEBRA COMPLEJA

		//NEWTON R. COMPLEJO
		for (j = 0; j < 1000; j++)x = x - fx(0, x, m, P) / fder(0, x, m, P);

		//SE CONSTRUYE EL POLINOMIO Q CON LAS RAICES HALLADAS, QUE DIVIDIRA A P
		double Q[30];

		//APROXIMACION DE LAS RAICES A CERO
		if (fabs(real(x)) < 1e-10)x = complex(0, imag(x));
		if (fabs(imag(x)) < 1e-10)x = complex(real(x), 0);

		//ANALISIS DE LAS RAICES
		if (fabs(imag(x)) == 0) {//la raiz es real
			n = 1;
			Q[0] = 1;
			Q[1] = -real(x);
			cout << "\nRaiz de P(x): " << x;
		}
		else {//la raiz es imaginaria
			n = 2;
			Q[0] = 1;
			Q[1] = -2 * real(x);//real(-(x+conj(x)));
			Q[2] = norm(x);//real(x*conj(x));
			cout << "\nRaiz de P(x): " << x << "\nRaiz de P(x): " << conj(x);
		}

		horner(0, m + 1, n + 1, P, Q, D[filaD]);
		m = m - n;

		P = D[filaD];

		filaD++;
	} while (m > 0);

	getch();

}
