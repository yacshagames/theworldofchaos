/***********************************************************************
:: NRAICES :: NROOTS ::

Calculates all real and complex roots of a polynomial of degree n

The algorithm is simple: just find any root of P(x) by Newton's R. Method,
then divide P(x) by Horner's method by the monomial (x-root), obtaining
a polynomial of degree n- 1, then the operation is repeated with this
resulting polynomial until a monomial is reached.

El algoritmo es sencillo: solo se encuentra una raiz cualquiera de P(x)
por el Metodo de Newton R., luego se divide P(x) por el metodo de Horner
entre el monomio (x-raiz), obteniendo un polinomio de grado n-1, luego
se vuelve a repetir la operacion con este polinomio resultante hasta
llegar a un monomio.

Developed by:

	JOSE LUIS DE LA CRUZ LAZARO
	contact@theworldofchaos.com

	YACSHA - Software & Desing, since 1999, Lima-Peru
	>> The World of Chaos - EL MUNDO DEL CAOS - Unlimited Programming
	www.theworldofchaos.com

LICENSE
	This file is released under the terms of the BSD 3-Clause License.
	Read LICENSE.txt file for more information.

HISTORY...

 >> Version 2 - 23-IV-2024
	- Update math-and-others\nraices - Porting to VC++ 2017
	- Code has updated to C++17
	- Add credits and history
	- The GUI has been translated from Spanish to English.
	- Comments and History version partially translated from
	  Spanish to English.

>> Version 1 - 17-IX-1999
	- First version for Borland C++ 3.1 and Turbo C 3.0

***********************************************************************/

#include <iostream>
#include <complex>
#include <vector>

using std::cout;
using std::cin;

typedef std::complex<double> complex;
#define DELTA 1e-10

complex fx(int iter, const complex& x, const int& n, const std::vector<double>& A ) {

	if (n != 0)
		return A[iter] * pow(x, n) + fx(iter + 1, x, n - 1, A);
	else 
		return A[iter];
}

complex fder(int iter, const complex& x, const int& n, const std::vector<double>& A ) {

	if (n != 0)
		return A[iter] * n*pow(x, n - 1) + fder(iter + 1, x, n - 1, A);
	else 
		return complex(0,0);
}

// Divide 2 polinomios P(orden m) Q(orden n) por el metodo de Horner,
// siendo D(orden m-n) el polinomio cociente
void horner(int iter, int m, const int& n, std::vector<double>& P, const std::vector<double>& Q, std::vector<double>& D) {

	int i;

	double a = P[0] / Q[0];

	std::vector<double> tmp(m);

	//D[iter] = a;
	D.push_back(a);

	for (i = 0; i < n; i++)
		tmp[i] = a * Q[i];

	for (i = n; i < m; i++)
		tmp[i] = 0;

	for (i = 0; i < m; i++)
		P[i] = P[i] - tmp[i];	
	
	i = 1;
	while ( i < m && 
			std::abs(P[i]) < DELTA // P[i]==0
		) {
		//D[++iter] = 0;
		D.push_back(0.0);
		i++;
	}

	int k;

	m = m - i;

	for (k = 0; k < m; k++)
		P[k] = P[k + i];

	if (m >= n)
		horner(iter + 1, m, n, P, Q, D);

}

complex NewtonRaphson(const int& n, const std::vector<double>& A) {

	complex x = complex(1, 1),	// Valor inicial para iteracion de NEWTON R.
								// UTILIZANDO ALGEBRA COMPLEJA
				last_x;			// x anterior calculado

	//NEWTON R. COMPLEJO
	do {

		last_x = x;

		x = x - fx(0, x, n, A) / fder(0, x, n, A);

	} while (std::abs(x - last_x) > DELTA);

	// Aproximación de las raices a cero para retornar
	// imaginarios puros o reales puros según sea el caso
		
	if (std::abs(std::real(x)) < DELTA)
		x = complex(0, std::imag(x)); // x es imaginario puro

	// Reales puros
	if (std::abs(std::imag(x)) < DELTA)
		x = complex(std::real(x), 0); // x es real puro

	return x;
}


int main()
{
	int m, n, i;

	// Coeficientes del polinomio ORIGINAL A
	std::vector<double> A;

	cout << ":: NROOTS ::" << std::endl << std::endl;

	cout << "Enter degree of the polynomial: ";
	cin >> m;

	// Asigna el espacio necesario para el vector A
	A.resize(m + 1, 0.0);

	cout << "\nEnter the coefficients starting with Cn to Co:";
	cout << "\nP(x)=Cnx^n+Cn-1x^n-1+....+Co ;Example: x^3-x+8 = 1 0 -1 -8\n\n";

	for (i = 0; i <= m; i++) {
		cout << "Enter C" << m - i << " : "; 
		cin >> A[i];
	}

	// Coeficientes del polinomio DIVIDENDO P
	std::vector<double> P;	

	// Coeficientes del polinomio DIVISOR Q
	std::vector<double> Q(3, 0.0);

	// Coeficientes del polinomio COCIENTE D
	std::vector<double> D;

	// Se inicializa el polinomio dividendo P
	// con los valores de A
	P = A;

	complex x;

	do {

		// NEWTON R. COMPLEJO
		x = NewtonRaphson(m, P);

		//SE CONSTRUYE EL POLINOMIO DIVISOR Q CON LAS RAICES HALLADAS
		//ESTE DIVIDIRA A P

		//ANALISIS DE LAS RAICES
		if (std::abs(std::imag(x)) == 0) {//la raiz es real
			n = 1;
			Q[0] = 1;
			Q[1] = -std::real(x);
			Q[2] = 0.0;
			cout << "\nRoot of P(x): " << x;

		} else {//la raiz es compleja

			n = 2;
			Q[0] = 1;
			Q[1] = -2 * std::real(x);//real(-(x+conj(x)));
			Q[2] = std::norm(x);//real(x*conj(x));
			cout << "\nRoot of P(x): " << x << "\nRoot of P(x): " << std::conj(x);
		}


		// El polinomio COCIENTE se inicializa vacio
		D.clear();

		// Se calcula el polinomio cociente D por el 
		// método de Horner: D = P/Q
		horner(0, m + 1, n + 1, P, Q, D);

		m = m - n;

		// D ahora es el nuevo polinomio DIVIDENDO
		P = D;

	} while (m > 0);

	return 1;

}
