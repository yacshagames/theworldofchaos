/**************************************************
RSFDEMO

This program is a demo of how to use GRAFXY.H and
RSF.H to plot functions at runtime, that is,
the function is entered into a text string,
evaluated by RSF.H and plotted by GRAFXY. h

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
	- Update: Porting to VC++ 2017 using winbgi

***************************************************/
#include <iostream> //cin y cout
#include "graphics.h" 
#include "conio.h" //clrscr() , getch()
#include "RSF.h" //Reconocedor Sintactico de Funciones desde una cadena de texto
#include "grafxy.h" //clase para graficar funciones bidimensionales

using namespace std;

//Grafica la funcion contenida en la cadena de texto Formula
void GraficarFormula(char *Formula, CRegionXY Region,
	char color = LIGHTBLUE, char conectar = CONECTAR,
	float Particion = 0.01)
{

	float x, y;

	CFuncad formula(Formula, //cadena de texto que contiene la funcion f(x)
		"X"); //variable independiente que se reconocera en la cadena

//Funcion a graficar y=f(x)
	for (x = Region.xmin(); x < Region.xmax(); x += Particion)
	{
		if (!formula.error)
			Region.punto(x, formula.f(x), color, conectar);
		else
			Region.punto(x, formula.f(x), LIGHTRED, conectar);
	}

}


void main()
{
	clrscr();
	cout << "DEMO OF THE SYNTACTIC FUNCTION RECOGNIZER (RSF.H):\n\n";
	cout << "Enter the function f(x) you want to plot: ";
	cout << "\n\nExample: \n\t\t0.5*exp(-x/5)*sin(pi*x)"; //damped movement"
	cout << "\n\t\t3/2*x^2-5/4*x+1/2"; //even ball"

	cout << "\n\nThe mathematical functions that can be recognized immediately are:";
	cout << "\nsin (SINE), cos (COSINE), tan (TANGENT), exp (EXPONENTIAL), \nsqr (SQUARE ROOT), log (NATURAL LOGARITHM)";
	cout << "\npi (constant Pi = 3.14159...)";
	cout << "\nNOTE: It does not matter if the characters are lowercase or uppercase...";

	cout << "\n\nNormally the plot will appear in a GREEN line, but if the graph shows a RED line, it means that the function is not defined in that interval. As an example, try graphing 0.2*sqr(x^2- 25)";

	cout << "\n\nf(x) = ";

	char Formula[100];

	cin >> Formula; //Se ingresa la función

	//se ingresa como argumento la ruta de la carpeta bgi
	//autoini("");//inicia el modo grafico, por defecto 16 colores
	int maxx = 1024;
	int maxy = 768;

	initwindow(maxx, maxy, "The world of chaos in C++ - Unlimited Programming");

	//se declara la región donde se graficará la función
	CRegionXY Region(-10,   //x mínimo
		10,   //x máximo
		-3,  //y mínimo
		3,   //y máximo
		//argumentos opcionales:
		//coordenadas (en pixeles ) de la region donde se
		// graficara la función
		40,  //posición izquierda
		80,  //posición superior
		maxx, //posición derecha
		maxy);//posición inferior

//Pinta el fondo gris
	setfillstyle(1, LIGHTGRAY);
	bar(0, 0, maxx, maxy);

	//Pinta el fondo (azul claro) de la región virtual donde
	//se graficará la funcion f(x)
	setfillstyle(1, LIGHTBLUE);
	bar(40, 80, maxx - 40, maxy - 40);

	//Pinta el marco (negro) de la región virtual
	setcolor(BLACK);
	rectangle(40, 80, maxx - 40, maxy - 40);

	setcolor(WHITE);
	outtextxy(10, 20, "The function is:");
	char txt[100];
	sprintf(txt, "f(x) = %s", Formula);
	outtextxy(10, 40, txt);


	double particion = 0.01; //partición mas pequeña de x

	Region.Ejes(); //grafica los ejes coordenados

	 //grafica la función f(x)
	GraficarFormula(Formula, //cadena de texto donde se encuentra f(x) (para este caso es una parábola )
		Region, //región donde se graficará la función
		LIGHTGREEN, //argumento opcional; color del trazo (verde claro)
		CONECTAR, //argumento opcional; CONECTAR=conectar los puntos de la gráfica, si no se ingresa este argumento no se conecta los puntos
		particion);//argumento opcional; partición mas pequeña de x

	getch();//pone una pausa

	closegraph();//cierra el modo gráfico

}