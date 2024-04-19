/***********************************************************************
 ::: DEFINIENDO NUESTRA PROPIA FUNCION ALEATORIA :::

Tres formas diferentes de definir una función que retorne números
aleatorios, al mismo estilo de la función random. Es una forma
excelente de definir aleatorios si su compilador no dispone de
la función random (no ANSI C )

Programmed by:

	JOSE LUIS DE LA CRUZ LAZARO
	ramondc@hotmail.com

	UNIVERSIDAD NACIONAL DE INGENIERIA
	Faculty of Electrical and Electronic Engineering
	Lima-Peru

	YACSHA - Software & Desing
	>> The World of chaos - EL MUNDO DEL CAOS - Unlimited Programming

 HISTORY...

 >> Version 2 - 27-III-2024
	- Update math-and-others\aleator - Porting to VC++ 2017 using winbgi

>> Version 1 - 25-V-2001
	- First version for Borland C++ 3.1 and Turbo C 3.0

***********************************************************************/

#include <iostream>
#include <time.h>

using namespace std;

int main()
{
 //1ra forma ( la que sugieres )

 long N, No=2254, X;
 do
  N = (No++,       //Incrementamos la semilla
       N=No*No,   // elevamos N al cuadrado
       X = N/100L, // quitamos las 2 £ltimas cifras
       X - (X/10000L)*10000L); //quitamos las 2 primeras cifras
 while( N<1000); //mientras N<1000

 cout<<"\nAleatorio 1: "<<N;

 //2da forma (similar al algoritmo de random )
 //(genera un pseudoaletorio en funci¢n del tiempo actual,
 // comprendido entre 1000 y 9999

  N = 1000 + (long) time(NULL)  % 9000;

 cout<<"\nAleatorio 2: "<<N;

 //3ra forma (la que mas me gusta, a pesar de ser mas lenta)
 //( Una combinaci¢n de ambos m‚todos )

 No = 1000 + (long) time(NULL)  % 9000; //semilla

 do
  N = (No++,       //Incrementamos la semilla
       N=No*No,   // elevamos N al cuadrado
       X = N/100L, // quitamos las 2 £ltimas cifras
       X - (X/10000L)*10000L); //quitamos las 2 primeras cifras
 while( N<1000); //mientras N<1000

 cout<<"\nAleatorio 3: "<<N;

 return 1;
}
