/***********************************************************************
 ::: CONVERTIDOR DE ROMANOS A ARABIGOS :::
  >> Versión 1.0 13-X-2000
 Convierte un número Romano a un número Arabigo (numeración ordinaria).

 Ejemplo:
 Si ingreso LIX, retorna 59.

 :::Programado por:::
 José Luis De La Cruz Lázaro
 YACSHA - Software & Desing 2002
  >> yacsha@elmundodelcaos.tk    
  >> www.elmundodelcaos.tk -> EL MUNDO DEL CAOS - Unlimited Programming
  >> www.foros3d.tk  -> Foros de discusión  Flash/ActionScript - C/C++

***********************************************************************/

#include <iostream.h>
#include <string.h>

int conver( int cifraIZQ, int cifraDER )
{
 if( cifraIZQ>=cifraDER )
  return cifraIZQ;
 else
  return -cifraIZQ;
}

//retorna el equivalente decimal de la cifra romana ingresada
int DEC( char cifraROMANA )
{
 switch( cifraROMANA )
 {
  case 'I':  return 1;
  case 'V':  return 5;
  case 'X':  return 10;
  case 'L':  return 50;
  case 'C':  return 100;
  case 'D':  return 500;
  case 'M':  return 1000;
  default :  return 0;
 }
}

void main()
{
 char Romano[15];
 cout<<"Ingrese n£mero romano: ";
 cin>>Romano;
 strupr(Romano); // convierte el número ingresado a mayúsculas
 int  i,n=strlen(Romano)-1,Arabigo=0;

 for(i=0;i<n;i++)
  Arabigo+=conver( DEC(Romano[i]), DEC(Romano[i+1]) );

 Arabigo+=DEC(Romano[n]);
 cout<<"El equivalente en ar bigo es: "<<Arabigo;

}
