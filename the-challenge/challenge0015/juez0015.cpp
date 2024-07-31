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

	// Variable que contiene los meses del año para el calendario.
	char mesc[][20] = { "       Enero","      Febrero","       Marzo",
	"       Abril","        Mayo","       Junio","       Julio",
	"       Agosto","     Septiembre","      Octubre","     Noviembre",
	"     Diciembre" };

	int semana[6][7] = { 0 }; // Matriz para contener el calendario del mes.
	int *p;    // Puntero que manejar  la matriz del calendario del mes.

	clrscr();

	printf("\ndía= "); //
	scanf("%i", &dia);  //
	printf("\nmes= "); //  Entrada de la Fecha
	scanf("%i", &mes);  //
	printf("\naño= "); //
	scanf("%i", &anho); //

	ds = (((1461 * ((anho + 4800) + ((mes - 14) / 12))) >> 2)      // Día de la semana
		+ ((367 * (mes - 2 - 12 * ((mes - 14) / 12))) / 12)          // Lunes = 0 ...
		- (3 * (((anho + 4800) + ((mes - 14) / 12) + 100) / 100) >> 2) // Domingo = 6
		+ dia - 32075L) % 7;                               //

	switch (mes)
	{
	case 1:case 3:case 5:case 7:case 8:case 10:      //
	case 12:mesd = 31; break;                           // Número de días
	case 4:case 6:case 9:case 11:mesd = 30; break;      // del mes...
	case 2:mesd = 28; if (bisiesto(anho)) mesd = 29; break; //
	}

	ds = ds - (dia % 7 - 1);  // Punto clave de la ubicación del día 1
	if (ds < 0)ds += 7;    // Corrección, caso de ser necesaria  ;-)

	printf("\n\n %s", mesc[mes - 1]); // Impresión del Título del mes.
	printf("\n Lu Ma Mi Ju Vi Sa Do\n"); // Encabezados de los días.

	p = &semana[0][0]; // Ubicación del puntero sobre la matriz del mes.

	for (i = 0; i < mesd; i++) // Ubicación de los días en la matriz
		*(p + ds + i) = i + 1;     // a través del puntero al primer elemento.

	for (j = 0; j < 6; j++) // Ciclo de impresión
	{
		for (i = 0; i < 7; i++)
		{
			if (semana[j][i] == 0)
			{
				printf("   "); // Si no es un día del mes.
			}
			else
			{
				cprintf("%3d", semana[j][i]); // Si es un día del mes.
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