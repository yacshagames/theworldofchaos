//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Copyright ??? nyder2000@yahoo.es ???
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <conio.h>
#include <stdio.h>
#define bisiesto(bs)    (!(bs%4)&&(bs%100)||!(bs%400))

int main()
{
	int i, j, anho, mes, dia, ds, mesd;

	// Variable que contiene los meses del a�o para el calendario.
	char mesc[][20] = { "       Enero","      Febrero","       Marzo",
	"       Abril","        Mayo","       Junio","       Julio",
	"       Agosto","     Septiembre","      Octubre","     Noviembre",
	"     Diciembre" };

	int semana[6][7] = { 0 }; // Matriz para contener el calendario del mes.
	int *p;    // Puntero que manejar  la matriz del calendario del mes.

	clrscr();

	printf("\nd�a= "); //
	scanf("%i", &dia);  //
	printf("\nmes= "); //  Entrada de la Fecha
	scanf("%i", &mes);  //
	printf("\na�o= "); //
	scanf("%i", &anho); //

	ds = (((1461 * ((anho + 4800) + ((mes - 14) / 12))) >> 2)      // D�a de la semana
		+ ((367 * (mes - 2 - 12 * ((mes - 14) / 12))) / 12)          // Lunes = 0 ...
		- (3 * (((anho + 4800) + ((mes - 14) / 12) + 100) / 100) >> 2) // Domingo = 6
		+ dia - 32075L) % 7;                               //

	switch (mes)
	{
	case 1:case 3:case 5:case 7:case 8:case 10:      //
	case 12:mesd = 31; break;                           // N�mero de d�as
	case 4:case 6:case 9:case 11:mesd = 30; break;      // del mes...
	case 2:mesd = 28; if (bisiesto(anho)) mesd = 29; break; //
	}

	ds = ds - (dia % 7 - 1);  // Punto clave de la ubicaci�n del d�a 1
	if (ds < 0)ds += 7;    // Correcci�n, caso de ser necesaria  ;-)

	printf("\n\n %s", mesc[mes - 1]); // Impresi�n del T�tulo del mes.
	printf("\n Lu Ma Mi Ju Vi Sa Do\n"); // Encabezados de los d�as.

	p = &semana[0][0]; // Ubicaci�n del puntero sobre la matriz del mes.

	for (i = 0; i < mesd; i++) // Ubicaci�n de los d�as en la matriz
		*(p + ds + i) = i + 1;     // a trav�s del puntero al primer elemento.

	for (j = 0; j < 6; j++) // Ciclo de impresi�n
	{
		for (i = 0; i < 7; i++)
		{
			if (semana[j][i] == 0)
			{
				printf("   "); // Si no es un d�a del mes.
			}
			else
			{
				cprintf("%3d", semana[j][i]); // Si es un d�a del mes.
				semana[j][i] = 0;
			}
		}
		printf("\n");
	}

	return (0);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//nyder2000@yahoo.es