/**************************************************
RSFDEMO

Este programa es un demo de como utilizar GRAFXY.H y RSF.H
para graficar funciones en tiempo de ejecuci¢n, es decir
la funci¢n es ingresada a una cadena de texto, evaluada
por RSF.H y graficada por GRAFXY.H

programado por:
 JOSE LUIS DE LA CRUZ LAZARO
correos:
 jcruz@ec-red.com
 ramondc@hotmail.com
Pagina Web ( EL MUNDO DEL CAOS ):
 http://www.geocities.com/joseluisdl

  >> Version 2 - 21-III-2024
	- Update: Porting to VC++ 2017 using winbgi

***************************************************/
#include <iostream> //cin y cout
#include "conio.h" //clrscr() , getch()
#include "graphics.h" 
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

	cin >> Formula; //Se ingresa la funci¢n

	//se ingresa como argumento la ruta de la carpeta bgi
	//autoini("");//inicia el modo grafico, por defecto 16 colores
	int maxx = 1024;
	int maxy = 768;

	initwindow(maxx, maxy, "The world of chaos in C++ - Unlimited Programming");

	//se declara la regi¢n donde se graficar  la funci¢n
	CRegionXY Region(-10,   //x m¡nimo
		10,   //x m ximo
		-3,  //y m¡nimo
		3,   //y m ximo
		//argumentos opcionales:
		//coordenadas (en pixeles ) de la region donde se
		// graficara la funci¢n
		40,  //posici¢n izquierda
		80,  //posici¢n superior
		maxx, //posici¢n derecha
		maxy);//posici¢n inferior

//Pinta el fondo gris
	setfillstyle(1, LIGHTGRAY);
	bar(0, 0, maxx, maxy);

	//Pinta el fondo (azul claro) de la regi¢n virtual donde
	//se graficar  la funcion f(x)
	setfillstyle(1, LIGHTBLUE);
	bar(40, 80, maxx - 40, maxy - 40);

	//Pinta el marco (negro) de la regi¢n virtual
	setcolor(BLACK);
	rectangle(40, 80, maxx - 40, maxy - 40);

	setcolor(WHITE);
	outtextxy(10, 20, "The function is:");
	char txt[100];
	sprintf(txt, "f(x) = %s", Formula);
	outtextxy(10, 40, txt);


	double particion = 0.01; //partici¢n mas peque¤a de x

	Region.Ejes(); //grafica los ejes coordenados

	 //grafica la funci¢n f(x)
	GraficarFormula(Formula, //cadena de texto donde se encuentra f(x) (para este caso es una par bola )
		Region, //regi¢n donde se graficar  la funci¢n
		LIGHTGREEN, //argumento opcional; color del trazo (verde claro)
		CONECTAR, //argumento opcional; CONECTAR=conectar los puntos de la gr fica, si no se ingresa este argumento no se conecta los puntos
		particion);//argumento opcional; partici¢n mas peque¤a de x

	getch();//pone una pausa

	closegraph();//cierra el modo gr fico

}