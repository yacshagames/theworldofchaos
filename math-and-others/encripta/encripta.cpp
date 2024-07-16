/*************************************************************************
::: GAUSSIAN ENCRYPTOR ::: ENCRIPTADOR GAUSSIANO :::

Program that encrypts an ACSII text document, using the
Gaussian function Pi(x) and the Primo(n) function

Where:

* Pi(x) is the number of primes less than or equal to a positive number x
 For example Pi(4)= 2 ; Pi(20)=8
* Prime(n) is the nth prime counted from 1
 Ejm Prime(11)=29

Algorithm:

If "character" is ASCII then 0<=character<=255

Then: character = prime + remainder

prime is the smallest prime number immediately to character

where prime = Prime( argument )

and argument = Pi(character)

So any number can be represented only by its argument (arg) and its
remainder (res).

 Example: if character='U' (character=85)

 85 = 83 + 2 = Prime(Pi(24)) + 2

 Then: 85 is represented by -> arg=24 and res=2

-Some Bugs fixed
Arg and res are increased by 32 so their values ??are not between
0 and 32 since fscanf does not read ASCII characters in said interval

Then in the example:

arg=32+24=56 (corresponding to ASCII '7')
res=32+2=34 (corresponding to ACSII '"')

NEXT PROJECTS
-TIME-DEPENDENT ENCRYPTION PROGRAMS, THIS MEANS THAT THE DESTINATION
 FILE ENCRYPTED AT 8:00am WILL BE DIFFERENT FROM ANOTHER DESTINATION
 FILE ENCRYPTED AT 8:01am, EVEN THOUGH THE 2 ENCRYPTIONS COME FROM
 THE SAME SOURCE FILE...

--------------------------------------------------------------------------
Spanish:

Programa que encripta un documento de texto ACSII, utilizando la funcion
Gaussiana Pi(x) y la funcion Primo(n)

Donde:

* Pi(x) es el numero de primos menor o igual que un numero positivo x
  Ejm Pi(4)= 2 ; Pi(20)=8
* Primo(n) es el n-esimo primo contado a partir desde 1
  Ejm Primo(11)=29

Algoritmo:

Si "caracter" es un ASCII entonces   0<=caracter<=255

Luego: caracter = primo + residuo

primo es el numero primo menor inmediato a caracter

donde  primo = Primo( argumento )

y       argumento = Pi(caracter)

Por lo que cualquier numero puede ser representado solo por su
argumento (arg) y por su residuo (res)

       Ejm: si caracter='U' (caracter=85)

       85 = 83 + 2 = Primo( Pi(24) ) + 2

       Luego: 85 se representa por -> arg=24 y res=2

-Algunos Bugs arreglados
A arg y res se les aumenta 32 para sus valores no esten entre 0 y 32
ya que fscanf no lee los caracteres ASCII en dicho intervalo

Luego en el ejemplo:

arg=32+24=56 (que corresponde al ASCII '7')
res=32+2=34  (que corresponde al ACSII '"')

PROXIMOS PROYECTOS
-PROGRAMAS ENCRIPTADORES QUE DEPENDENDEN DEL TIEMPO, ESTO QUIERE
 DECIR QUE EL ARCHIVO DESTINO ENCRIPTADO A LAS 8:00am SERA DIFERENTE A OTRO
 ARCHIVO DESTINO ENCRIPTADO A LAS 8:01am, A PESAR DE QUE LAS 2
 ENCRIPTACIONES PROVIENEN DE UN MISMO ARCHIVO FUENTE...

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

 >> Version 3 - 22-IV-2024
	- The modern C++ ifstream and ofstream classes are used, instead
	  of the old C language FILE library, to read and write binary files.

 >> Version 2 - 19-IV-2024
	- Update math-and-others\encripta - Porting to VC++ 2017 using winbgi
	- Using strcpy_s and strcat_s instead old and not secure strcpy and strcat

>> Version 1 - 10-VI-1999
	- First version for Borland C++ 3.1 and Turbo C 3.0

*************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::cin;

int Primo[56] = { 1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
		31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73,
		79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131,
		137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191,
		193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257 };

int Pi(int x)
{
	int i = 0;
	while (x >= Primo[i])i++;
	return i - 1;
}


int main()
{
	int opcion;

	std::string ruta1, ruta2;

	cout << "ENCRIPTADOR NATURAL 1.0\n\n";
	cout << "\t(1) CODIFICACION\n\n";
	cout << "\t(2) DECODIFICACION\n\n";
	cout << "\t(3) Salir\n\n";
	cout << "\tElija una opcion: ";
	cin >> opcion;

	if (opcion == 3)
		return 0;

	cout << endl;

	if (opcion == 1)
		cout << "\tCODIFICACION:\n\n";

	if (opcion == 2)
		cout << "\tDECODIFICACION:\n\n";

	cout << "\tIngrese la ruta del archivo fuente:\n\t>> ";
	cin >> ruta1;

	cout << "\tIngrese la ruta del archivo destino:\n\t>> ";
	cin >> ruta2;


	//Abre el archivo para lectura
	std::ifstream Alec(ruta1, std::ios::binary);
	std::ofstream Aesc(ruta2, std::ios::binary);

	if (Alec.is_open()==false)
	{
		cout << "\n\n\tEl archivo fuente no Existe!!!";
		return 1;
	}

	if (Aesc.is_open()==false)
	{
		cout << "\n\n\tNo se pudo crear el archivo destino!!!";
		return 1;
	}

	// Copia el archivo de lectura en un buffer
	std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(Alec), {});

	char arg, res, caracter;

	if (opcion == 1)
		//CODIFICACION
		for( auto& caracter : buffer)
		{
			arg = Pi(caracter);
			res = caracter - Primo[arg] + 32;
			arg += 32;
			// Escribe arg y res en Aes
			Aesc.write(&arg, 1);
			Aesc.write(&res, 1);
		}

	if (opcion == 2) {
		//DECODIFICACION
		if (buffer.empty()==false) {
			unsigned int i, size = static_cast<unsigned int>(buffer.size()) - 1;
			for (i = 0; i < size; i += 2)
			{
				arg = buffer[i] - 32;
				res = buffer[i + 1] - 32;
				caracter = Primo[arg] + res;

				// Escribe caracter en Aes
				Aesc.write(&caracter, 1);
			}
		}
	}

	Alec.close();
	Aesc.close();
	
	cout << endl << "PROCESO TERMINADO" << endl;

	return 1;
}
