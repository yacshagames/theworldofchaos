/**************************************************
PARABOLA
Grafica una parabola en la pantalla...

Este programa es un demo de como utilizar GRAFXY.H

programado por:
 JOSE LUIS DE LA CRUZ LAZARO
correos:
 jcruz@ec-red.com
 ramondc@hotmail.com
Pagina Web ( EL MUNDO DEL CAOS ):
 http://www.geocities.com/joseluisdl

***************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include "graphics.h"

//#include <conio.h> //getch()
#include "grafxy.h"

using namespace std;

int APIENTRY WinMain
(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{	

	//se ingresa como argumento la ruta de la carpeta bgi
	//autoini("");//inicia el modo grafico, por defecto 16 colores
	initwindow(1024, 768, "El mundo del caos");


	//se declara la regi¢n donde se graficar  la funci¢n
	CRegionXY Region(-5,   //x m¡nimo
		5,   //x m ximo
		-3,  //y m¡nimo
		3); //y m ximo

	double x, //variable independiente
		dx = 0.01; //partici¢n mas peque¤a de x

	Region.Ejes(); //grafica los ejes coordenados

	//se varia x desde su valor m¡nimo a su m ximo, con una partici¢n de dx
	for (x = Region.xmin(); x < Region.xmax(); x += dx)
		//grafica un punto de la funci¢n
		Region.punto(x, // variable independiente
			x*x, //funci¢n f(x) a graficar (para este caso es una par bola )
			LIGHTGREEN, //color del trazo (verde claro)
			CONECTAR); //argumento opcional; CONECTAR=conectar los puntos de la gr fica, si no se ingresa este argumento no se conecta los puntos

	getch();//pone una pausa

	closegraph();//cierra el modo gr fico

}