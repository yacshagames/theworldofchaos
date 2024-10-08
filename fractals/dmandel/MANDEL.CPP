/*****************************************************************************
DMANDEL - MANDELBROT SET PLOTTER

At the request of several friends, I upload this program that diagrams the
Mandelbrot set, using a short, simple and easy to understand code
(compared to FractalX), in addition to serving as an aid for those who want
to start programming your own fractals using the powerful bgi routines
that Turbo C has.

It shows in a simple way how to use the SVGA256.BGI bgi driver,
which works with 256 colors.

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

  >> Version 3 - 11-IV-2024
	- Update graphics/dmandel - Porting to VC++ 2017 using winbgi
	- Porting to VC++ 2017 completed
	- Update credits and history
	- The credits have been translated from Spanish to English
	- Update from version 1.0(01-XI-1999) to version 1.5(23-II-2002)
	- Simple example of fractal diagramming. Optimization of version 1.0,
	  now you can customize the palette of 256 colors that our fractal will
	  use, using the setrgbpallete function of the BGI
	- Update code format
	- Update credits
	- Enabled coordinates for plot "Lightning Mandelbrot"
	- Stop using the winbgi putpixel function and use the CScreenBitmap
	  class instead, to speed up the drawing of the fractal on the screen
	- The conio.h library is used to display the end credits

  >> Version 2 - 25-III-2024
	- Update graphics/dmandel - Porting to VC++ 2017 using winbgi

    - Simple example of fractal diagramming. Optimization of version 1.0,
	  now you can customize the palette of 256 colors that our fractal will use,
	  using the setrgbpallete function of the BGI

  >> Version 1 - 01-XI-1999
    - First version for Borland C++ 3.1 and Turbo C 3.0
	
*****************************************************************************/

#include "graphics.h"
#include "conio.h"
#include "complex.h"
#include "screenbitmap.h"
#include <iostream>
using std::cout;

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

	  
	// Coordinates for Lightning-Mandelbrot

	double x1 = -1.19172737578084;
	double y1 = 0.307841264022174;
	double x2 = -1.18215986353386;
	double y2 = 0.298345102426701;

	REALMIN = x1;  //{PROCURAR QUE REALMAX-REALMIN SEA IGUAL A                   }
	REALMAX = x2;   //{COMPLEJOMAX-COMPLEJOMIN, PARA EVITAR FIGURAS DISTORSIONADAS}
	IMAGMIN = y1;    //{MODIFICAR LOS VALORES PARA HACER ZOOM}
	IMAGMAX = y2;
	  
	int  i, j, ITERACION;

	complex Z, C;

	// Init WinBGI window
	int maxx = 1024, maxy = 768;
	initwindow(maxx + 10, maxy + 10, "The world of chaos in C++ - Unlimited Programming");	

	CScreenBitmap scrBitmap(maxx, maxy);

	//Cambia la paleta de 256 colores en funcion lineal a los tonos
	//red=10 , green=5, blue=1
	scrBitmap.setpalette(10, 5, 1);

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

			if (ITERACION != ITERMAX)
				scrBitmap.putpixel(i, j, ITERACION + 50);
				

		}

	scrBitmap.draw(0,0);

	getch();	
	closegraph();

	textcolor(LIGHTRED);
	cout << "<< DMandel >>\n";
	textcolor(LIGHTCYAN);
	cout << "Programmed by Jose Luis De la Cruz Lazaro - YACSHA-Software\n\n\n\n\n\n\n\n\n";	
	textcolor(LIGHTGRAY);
	
	return 1;
}