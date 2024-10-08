/****************************************************************
GRAFXYZ

3D FUNCTION PLOTTER
in Cartesian and polar coordinates

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

>> Version 1.3 - 26/06/99

****************************************************************/
#pragma once
//#include <conio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "graphics.h"
//#include <iostream>
#include "vector.h"	//para que compile este programa copie vector.h
					//en su directorio de includes
//using namespace std;

int Zcolor(double z, double maxZ) {
	int color = (maxZ - z) * 14 / (2 * maxZ);
	color++;//retorna colores entre 1 y 15
	return color;
}

void grafxyz()
{
	//int gd=DETECT,gm;
	//initgraph(&gd,&gm,""); //aqui cambie la ruta de su carpeta bgi
	initwindow(1024, 768, "The world of chaos in C++ - Unlimited Programming");

	vector O(320, 240), I(-sin(45 * M_PI / 180), cos(45 * M_PI / 180))
		, J(1, 0), K(0, -1);
	//I: direccion unitaria del eje X
	//J: direccion unitaria del eje Y
	//K: direccion unitaria del eje Z

	double d = 239, maxX = 10, maxY = 10, maxZ = 10, rot = 0;
	//d: longitud en pixeles del eje Z = eje X = eje Y

	//Activar para simetria
	//maxY=maxX;maxZ=maxX;
	rot = rot * M_PI / 180;
	I = cos(rot)*I + sin(rot)*J;
	J = -sin(rot)*I + cos(rot)*J;

	//Trazado de los Ejes
	line(O.x, O.y, (O + d * I).x, (O + d * I).y);
	line(O.x, O.y, (O + d * J).x, (O + d * J).y);
	line(O.x, O.y, (O + d * K).x, (O + d * K).y);

	int m, n, p;
	//Coordenadas Cartesianas
	double x, y;
	vector F, f;

	/*
	//Coordenadas Polares
	double r,w;

	for(r=0;r<=10;r+=0.01){
	for(w=0;w<2*M_PI;w+=0.01){
	x=r*cos(w);
	y=r*sin(w);
	*/


	for (x = -maxX; x < maxX; x += 0.06) {
		for (y = -maxY; y < maxY; y += 0.06) {


			//F(x,y,z)= ( x, y, cos(x*y) )
			//Aqui cambia tu funcion
			F = vector(x, y, cos(x*y));

			m = F.x*d / maxX;
			n = F.y*d / maxY;
			p = F.z*d / maxZ;

			f = O + m * I + n * J + p * K;

			if (!getpixel(f.x, f.y))putpixel(f.x, f.y, Zcolor(F.z, maxZ));
		}
	}

	outtextxy(500, 450, "z = cos(x*y)");

	getch();
	closegraph();


}
