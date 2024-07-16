/***********************************************************************
::: CHAIN ??CONCATENATION ::: CONCATENEO DE CADENAS :::

 Cstring class that supports string concatenation, i.e.
 which joins the contents of 2 chains and adds them to another destination chain.

 I developed this library in the 2000s, and it was useful in compilers
 old that did not support the STL, but now with the inclusion of the class
 standard std::string, this library has been obsolete, but I am
 leaving at the disposal of the community, as a didactic example of the
 overloading of the + operator, on objects of a class

 Example:

 CString first("A sum of strings?"), second("Impossible!"), destination;
 destination = first + second; //concatenate
 destination.Write(); //write the destination on the screen

------------------------------------------------------------------------------

 Clase Cstring que soporta concateneación de cadenas, es decir,
 que junta los contenidos de 2 cadenas y los añade a otra cadena destino.

 Esta librería la desarrollé por los años 2000, y era útil en compiladores
 viejos que no soportaban la STL, pero ahora con la inclusión de la clase
 estándar std::string, esta librería a quedado obsoleta, pero la estoy
 dejando a disposición de la comunidad, como un ejemplo didáctico de la
 sobrecarga del operador +, en objetos de una clase

 Ejemplo:

 CString primera("¨Una suma de cadenas?"), segunda("­Imposible!"), destino;
 destino = primera + segunda; //concateneo
 destino.Escribir(); //escribe el destino en pantalla

Developed by:

	JOSE LUIS DE LA CRUZ LAZARO
	contact@theworldofchaos.com

	YACSHA - Software & Desing, since 1999, Lima-Peru
	>> The World of Chaos - EL MUNDO DEL CAOS - Unlimited Programming
	www.theworldofchaos.com

LICENSE
	This file is released under the terms of the BSD 3-Clause License.
	Read LICENSE.txt file for more information.

HISTORY...

 >> Version 2 - 19-IV-2024
	- Update math-and-others\concateo - Porting to VC++ 2017 using winbgi
	- Using strcpy_s and strcat_s instead old and not secure strcpy and strcat

>> Version 1 - 26-XI-2000
	- First version for Borland C++ 3.1 and Turbo C 3.0

***********************************************************************/

#include <iostream>

using namespace std;

class CString
{
public:
	char *cadena;

	CString() { cadena = NULL; } //constructor por defecto
	CString(const char *cadini); // inicia el string con una cadena de caracteres
	//~CString();              //destructor "finta"

   //operador de concateneo, entre un objeto de esta
   //clase ( cadena izquierda ) y str ( cadena derecha )
   //y se retorna un objeto destino = CadIzq + CadDer
	CString operator +(const CString&  str);

	void Escribir();  //escribe la cadena en pantalla
};

CString::CString(const  char *cadini)
{
	//asigna espacio para cadena
	unsigned int tamanoCadena = static_cast<unsigned int>(strlen(cadini) + 1);
	cadena = new char[tamanoCadena];
	strcpy_s(cadena, tamanoCadena, cadini); // cadena = cadini
}

CString CString::operator +(const CString& str)
{
	CString destino;
	//se asigna el nuevo espacio para destino
	unsigned int tamanoCadena = static_cast<unsigned int>(strlen(cadena) + strlen(str.cadena) + 1);
	destino.cadena = new char[tamanoCadena];
	strcpy_s(destino.cadena, tamanoCadena, cadena); //destino = CadIzq
	strcat_s(destino.cadena, tamanoCadena, str.cadena);    //destino = primera + CadDer
	return destino;
}

void CString::Escribir()
{
	cout << cadena;
}

//un ejemplo
int main()
{
	CString primera("¨Una suma de cadenas?"),
			segunda("­Imposible!"),
			destino;

	destino = primera + segunda; //concateneo
	// destino = primera.operator+( segunda );

	destino.Escribir(); //escribe el destino en pantalla
	
	cout << endl;

	return 1;
}
