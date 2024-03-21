/***********************************************************************
 :::CONCATENEO DE CADENAS:::
  >> Versión 1.0 26-XI-2000
 Clase Cstring que soporta concateneación de cadenas, es decir,
 que junta los contenidos de 2 cadenas y los añade a otra cadena destino.

 Ejemplo:

 CString primera("¨Una suma de cadenas?"), segunda("­Imposible!"), destino;
 destino = primera + segunda; //concateneo
 destino.Escribir(); //escribe el destino en pantalla

 :::Programado por:::
 José Luis De La Cruz Lázaro
 YACSHA - Software & Desing 2002
  >> yacsha@elmundodelcaos.tk    
  >> www.elmundodelcaos.tk -> EL MUNDO DEL CAOS - Unlimited Programming
  >> www.foros3d.tk  -> Foros de discusión  Flash/ActionScript - C/C++

***********************************************************************/

#include <string.h>
#include <stdio.h>

class CString
{
  public:
  char *cadena;

  CString(){ cadena =NULL; } //constructor por defecto
  CString( char *cadini ); // inicia el string con una cadena de caracteres
  //~CString();              //destructor "finta"

 //operador de concateneo, entre un objeto de esta
 //clase ( cadena izquierda ) y str ( cadena derecha )
 //y se retorna un objeto destino = CadIzq + CadDer
  CString operator +( CString str );

  void Escribir();  //escribe la cadena en pantalla
};

CString::CString( char *cadini )
{
 //asigna espacio para cadena
 cadena = new char[ strlen(cadini)+1 ];
 strcpy(cadena,cadini); // cadena = cadini
}

CString CString::operator +( CString str )
{
 CString destino;
 //se asigna el nuevo espacio para destino
 destino.cadena = new char[strlen(cadena)+strlen(str.cadena)+1];
 strcpy(destino.cadena,cadena); //destino = CadIzq
 strcat(destino.cadena,str.cadena);    //destino = primera + CadDer
 return destino;
}

void CString::Escribir()
{
 printf( "%s",cadena );
}

//un ejemplo
void main()
{
 CString primera("¨Una suma de cadenas?"),
	 segunda("­Imposible!"),
	 destino;

 destino = primera + segunda; //concateneo
 // destino = primera.operator+( segunda );

 destino.Escribir(); //escribe el destino en pantalla
 printf("\n");

}
