/*************************************************************************
JOSE LUIS DE LA CRUZ LAZARO   UNI-FIEE
ramondc@hotmail.com

ENCRIPTADOR GAUSSIANO

VERSION 1.0 10/06/99

Programa que encripta un documento de texto ACSII, utilizando la funcion
Gaussiana Pi(x) y la funcion Primo(n)

Donde:

* Pi(x) es el numero de primos menor o igual que un numero positivo x
  Ejm Pi(4)= 2 ; Pi(20)=8
* Primo(n) es el n-‚simo primo contado a partir desde 1
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

*************************************************************************/

#include "iostream.h"
#include "conio.h"
#include "stdio.h"

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
	clrscr();

	int opcion;

	char ruta1[255], ruta2[255], *p;


	cout << "\tENCRIPTADOR NATURAL 1.0\n\n";
	cout << "\t\t(1) CODIFICACION\n\n";
	cout << "\t\t(2) DECODIFICACION\n\n";
	cout << "\t\t(3) Salir\n\n";
	cout << "\t\tElija una opci¢n: ";
	cin >> opcion;

	clrscr();
	if (opcion == 3)return 0;
	if (opcion == 1)cout << "CODIFICACION:\n\n";
	if (opcion == 2)cout << "DECODIFICACION:\n\n";
	cout << "\tIngrese la ruta del archivo fuente:\n>>\t";
	cin >> ruta1;
	cout << "\tIngrese la ruta del archivo destino:\n>>\t";
	cin >> ruta2;


	//Abre el archivo para lectura
	FILE *Alec, *Aesc;
	p = ruta1;
	Alec = fopen(p, "r");
	p = ruta2;
	Aesc = fopen(p, "w");


	if (Alec == NULL)
	{
		cout << "\n\n\t­­­El archivo fuente no Existe!!!";
		return 1;
	}


	unsigned char arg, res, caracter;

	if (opcion == 1)
		//CODIFICACION
		while (fscanf(Alec, "%c", &caracter) != EOF)
		{
			arg = Pi(caracter);
			res = caracter - Primo[arg];
			fprintf(Aesc, "%c%c", 32 + arg, 32 + res);
		}

	if (opcion == 2)
		//DECODIFICACION
		while (fscanf(Alec, "%c%c", &arg, &res) != EOF)
		{
			arg -= 32;
			res -= 32;
			caracter = Primo[arg] + res;
			fprintf(Aesc, "%c", caracter);
		}

	fcloseall();
	gotoxy(30, 12); cout << "PROCESO TERMINADO";

	getch();


	return 0;
}
