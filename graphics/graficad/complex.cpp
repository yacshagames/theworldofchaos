// complex.cpp: implementation of the complex class.
//
//////////////////////////////////////////////////////////////////////
#include <cmath>
#include "complex.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//Modulo del complejo
double abs(const complex &Z)
{
	return sqrt(real(Z)*real(Z) + imag(Z)*imag(Z));
}

//Conjugada de un complejo
complex conj(const complex &Z)
{
	return complex(real(Z), -imag(Z));
}

//Argumento de un complejo [-pi,pi]
double arg(const complex &A) {

	double arg = acos(real(A) / abs(A));
	if (imag(A) < 0) arg = (-arg);

	return arg;
}

//Potencia de un complejo Z^n
complex pow(const complex &Z, double n) {

	return pow(abs(Z), n)*complex(cos(n*arg(Z)), sin(n*arg(Z)));
}

//Potencia compleja de un complejo Z^W ; W=x+y*i
complex pow(const complex &Z, const complex &W) {

	if (W.im == 0)
		return pow(Z, W.re);
	else
		return pow(Z, W.re)*exp(-arg(Z)*W.im);
}


//Raiz cuadrada de un complejo
complex sqrt(const complex &Z) {

	return pow(Z, 0.5);
}

//exponencial de un complejo e^Z
complex exp(const complex &Z) {

	return exp(real(Z))*complex(cos(imag(Z)), sin(imag(Z)));
}

//Logaritmo Natural de un complejo ln(Z)
complex log(const complex &Z) {

	return complex(log(abs(Z)), arg(Z));
}

//Logaritmo en base 10 de un complejo
complex log10(const complex &Z) {

	return log(Z) / log(10);
}

//Seno de un complejo
complex sin(const complex &Z) {
	//complex i(0,1);
	//return ( exp( Z*i ) - exp( -Z*i ) ) / ( 2*i );

	return complex(sin(real(Z))*cosh(imag(Z)), cos(real(Z))*sinh(imag(Z)));
}

//Coseno
complex cos(const complex &Z) {
	//complex i(0,1);
	//return ( exp( Z*i ) + exp( -Z*i ) )/2;
	return complex(cos(real(Z))*cosh(imag(Z)), -sin(real(Z))*sinh(imag(Z)));
}

//Tangente
complex tan(const complex &Z) {

	return sin(Z) / cos(Z);
}

//Seno Hiperbolico
complex sinh(const complex &Z) {

	//return (exp(Z)-exp(-Z))/2;
	return complex(sinh(real(Z))*cos(imag(Z)), cosh(real(Z))*sin(imag(Z)));

}

//Coseno Hiperbolico
complex cosh(const complex &Z) {

	//return (exp(Z)+exp(-Z))/2;
	return complex(cosh(real(Z))*cos(imag(Z)), sinh(real(Z))*sin(imag(Z)));

}

//Tangente Hiperbolica
complex tanh(const complex &Z) {

	return sinh(Z) / cosh(Z);

}

//Arcoseno Hiperbolico
complex asinh(const complex &Z) {

	return log(Z + sqrt(Z*Z + 1));
}

//Arcocoseno Hiperbolico
complex acosh(const complex &Z) {

	return log(Z + sqrt(Z*Z - 1));
}

//Arcotangente Hiperbolica
complex atanh(const complex &Z) {

	return 0.5*log((1 + Z) / (1 - Z));
}

//Arcoseno
complex asin(const complex &Z) {
	complex i(0, 1);
	return asinh(Z*i) / i;
}

//Arcocoseno
complex acos(const complex &Z) {
	complex i(0, 1);
	return acosh(Z) / i;

}

//Arcotangente
complex atan(const complex &Z) {
	complex i(0, 1);
	return  atanh(Z*i) / i;
}