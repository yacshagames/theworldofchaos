/****************************************************************************
LOAD A PCX ON SCREEN using WINBGIDLL

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

>> Version 2 - 22-III-2024
	- Update: Porting to VC++ 2017 using winbgi
	- Using IMGBGI to load PCX
	- LOAD A PCX ON SCREEN using WINBGI

>> Version 1.1 -  20/09/1999
	- LOAD A PCX ON SCREEN using the bgi SVGA256 driver
	- Class PCX 1.1

****************************************************************************/

#include "graphics.h"
#include "imgbgi.h"

void main(void)
{
	int maxx = 1024, maxy = 768;
	initwindow(maxx, maxy, "The world of chaos in C++ - Unlimited Programming");

	IMG pcx_mandel, pcx_uni;

	pcx_mandel.leer_cabecera("mandel.pcx");
	pcx_uni.leer_cabecera("logouni.pcx");

	// Plot PXC at center to screen
	int mandelx = maxx / 2 - pcx_mandel.ancho / 2;
	int mandely = maxy / 2 - pcx_mandel.ancho / 2;
	pcx_mandel.Dibujar( mandelx, mandely);	
	pcx_uni.Dibujar( maxx/2 - pcx_uni.ancho/2, mandely + pcx_mandel.alto+10);

	getch();

	closegraph();

}
