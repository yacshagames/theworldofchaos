/**************************************************
PARABOLA

Plot a parabola on the screen...

This program is a demo of how to use GRAFXY.H

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

 >> Version 2 - 21-III-2024
	- Update graphics/gxydemo - Porting to VC++ 2017 using winbgi

***************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include "graphics.h"

//#include <conio.h> //getch()
#include "grafxy.h"

using namespace std;

int main()
{
	//se ingresa como argumento la ruta de la carpeta bgi
	//autoini("");//inicia el modo grafico, por defecto 16 colores
	initwindow(1024, 768, "The World of Chaos");


	//se declara la regi¢n donde se graficar  la función
	CRegionXY Region(-5,   //x mínimo
		5,   //x máximo
		-3,  //y mínimo
		3); //y máximo

	double x, //variable independiente
		dx = 0.01; //partición mas pequeña de x

	Region.Ejes(); //grafica los ejes coordenados

	//se varia x desde su valor mínimo a su máximo, con una partición de dx
	for (x = Region.xmin(); x < Region.xmax(); x += dx)
		//grafica un punto de la función
		Region.punto(x, // variable independiente
			x*x, //función f(x) a graficar (para este caso es una parábola )
			LIGHTGREEN, //color del trazo (verde claro)
			CONECTAR); //argumento opcional; CONECTAR=conectar los puntos de la gráfica, si no se ingresa este argumento no se conecta los puntos

	getch();//pone una pausa

	closegraph();//cierra el modo gráfico

	return 1;
}