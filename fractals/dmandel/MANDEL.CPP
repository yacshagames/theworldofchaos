/*****************************************************************************
MANDELBROT SET PLOTTER
BY JOSE LUIS DE LA CRUZ LAZARO

>> Version 2 - 25 - III - 2024
- Update graphics/dmandel - Porting to VC++ 2017 using winbgi

  >> Versión 1.5 23-II-2002
 Ejemplo simple de diagramación de fractales.
 Optimización de la versión 1.0, ahora se puede personalizar la paleta
 de 256 colores que utilizará nuestro fractal, mediante la función
 setrgbpallete de la BGI.

>> Version 1 - 01 - XI - 1999
- First version for Borland C++ 3.1 and Turbo C 3.0

ramondc@hotmail.com
Pagina web: www.geocities.com/SiliconValley/Screen/2767/jldl.htm");

*****************************************************************************/

#include "graphics.h"
//#include "conio.h"
#include "complex.h"

void CambiarColores(int red, int green, int blue) {

	for (int i = 0; i < 256; i++)
		setrgbpalette(i, i*red, i*green, i*blue);
}


int main()
{

	double
		//////////////////////////
		//COORDENADAS DEL PLANO COMPLEJO
		REALMIN = -2,
		REALMAX = 1,
		IMAGMIN = -1.2,
		IMAGMAX = 1.2,
		//////////////////////////
		DIVERGE = 100,   //valor de divergencia
		ITERMAX = 200; //iteracion maxima

	  /*
	  // coordenadas del Mandelbrot-Rayos

	  double x1 = -1.19172737578084;
	  double y1 = 0.307841264022174;
	  double x2 = -1.18215986353386;
	  double y2 = 0.298345102426701;

	  REALMIN=x1;  //{PROCURAR QUE REALMAX-REALMIN SEA IGUAL A                   }
	  REALMAX=x2;   //{COMPLEJOMAX-COMPLEJOMIN, PARA EVITAR FIGURAS DISTORSIONADAS}
	  COMPLEJOMIN=y1;    //{MODIFICAR LOS VALORES PARA HACER ZOOM}
	  COMPLEJOMAX=y2;
	  */

	int  i, j, ITERACION;

	complex Z, C;

	// Init WinBGI window
	int maxx = 1024, maxy = 768;
	initwindow(maxx + 10, maxy + 10, "The world of chaos in C++ - Unlimited Programming");

	//muestra una precarga mientras se carga los colores
	  //en la paleta
	setrgbpalette(255, 255, 255, 255); //color blanco
	setcolor(255);
	outtextxy(280, 240, "CARGANDO...");

	//Cambia la paleta de 256 colores en funcion lineal a los tonos
	//red=10 , green=5, blue=1
	CambiarColores(10, 5, 1);

	//borra la precarga
	setcolor(0);
	outtextxy(280, 240, "CARGANDO...");

	//TITULOS Y CREDITOS
	setcolor(115);
	outtextxy(130, 5, "THE MANDELBROT-RAYOS: Z^2+C");
	setcolor(10);
	settextstyle(7, 1, 1);
	outtextxy(10, 5, "<< MANDELX 1.5 >>");
	setcolor(114);
	settextstyle(7, 0, 1);
	outtextxy(220, 450, "por YACSHA - Software & Desing");
	setcolor(12);
	settextstyle(10, 1, 1);
	outtextxy(10, 230, "UNI-FIEE");
	rectangle(120, 20, 550, 450);

	//PROCESO DE DIAGRAMADO
	for (j = 0; j < maxy; j++)
		for (i = 0; i < maxx; i++)
		{

			C = complex((REALMAX - REALMIN) / maxx * i + REALMIN,
				IMAGMAX - (IMAGMAX - IMAGMIN) / maxy * j);
			ITERACION = 0;

			Z = 0;
			do {

				Z = Z * Z + C; //cambiar aqui la ecuacion

				ITERACION++;
				if (abs(Z) > DIVERGE)break;
			} while (ITERACION < ITERMAX);

			if (ITERACION != ITERMAX)putpixel(i, j, ITERACION + 50);

		}


	getch();
	setcolor(GREEN);
	printf("<< Mandel 2.0 >>\n");
	printf("Programmed by Jose Luis De la Cruz Lazaro\n\n\n\n\n\n\n\n\n");
	closegraph();
	return 1;
}