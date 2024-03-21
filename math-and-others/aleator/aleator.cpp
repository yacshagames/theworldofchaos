/***********************************************************************
 ::: DEFINIENDO NUESTRA PROPIA FUNCION ALEATORIA :::
  >> Versión 1.0 25-V-2001
 Tres formas diferentes de definir una función que retorne números
 aleatorios, al mismo estilo de la función random. Es una forma
 excelente de definir aleatorios si su compilador no dispone de
 la función random (no ANSI C ).

 :::Programado por:::
 José Luis De La Cruz Lázaro
 YACSHA - Software & Desing 2002
  >> yacsha@elmundodelcaos.tk    
  >> www.elmundodelcaos.tk -> EL MUNDO DEL CAOS - Unlimited Programming
  >> www.foros3d.tk  -> Foros de discusión  Flash/ActionScript - C/C++

***********************************************************************/

#include <iostream.h>
#include <time.h>

void main()
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

}
