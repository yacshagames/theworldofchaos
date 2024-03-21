/***********************************************************************
 :::VALIDACION DE ENTRADA NUMERICA:::
  >> Versión 1.0 14-X-2000
  Aqui se muestra unos cuantos métodos para validar la entrada de solo
  números desde teclado. Cualquier entrada del tipo texto es rechazada. 

 :::Programado por:::
 José Luis De La Cruz Lázaro
 YACSHA - Software & Desing 2002
  >> yacsha@elmundodelcaos.tk    
  >> www.elmundodelcaos.tk -> EL MUNDO DEL CAOS - Unlimited Programming
  >> www.foros3d.tk  -> Foros de discusión  Flash/ActionScript - C/C++

***********************************************************************/

#include <stdio.h>
#include <stdlib.h>

void main()
{
  float a;
  char cad[10];

  printf("\n\nTipee cualquier cosa: ");

  //Para validar el n£mero ingresado, aprovecho el valor retornado
  //por scanf; scanf retorna 1 si lee el tipo de variable correcta
  //especificada en la cadena y cero en caso contrario

  while( !scanf("%f",&a) )
  {
   scanf("%s",&cad); //si el tipo de variable es incorrecta, la capturo
		     //a una cadena de texto
   printf("\nTipee cualquier cosa (El validador solo dejara entrar un numero): ");

  }

 printf("\nEl valor de a es: %f", a);

 //Otra forma de validar el n£mero, ser¡a tomando la entrada del
 //n£mero como una cadena de texto para luego convertirlo a un float
 //la funcion atof retorna el n£mero ( float ) contenido en la cadena,
 //y si la cadena no contiene un n£mero, retorna cero.
 //Por lo que el problema aqu¡, es que el n£mero a ingresar debe ser
 //diferente de cero.

  do
  {
   printf("\n\nTipeee cualquier cosa diferente de 0: ");
   scanf("%s",cad);
   a=atof(cad); //convierte la cadena a un n£mero en punto flotante
   if( a!=0.0) break;
   printf("\nPor favor ingrese un n£mero...\n");
  }while( 1 );

 printf("\nEl valor de a es: %f", a);

}
