/*********************************************************************
LECTURA DE NUMEROS
Este programa lee un numero entero y retorna su equivalente en letras.
Ejm:
Si ingreso 3465
el programa retorna "tres mil cuatrocientos sesenta y cinco"

Version 1.1 - 9 Feb 2000
- Se supero el error de que cuando ingresabas un numero que terminaba
  en tres ceros, se escribia "cero" al final de la cadena.

Version 1.0 - 2 Dic 1999
- Lectura de numeros menores que 100000.

programado por:
JOSE LUIS DE LA CRUZ LAZARO
ramondc@hotmail.com
Pagina Web: http://www.geocities.com/joseluisdl/jldl.htm
**********************************************************************/

#include <iostream.h>
#include <conio.h>

char *Unidad[10] = { "cero", "uno", "dos","tres","cuatro","cinco", "seis",
		   "siete", "ocho", "nueve" };

char *Diez[10] = { "diez", "once", "doce", "trece", "catorce", "quince",
		 "dieciseis", "diecisiete", "dieciocho", "diecinueve" };

char *Decena[10] = { "cero","diez","veinte","treinta","cuarenta","cincuenta",
		   "sesenta","setenta","ochenta","noventa" };

char *Centena[10] = { "cien", "ciento", "doscientos", "trescientos","cuatrocientos",
			 "quinientos", "seiscientos", "setecientos",
			 "ochocientos", "novecientos" };
char Millar[] = "mil";

void Nombrar_Centena(int Num)
{
	//Num es una centena de la forma abc
	//descomponemos num en: a, b y c
	int a, b, c;
	c = Num % 10;
	b = (Num % 100 - c) / 10;
	a = (Num - 10 * b - c) / 100;

	if (a > 0)
		if (b == 0 && c == 0)       //si el Num = 100
			cout << Centena[0] << " ";
		else cout << Centena[a] << " "; ///si 100<Num<200


	if (b > 0)
		if (b == 1)
			cout << Diez[c] << " "; //si 10<Num<20
		else
			cout << Decena[b] << " "; //si 1<b<10

	if (c > 0)                 //imprime las unidades
	{
		if (b > 1) cout << "y ";
		if (b != 1) cout << Unidad[c] << " ";
	}

}

void Nombrar_Numero(long Num)
{
	//Num es un numero menor que 100000
	if (Num == 0)cout << Unidad[0]; //si Num=0
	if (Num < 100000) //si Num 1<
	{
		int Num_mil = (Num - Num % 1000) / 1000;
		if (Num_mil > 1) Nombrar_Centena(Num_mil);
		if (Num >= 1000) cout << Millar << " ";
		Nombrar_Centena(Num % 1000);
	}
	else cout << "Lo siento, el n£mero ingresado es mayor o igual a 100000";

}


void main()
{

	clrscr();
	long Num;
	cout << "Ingrese un n£mero menor que 100000: ";
	cin >> Num;

	cout << "\nEl n£mero en letras ingresado es:\n\n";
	Nombrar_Numero(Num);

	getch();

}