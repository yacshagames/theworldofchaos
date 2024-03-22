/****************************************************************
GRAFXY

GRAFICADOR DE FUNCIONES EN 2D

JOSE LUIS DE LA CRUZ LAZARO UNI-FIEE
ramondc@hotmail.com

>> Version 2 - 22-III-2024
	- Update: Porting to VC++ 2017 using winbgi

>> Version 1.1 - 26/06/99

****************************************************************/

//#include "conio.h"
#include "graphics.h"
#include <cmath>
#include <iostream>
#include "rsf.h" 	// para que compile este programa copie rsf.h
					// en su directorio de includes
using namespace std;

void main()
{
//int gd=DETECT,gm;
//initgraph(&gd,&gm,""); //aqui cambie la ruta de su carpeta bgi
int maxx = 1024;
int maxy = 768;

double x,y;

//setcolor(2);
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(hConsole, 2);
cout << "Function Plotter for DOS" << endl;
//setcolor(6);
SetConsoleTextAttribute(hConsole, 6);
cout << "Jos‚ Luis De la Cruz L zaro - UNI-FIEE -1999-" << endl;
cout << "Consultas y sugerencias a: ramondc@hotmail.com" << endl;
//setcolor(3);
SetConsoleTextAttribute(hConsole, 3);
cout << "Enter the function to plot:" << endl << endl;
SetConsoleTextAttribute(hConsole, WHITE);
cout << "\n\t f(x) = ";

char Formula[100];
cin>>Formula;

initwindow(maxx, maxy, "The world of chaos in C++ - Unlimited Programming");

CFuncad formula(Formula, //cadena de texto que contiene la funcion f(x)
	"X"); //variable independiente que se reconocera en la cadena	

cleardevice();

//Se establece las particiones de la pantalla (RANGO DE VISION DE LA FUNCION)
double minX=-5,maxX=5;
double minY=-5,maxY=5;

int m,n;

//Se halla las coordenadas del origen deacuerdo con la particion dada (m,n)
m=(-minX)*maxx /(maxX-minX)+1; 	//eje X
n= maxy -(-minY)*maxy /(maxY-minY)+1;//eje Y

//Se grafican los ejes cartesianos
setcolor(14);
line(m,maxy,m,0);
line(0,n,maxx,n);

for(x=-5;x<5;x+=0.01){

//Funcion a graficar y=f(x)
y= formula.f(x);

m=(x-minX)*maxx /(maxX-minX)+1; 	//Conversion de real a entero x-->m
n= maxy -(y-minY)*maxy /(maxY-minY)+1;//Conversion de real a entero y-->n

putpixel(m,n,3);  //grafica la funcion en pantalla

}
getch();
closegraph();
}