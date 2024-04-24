/***********************************************************************
 ::: NUMERO PRIMO :::
  >> Versi�n 1.0 17-IV-2001
 Programa que determina si un n�mero ingresado es un n�mero primo.

 :::Programado por:::
 Jos� Luis De La Cruz L�zaro
 YACSHA - Software & Desing 2002
  >> yacsha@elmundodelcaos.tk
  >> www.elmundodelcaos.tk -> EL MUNDO DEL CAOS - Unlimited Programming
  >> www.foros3d.tk  -> Foros de discusi�n  Flash/ActionScript - C/C++

***********************************************************************/

#include <iostream.h> //cout, cin
#include <math.h>

void main()
{
	int N, k, raiz;

	cout << "Ingrese un n�mero: ";
	cin >> N;

	raiz = (int)sqrt(N);

	// N ser� un primo, si solo es divisible por N
	// o por la unidad.
	for (k = 2; N%k && k <= raiz; k++);

	//Si se llego a dividir N entre todos los n�meros
	//menores que su ra�z cuadrada entonces es un primo
	cout << "\nEl n�mero " << (k == raiz + 1 ? "si" : "no") << " es primo";

}
