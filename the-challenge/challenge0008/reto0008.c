/*****************************************************************
El Reto 0008
creado por: José Luis De la Cruz Lázaro
              jcruz@ec-red.com
            www.geocities.com/joseluisdl
Fecha: 19 de Octubre del 2000

ENUNCIADO:
El problema es simple, solo se tiene ingresar un número "x", luego
evaluar "f(x)" y mostrar este resultado en pantalla. Donde la función
f(x) se define como sigue:

f(x) = { 2*sen(x/2)*(cos(x/2))^2 , x<0
         1/4*sen(2*x)*sec(x/2)   , 0<=x<2
         exp(x)*tan(x/2)         , x>2    }

Nota:^2 significa que está elevado al cuadrado

Para lograr lo anterior, adjunto un programa incompleto. En dicho
programa se puede observar unas líneas punteadas ( ....... ) que hay
que completar con código.

CONDICIONES DEL PROBLEMA:
Estas condiciones deben ser respetadas, de lo contrario su solución
quedará descalificada.

1) No modificar el código que ya está escrito, solo se debe completar
las líneas punteadas.

2) No se puede declarar más funciones, la única función declarada en el
programa debe ser:
   double f(double x) .

3) No se puede utilizar la sentencia if .

4) En las líneas punteadas que aparecen dentro de la función: double
( double x )
   no se puede utilizar ningún tipo de sentencia ni operador
condicional.

5) La evaluación de la función f(x) se debe hacer solo dentro de la
función:
   double f( double x ) , en ningún otro lado del programa.

NOTA FINAL:
Este programa ha sido probado en los siguientes compiladores para DOS:
DJGPP 2.02 y Borland C++ 3.1

Si alguien tiene problemas con los acentos, sugiero que conviertan el
presente texto, a texto en formato DOS, puede ser utilizando el WorPad
de windows.

Y POR ULTIMO SOLO PUEDO DECIR.... MUCHA SUERTE Y QUE GANE EL MEJOR
CODIGO....
*****************************************************************/

#include <stdio.h>
#include <math.h>

.......

double f( double x )
{
  return .......
}

void main()
{
  double x;
  printf("\n\nIngrese x: ");
  scanf( "%lf", &x );

  .......

  printf( "Resultado: f( %lg ) = %lf ", x, f( x ) );

}

