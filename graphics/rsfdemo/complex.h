// complex.h: interface for the complex class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMPLEX_H__C9098920_8F74_11D3_8C27_BE29B0177312__INCLUDED_)
#define AFX_COMPLEX_H__C9098920_8F74_11D3_8C27_BE29B0177312__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/*COMPLEJO.H fue creado por JLDL-SOFTWARE UNI-FIEE
Contiene operaciones aritmeticas entre numeros complejos
NOTA:	SI ALGUIEN QUIERE AGREGAR OTRA OPERACION MAS, HAGALO CON
	TODA CONFIANZA; PERO NO VAYA A BORRAR NADA DE LO QUE YA
	ESTA ECHO!!!!!!


 Version 1.1 31/10/1999

 se añade:
  constructor
  complex( double real)

	funcion
   exp( complex Z, complex B )

  
 Version 1.0 -> 26/1/99
	CLASES
	OPERADORES ARITMETICOS
	OPERADORES LOGICOS
	-Operador ==
	-Operador !=
	FUNCIONES

EJEMPLO:

#include"conio.h"
#include"iostream.h"
#include"math.h"
#include"complejo.h"

void coutz(complex Z,int i){
cout<<i<<")  ("<<Z.re<<","<<Z.im<<")\n";
}

void main()
{
clrscr();

complex Z(3,4),X;

cout<<abs(Z)<<"\n"<<arg(Z)<<"\n";

int i=1;

//1
X=conj(Z);
coutz(X,i++);
//2
X=pow(Z,5);
coutz(X,i++);
//3
X=sqrt(Z);
coutz(X,i++);
//4
X=exp(Z);
coutz(X,i++);
//5
X=log(Z);
coutz(X,i++);
//6
X=log10(Z);
coutz(X,i++);
//7
X=sin(Z);
coutz(X,i++);
//8
X=cos(Z);
coutz(X,i++);
//9
X=tan(Z);
coutz(X,i++);
//10
X=sinh(Z);
coutz(X,i++);
//11
X=cosh(Z);
coutz(X,i++);
//12
X=tanh(Z);
coutz(X,i++);
//13
X=asin(complex(5,8));
coutz(X,i++);
//14
X=acos(Z);
coutz(X,i++);
//15
X=atan(Z);
coutz(X,i++);

X=asinh(Z);
coutz(X,i++);

X=acosh(Z);
coutz(X,i++);

X=atanh(Z);
coutz(X,i++);

getch();

}

*/


//Esta es la clase complex
class complex{

	protected:

	double re,im;//Componentes del complejo

	
	public:
	//Si se declara un complejo
	//inline complex(complex Z){ re=real(Z);im=imag(Z); }

	complex(double real,double imag){ re=real;im=imag; }

	complex(double real){ re=real;im=0; }

	//Si se declara complejo sin argumentos
	complex() { re=0; im=0; }
	
	//Suma de complejos
	friend	complex operator +(complex Z,complex W)
	{
	 return complex( Z.re + W.re, Z.im + W.im );
	}

	//Suma de complejo y real
	friend	complex operator +(complex A,double x){

	return complex( A.re + x, A.im);
	}

	//Suma de real y complejo
	friend	complex operator +(double x, complex A){
	return complex( x + A.re, A.im);
	}

	//Diferencia de complejos
	friend	complex operator -(complex Z,complex W){
	return complex(Z.re - W.re, Z.im - W.im);
	}

	//Diferencia de complejo y real
	friend	complex operator -(complex A,double x){
	return complex( A.re-x, A.im );
	}

	//Diferencia de real y complejo
	friend	complex operator -(double x,complex A){
	return complex(x - A.re,-A.im);
	}
	//Negativo de un complejo
	complex operator -()
	 {
	  return complex(-re, -im);
	 }

	//Multiplicion de complejos
	friend	complex operator *(complex Z,complex W){
	
		return complex(Z.re*W.re - Z.im*W.im, Z.re*W.im + Z.im*W.re);

	}

	//Multiplicacion de un real con un complejo
	friend	complex operator *(double x,complex A){
		return complex(x*A.re,x*A.im);
	}

	//Division de complejo con real
	friend	complex operator /(complex A,double x){
	return complex(A.re/x,A.im/x);
	}

	//Division de complejos
	friend	complex operator /(complex A,complex B){
	return complex(A.re*B.re+A.im+B.im, A.im*B.re - A.re*B.im)/(B.re*B.re+B.im+B.im);
	}

	//OPERADORES LOGICOS

	//Operador ==
	friend	int operator ==(complex A,complex B){

	if(A.re==B.re&&A.im==B.im)return 1;else return 0; }

	//Operador !=
	friend	int operator !=(complex A,complex B){

	if(A.re!=B.re&&A.im!=B.im)return 1;else return 0; }


	//Parte Real e Imaginaria

	inline friend double real(complex Z){ return Z.re; };

	inline friend double imag(complex Z){ return Z.im; };

	
	//Modulo de un compolejo
friend double abs(const complex &Z);

//Conjugada de un complejo
friend complex conj(const complex &Z);
 
//Argumento de un complejo [-pi,pi]
friend double arg(const complex &A);

//Potencia de un complejo Z^n
friend complex pow(const complex &Z, double n);

//Potencia compleja de un complejo Z^W ; W=x+y*i
friend complex pow(const complex &Z, const complex &W);

//Raiz cuadrada de un complejo
friend complex sqrt(const complex &Z);

//exponencial de un complejo e^Z
friend complex exp(const complex &Z);

//Logaritmo Natural de un complejo ln(Z)
friend complex log(const complex &Z);

//Logaritmo en base 10 de un complejo
friend complex log10(const complex &Z);

//Seno de un complejo
friend complex sin(const complex &Z);

//Coseno
friend complex cos(const complex &Z);

//Tangente
friend complex tan(const complex &Z);

//Seno Hiperbolico
friend complex sinh(const complex &Z);

//Coseno Hiperbolico
friend complex cosh(const complex &Z);

//Tangente Hiperbolica
friend complex tanh(const complex &Z);

//Arcoseno Hiperbolico
friend complex asinh(const complex &Z);

//Arcocoseno Hiperbolico
friend complex acosh(const complex &Z);

//Arcotangente Hiperbolica
friend complex atanh(const complex &Z);

//Arcoseno
friend complex asin(const complex &Z);

//Arcocoseno
friend complex acos(const complex &Z);

//Arcotangente
friend complex atan(const complex &Z);

};


#endif // !defined(AFX_COMPLEX_H__C9098920_8F74_11D3_8C27_BE29B0177312__INCLUDED_)
