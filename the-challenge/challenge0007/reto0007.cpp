/****************************************************************************
El Reto 007
creado por: José Luis De la Cruz Lázaro
	    jcruz@ec-red.com
            www.geocities.com/joseluisdl
Fecha: 22 de Septiembre del 2000

Este programa es la recreación de un problema que tuve hace algún tiempo.

El objetivo es sumar 2 matrices mediante una función Suma, donde las matrices
son arreglos bidimensionales creados dinámicamente y su orden es
ingresado desde el teclado.

Pero resulta que el programa no muestra errores a la hora de compilar, talvez
algunos warnings, pero al momento de ejecutar el exe, sucede alguno de los
siguientes casos:
-El programa se cuelga desde el inicio;
-Muestra bien el resultado, pero al final se cuelga;
-Muestra bien el resultado, pero al final muestra el mensaje de error:
 Null pointer assignment.
-Muestra bien el resultado pero solo para matrices de orden pequeño;

PREGUNTAS:...
Lo que se quiere en primer lugar es encontrar donde está el error y explicar
porque que se cuelga. No se quiere que se de la solución para un compilador
específico, esto lo digo, porque su solución puede correr en DJGPP, pero no
en Borland C. Lo que se quiere es que la soluci¢n sea general.

En segundo lugar, modificar el programa de tal forma que se pueda sumar
las 2 matrices mas eficientemente.

La tercera pregunta es: ¨Hasta que Orden ( de las matrices ), podría
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

//Asigna Memoria a un puntero doble A
void CrearMatriz( int **A, int Orden);

//Destruye la matriz cuadrada creada con CrearMatriz
void DestruirMatriz( int **A, int Orden);

//Retorna la matriz suma de A y B
int **Suma( int **A, int **B, int Orden );

//Muestra la matriz A
void MostrarMatriz( int **A, int Orden );

void main()
{

 //2 punteros dobles, se utilizaran para crear 2 arreglos bidimensionales
 //din micos
 int **a,**b;

 int i,j;

 int N;

 cout<<"\n\nIngrese el orden de las matrices: ";
 cin>>N;

 CrearMatriz(a,N); //se crea din micamente una MATRIZ de orden N
 CrearMatriz(b,N); //se crea din micamente una MATRIZ de orden N

 srand(time(NULL)); //Inicializa el generador n£meros aleatorios,
		    //dependiente del tiempo actual

 for(i=0;i<N;i++)
  for(j=0;j<N;j++)
  {
   a[i][j]=rand()%10; // a y b contienen n£meros naturales menores que 10
   b[i][j]=rand()%10;
  }

 cout<<"\nContenido de matriz A:\n";
 MostrarMatriz(a,N); //se muestra la matriz A

 cout<<"\n\nContenido de matriz B:\n";
 MostrarMatriz(b,N); //se muestra la matriz B

 a=Suma(a, b, N); //se ejecuta la funci¢n suma y se asigna el resultado a la
		  //matriz a

 cout<<"\n\nLa suma matricial de A y B es:\n";
 MostrarMatriz(a,N); //se muestra la suma A+B

 DestruirMatriz(a, N); //destruye A
 DestruirMatriz(b, N); //destruye B

}

void CrearMatriz( int **A, int Orden)
{
 for( int i=0; i<Orden; i++)
  A[i] = new int[Orden];
}

void DestruirMatriz( int **A, int Orden)
{
 for( int i=0; i<Orden; i++)
  delete A[i];
}

int **Suma( int **A, int **B, int Orden )
{
 int **C,i,j;

 CrearMatriz(C,Orden);

 for(i=0;i<Orden;i++)
  for(j=0;j<Orden;j++)
    C[i][j]=A[i][j]+B[i][j];

 return C;
}

void MostrarMatriz( int **A, int Orden )
{
 int i,j;

  for(i=0;i<Orden;i++)
 {
  cout<<"\n";
  for(j=0;j<Orden;j++)
    cout<<A[i][j]<<" ";
 }
}




