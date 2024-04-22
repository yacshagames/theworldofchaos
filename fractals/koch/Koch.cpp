/*********************************************************************
::: THE KOCH CURVE :::
  Diagram of the Koch curve:

  "Starting from a segment which is divided into three equal parts.
  The central part is replaced by two segments of the same size as
  the eliminated. The same process is successively repeated for each
  formed segment".

Developed by:

	JOSE LUIS DE LA CRUZ LAZARO
	ramondc@hotmail.com

	UNIVERSIDAD NACIONAL DE INGENIERIA
	Faculty of Electrical and Electronic Engineering
	Lima-Peru

	YACSHA - Software & Desing
	>> The World of chaos - EL MUNDO DEL CAOS - Unlimited Programming

HISTORY...

  >> Version 2 - 10-IV-2024
	- Porting to VC++ 2017 using winbgi

  >> Version 1 - 28-XII-2001
	- First version for Borland C++ 3.1 and Turbo C 3.0

**********************************************************************/
#include "graphics.h"

int n = 0;

void koch(double x0, double y0, double x1, double y1) {

	line(x0, 480 - y0, x1, 480 - y1);
	delay(10);
	n++;

	double x2, y2, x3, y3, x4, y4, dx, dy;

	dx = (x1 - x0) / 3;
	dy = (y1 - y0) / 3;

	x2 = x0 + dx;
	y2 = y0 + dy;
	x3 = x2 + dx;
	y3 = y2 + dy;
	x4 = (x0 + x1) / 2 - 0.866025*dy;
	y4 = (y0 + y1) / 2 + 0.866025*dx;

	if (fabs(x0 - x2) > 1)
		koch(x0, y0, x2, y2);
	if (fabs(x2 - x4) > 1)
		koch(x2, y2, x4, y4);
	if (fabs(x4 - x3) > 1)
		koch(x4, y4, x3, y3);
	if (fabs(x3 - x1) > 1)
		koch(x3, y3, x1, y1);
}


void main() {

	// Init WinBGI window
	initwindow(1024, 768, "The world of chaos in C++ - Unlimited Programming");

	koch(10, 100, 600, 100);
	getch();

	closegraph();

}
