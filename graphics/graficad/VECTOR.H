#pragma once

/**********************************************************************
VECTOR.H fue creado por JLDL-SOFTWARE UNI-FIEE
Contiene las operaciones mas comunes echas con vectores en 3D y 2D
NOTA:	SI ALGUIEN QUIERE AGREGAR OTRA OPERACION MAS, HAGALO CON
	TODA CONFIANZA; PERO NO VAYA A BORRAR NADA DE LO QUE YA
	ESTA ECHO!!!!!!

>> Version 2 - 22-III-2024
	- Update: Porting to VC++ 2017 using winbgi

Version 1.1 -> 29/11/98
	OPERADORES LOGICOS
	-Operador ==
	-Operador !=

Version 1.0 -> 26/11/98
	CLASES
	-Componentes del vector
		componenteX= A.x
		componenteY= A.y
		componenteZ= A.z

	-vector con 3 coordenadas: vector <vector>(double x,double y,double z);
	-vector con 2 coordenadas: vector <vector>(double x,double y);
	-vector sin argumentos:    vector <vector>;
	-Modulo del vector			-> A.mod()
	-Unitario de un Vector  		-> A.uni()
	-Vector Ortogonal (Solo para 2D) 	-> A.ort()
	-Suma de Vectores			-> A+B
	-Diferencia de vectores 		-> A-B
	-Producto Escalar			-> A%B
	-Producto Vectorial			-> A*B
	-Producto de un Escalar por un Vector 	-> k*A
	-Division de un Vector entre un Escalar -> A/k
	I/O
	-Se define cout<<(vector)
	-Se define cin>>(vector)
	FUNCIONES
	-Triple Producto Escalar de Vectores	-> tpe(vector A,vector B,vector C)
	-Angulo entre 2 vectores ( [0,PI] en Radianes)
		-> double ang(vector A,vector B)

	-Argumento de un Vector ([0,2*PI] en Radianes)
	 (Angulo que hace con respecto al eje X en sentido antihorario)
	 (Solo para 2D)

		-> double arg(vector A)


EJEMPLO:

#include"vector.h"
#include"conio.h"
void main(){
clrscr();
vector a(1,2,0),b(4,5,6),c;
//Producto vectorial
c=a*b;
cout<<c;
//Producto Escalar
cout<<"\n"<<a%b;
//ortogonal de a
c=a.ort();
cout<<"\n"<<c;
//Componente z de b
cout<<"\n"<<b.z;
//Modulo de b
cout<<"\n"<<b.mod();
getch();
}


**********************************************************************/


//#include"iostream.h"
//#include"math.h"

//Esta es la clase vector
class vector {

public:

	double x, y, z;//Componentes del vector

	//Si se declara un vector con 3 coordenadas
	vector(double xx, double yy, double zz) { x = xx; y = yy; z = zz; }

	//Si se declara un vector con 2 coordenadas
	vector(double xx, double yy) { x = xx; y = yy; z = 0; }

	//Si se declara vector sin argumentos
	vector() { vector(0, 0, 0); }

	//Modulo del vector
	double mod() { return sqrt(x*x + y * y + z * z); }

	//Unitario de un Vector
	vector uni()
	{
		vector A;
		A.x = x; A.y = y; A.z = z;
		return A / A.mod();
	}

	//Vector Ortogonal (Solo para 2D)
	vector ort() {
		//if(z!=0)cout<<"\nNo se puede ortogonalizar vector!!!__JLDL";
		vector M;
		M.x = -y; M.y = x; M.z = z;
		return M;
	}

	//Suma de Vectores
	friend	vector operator +(vector A, vector B) {
		vector M;

		M.x = A.x + B.x;
		M.y = A.y + B.y;
		M.z = A.z + B.z;

		return M;
	}

	//Diferencia de vectores
	friend	vector operator -(vector A, vector B) {
		vector M;

		M.x = A.x - B.x;
		M.y = A.y - B.y;
		M.z = A.z - B.z;

		return M;
	}

	//Producto Escalar
	friend	double operator %(vector A, vector B) {
		double M;

		M = A.x*B.x + A.y*B.y + A.z*B.z;

		return M;

	}

	//Producto Vectorial
	friend	vector operator *(vector A, vector B) {
		vector M;

		M.x = A.y*B.z - A.z*B.y;
		M.y = -(A.x*B.z - A.z*B.x);
		M.z = A.x*B.y - A.y*B.x;

		return M;
	}

	//Producto de un Escalar por un Vector
	friend	vector operator *(double k, vector B) {
		vector M;

		M.x = k * B.x;
		M.y = k * B.y;
		M.z = k * B.z;

		return M;
	}

	//Division de un Vector entre un Escalar
	friend	vector operator /(vector B, double k) {
		vector M;

		M.x = B.x / k;
		M.y = B.y / k;
		M.z = B.z / k;

		return M;
	}

	//OPERADORES LOGICOS

	//Operador ==
	friend	int operator ==(vector A, vector B) {

		if (A.x == B.x&&A.y == B.y&&A.z == B.z)return 1; else return 0;
	}

	//Operador !=
	friend	int operator !=(vector A, vector B) {

		if (A.x != B.x&&A.y != B.y&&A.z != B.z)return 1; else return 0;
	}


};
/*
//Se define cout<<(vector)
ostream _FAR & _Cdecl _FARFUNC operator<<(ostream _FAR &, vector _FAR & A){
cout<<"("<<A.x<<","<<A.y<<","<<A.z<<")";
}

//Se define cin>>(vector)
istream _FAR & _Cdecl _FARFUNC operator>>(istream _FAR &, vector _FAR & A){
cin>>A.x>>A.y>>A.z;
}*/

//Triple Producto Escalar de Vectores
double tpe(vector A, vector B, vector C) {
	return A % (B*C);
}

//Angulo entre 2 vectores ([0,PI] en Radianes)
double ang(vector A, vector B) {
	return acos(A%B / (A.mod()*B.mod()));
}

//Argumento de un Vector ([0,2*PI] en Radianes)
//(Angulo que hace con respecto al eje X en sentido antihorario)
//(Solo para 2D)
double arg(vector A) {

	double arg = acos(A.x / A.mod());
	if (A.y < 0)arg = 2 * M_PI - arg;

	return arg;
}