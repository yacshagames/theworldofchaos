/****************************************************************************
Optimizacion de la SOLUCION al Reto 007
Solucionado el 11 de Octubre del 2000
****************************************************************************
ENUNCIADO ORIGINAL:

El Reto 007
creado por: José Luis De la Cruz Lázaro
	    jcruz@ec-red.com
	    www.geocities.com/joseluisdl
Propuesto el: 22 de Septiembre del 2000

Este programa es la recreaci¢n de un problema que tuve hace alg£n tiempo.

El objetivo es sumar 2 matrices mediante una funci¢n Suma, donde las 
matrices
son arreglos bidimensionales creados din micamente y su orden es
ingresado desde el teclado.

Pero resulta que el programa no muestra errores a la hora de compilar, 
talvez
algunos warnings, pero al momento de ejecutar el exe, sucede alguno de los
siguientes casos:
-El programa se cuelga desde el inicio;
-Muestra bien el resultado, pero al final se cuelga;
-Muestra bien el resultado, pero al final muestra el mensaje de error:
Null pointer assignment.
-Muestra bien el resultado pero solo para matrices de orden peque¤o;

PREGUNTAS:...
Lo que se quiere en primer lugar es encontrar donde est  el error y explicar
porque que se cuelga. No se quiere que se de la soluci¢n para un compilador
espec¡fico, esto lo digo, porque su soluci¢n puede correr en DJGPP, pero no
en Borland C. Lo que se quiere es que la soluci¢n sea general.

En segundo lugar, modificar el programa de tal forma que se pueda sumar
las 2 matrices mas eficientemente.

La tercera pregunta es: ¨Hasta que Orden ( de las matrices ), podr¡a
funcionar bien el programa, sin colgarse por falta de memoria?
Explicar porque.
Se debe cumplir que la soluci¢n de la pregunta 1 debe concordar con lo
dicho en la pregunta 3.

NOTA FINAL:
Este programa ha sido probado en los siguientes compiladores para DOS:
DJGPP 2.02, Borland C 3.1, Visual C++ 6 ( Win32 Console Application Project)
****************************************************************************/

#include <iostream.h>
#include <stdlib.h>
#include <time.h>

struct Matriz
{
int *elemento; //puntero a los elementos de la matriz
};

//Asigna Memoria a un puntero doble A
int CrearMatriz( Matriz &A , unsigned Orden);

//Destruye la matriz cuadrada creada con CrearMatriz
void DestruirMatriz( Matriz &A );

//Retorna la matriz suma de A y B
void Suma( Matriz &A , Matriz &B , unsigned Orden );

//Muestra la matriz A
void MostrarMatriz( Matriz &A , unsigned Orden );

void main()
{
//2 punteros dobles, se utilizaran para crear 2 arreglos bidimensionales
//din micos
Matriz a,b;

int i,j;
int N;

cout<<"\n\nIngrese el orden de las matrices: ";
cin>>N;

if( !CrearMatriz(a,N) ) return; //se crea din micamente una MATRIZ de orden 
N
if( !CrearMatriz(b,N) ) return; //se crea din micamente una MATRIZ de orden 
N

srand(time(NULL)); //Inicializa el generador n£meros aleatorios,
		    //dependiente del tiempo actual

for(i=0;i<N;i++)
  for(j=0;j<N;j++)
  {
   a.elemento[j*N+i]=rand()%10; // a y b contienen n£meros naturales menores 
que 10
   b.elemento[j*N+i]=rand()%10;
  }

cout<<"\nContenido de matriz A:\n";
MostrarMatriz(a,N); //se muestra la matriz A

cout<<"\n\nContenido de matriz B:\n";
MostrarMatriz(b,N); //se muestra la matriz B

Suma(a, b, N); //se ejecuta la funci¢n suma y se asigna el resultado a la
		  //matriz a

cout<<"\n\nLa suma matricial de A y B es:\n";
MostrarMatriz(a,N); //se muestra la suma A+B

DestruirMatriz(a); //destruye A
DestruirMatriz(b); //destruye B

}

int CrearMatriz( Matriz &A , unsigned Orden)
{

  if(  (A.elemento = new int[Orden*Orden])==NULL )
  {
   cout<<"\nNo hay memoria para crear la matriz...";
   return 0;
  }

return 1;
}

void DestruirMatriz( Matriz &A )
{
  delete A.elemento;
}

void Suma( Matriz &A , Matriz &B , unsigned Orden )
{

unsigned i,N=Orden*Orden;

for(i=0;i<N;i++)
  A.elemento[i]=A.elemento[i]+B.elemento[i];

}

void MostrarMatriz( Matriz &A , unsigned Orden )
{
unsigned i,N=Orden*Orden;

for(i=0;i<N;i++)
{
  if( i%Orden==0 ) cout<<"\n";
  cout<<A.elemento[i]<<" ";
}
}





