/*****************************************************************************
FractalX para la BGI
Mandelbrot's Beetle Fractal Plotter

Developed by:

	JOSE LUIS DE LA CRUZ LAZARO
	ramondc@hotmail.com

	UNIVERSIDAD NACIONAL DE INGENIERIA
	Faculty of Electrical and Electronic Engineering
	Lima-Peru

	YACSHA - Software & Desing
	>> The World of chaos - EL MUNDO DEL CAOS - Unlimited Programming

HISTORY...

 >> Version 2 - 12-IV-2024
	- Update fractals/fractalxbgi - Porting to VC++ 2017 using winbgi
	- The menu in text mode is made independent of the functions to
	  plot the fractal, in such a way as to have the GUI and the view
	  separated
	- The code of the old MouseBGI 1.x library is adapted to the new
	  version 3 adapted to WinBGI
	- The use of the rectangulo_inverso function is discarded for
	  "rectangle" function using setwritemode(XOR_PUT), which does the
	  same thing but natively
	- Stop using the winbgi putpixel function and use the CScreenBitmap
	  class instead, to speed up the drawing of the fractal on the screen

-Version 1.2 08/10/1999
 *Grafica el conjunto de Mandelbrot, utilizando solo el controlador bgi
  SVGA256.BGI, posee 5 modos de resolucion grafica y 256 colores
 *Se utilizan las cabeceras pcxbgi.h y mousebgi.h para cargar archivos
  graficos y el puntero del mouse respectivamente utilizando solo la bgi.
 *Se implementa el modo de graficacion tipo persiana, a diferencia
  del modo anterior que barria la pantalla de arriba a abajo.
 *Se implementa un menu en modo texto para cambiar la resolucion.
 *Con las teclas + y - se rotan los colores de la paleta en sentido
  horario y antihorario respectivamente.
 *se mejora la rutina para hacer zoom, ahora solo se hace un rectangulo
  proporcional a la pantalla para que la escala del fractal no se cambie
 *se a¤ade una pantalla de creditos.

-Version 1.1 02/05/1999
 *grafica solo el conjunto de Mandelbrot, utilizando la interrupcion 10h
  subfuncion 13h (320x200 de resolucion y 256 colores) incluye
  subrutinas graficas en lenguaje ensamblador, incluidas en la
  cabecera Color256.h
 *Se rota los colores de la paleta del fractal en sentido horario
 *Se implementa una rutina para el zoom, utilizando el mouse.

-version 1.0 17/09/1998
 Grafica los conjuntos de Julia, ulizando el modo bgi VGA 16 colores

*****************************************************************************/

#include <iostream>
#include "complex.h"
#include "graphics.h"
#include "conio.h"
#include <time.h>
#include "mousebgi.h"
#include "screenbitmap.h"

using namespace std;


int MAXX, MAXY;
long iter;

/*
void Paleta(unsigned char r, unsigned char g, unsigned char b)
{
	unsigned char cont1, Paleta[256][3];
	int cont;

	for (cont = 0; cont < 256; cont++)
	{
		Paleta[cont][0] = r * (cont + 1);
		Paleta[cont][1] = g * (cont + 1);
		Paleta[cont][2] = b * (cont + 1);
	}


	cont = 0;
	cont1 = 0;

	// El c¢digo que sigue a continuaci¢n pasa el contenido del array "Paleta"
	// a la paleta de la VGA 
	for (cont = 0; cont < 256; cont++)
	{
		outportb(0x03c8, cont);
		for (cont1 = 0; cont1 < 3; cont1++)
			outportb(0x03c9, Paleta[cont][cont1]);
		//cout<<Paleta
	}

}
*/

struct RegionXY
{
	double xmin;
	double xmax;
	double ymin;
	double ymax;
};

int zoom(RegionXY &PC)
{
	//mouseshow();

	//int x = 0, y = 0, c;
	int ButonDown = 1, Lx=0, Ly=0, x0=0, y0=0;

	MouseBGI::Event raton;	// estructura que contiene datos sobre la posicion y
					// la tecla presionada. Para mas informacion vea la
					// definicion de la estructura Evento en MOUSEBGI.H

	setwritemode(XOR_PUT);

	while (1) {

		raton = MouseBGI::Detect_click_or_key();
		raton.key = toupper(raton.key);

		switch (raton.key)
		{
		case 13:
		{
			double ex = (PC.xmax - PC.xmin) / getmaxx();//escalax
			double ey = (PC.ymax - PC.ymin) / getmaxy();//escalay

			PC.xmin = PC.xmin + (x0 - Lx) * ex;
			PC.ymax = PC.ymax - (y0 - Ly) * ey;
			PC.xmax = PC.xmin + 2 * Lx * ex;
			PC.ymin = PC.ymax - 2 * Ly * ey;
			return raton.key;
		}
		case 27:
		case 'M':
		case'+':
		case'-':
			return raton.key;
		}
		
		int &x = raton.x, &y = raton.y;

		switch (raton.event)
		{

		case MouseBGI::EVENT::LBUTTON_DOWN:

			if (ButonDown) {
				x0 = x;
				y0 = y;
				ButonDown = 0;
			} else
				rectangle(x0 - Lx, y0 - Ly, x0 + Lx, y0 + Ly);

			Lx = abs(x - x0);
			Ly = int(double(MAXY) * (double)(Lx) / double(MAXX));

			rectangle(x0 - Lx, y0 - Ly, x0 + Lx, y0 + Ly);
			break;

		case MouseBGI::EVENT::RBUTTON_DOWN:
			if (ButonDown == 0) {
				rectangle(x0 - Lx, y0 - Ly, x0 + Lx, y0 + Ly);
				ButonDown = 1;
			}
			break;
		}		
	}
}

/*
int Cambiar_Paleta_Fractal(char tecla, unsigned char r, unsigned char g, unsigned char b)
{
	unsigned char esc = 0, i = 1;

	if (tecla == '+' || tecla == '-')
	{
		mousehide();
		while (1)
		{

			switch (tecla)
			{
			case '+':
				i++;
				break;
			case'-':
				i--;
			}
			if (i)Paleta(r + i, g + i, b + i);
			delay(400);
			if (kbhit())esc = getch();
			if (esc == 13)return 1;
			if (esc == '+' || esc == '-') tecla = esc;

		}
	}
	return 0;
}
*/

void ModoGrafico(int resolucion)
{
	std::string sTittle = "The world of chaos in C++ - Unlimited Programming";

	//se instala la resolucion deseada
	switch (resolucion)
	{
	case 0:
		closegraph();
		break;
	case 1: //_320x200:
		initwindow(320, 200, sTittle.c_str());
		break;
	case 2: //_640x400:
		initwindow(640, 400, sTittle.c_str());
		break;
	case 3: // _640x480:
		initwindow(640, 480, sTittle.c_str());
		break;
	case 4: // _800x600:
		initwindow(800, 600, sTittle.c_str());
		break;
	case 5: //_1024x768:
		initwindow(1024, 768, sTittle.c_str());
	}

	if( resolucion > 0 )
		// starts register of mouse events by MouseBGI class
		MouseBGI::RegisterMouseEvents();
 }


void Mandelbrot1(RegionXY PC, double& DIVERGE, const unsigned int& ITERMAX, CScreenBitmap& scrBitmap)
{

	unsigned int  i, j, ITERACION, des = 10, k, drawblind_step=3;

	complex Z, C;

	int maxy = MAXY, maxx = MAXX;

	//Modo de graficacion: TIPO PERSIANA
	for (k = 0; k < des; k++) {

		for (j = k; j < maxy; j += des)
		{
			if (kbhit())return /*getch()*/;
			for (i = 0; i < maxx; i++)
			{

				C = complex(PC.xmin + ((PC.xmax - PC.xmin)*i) / maxx,
					PC.ymax - ((PC.ymax - PC.ymin)*j) / maxy);
				ITERACION = 0;
				Z = 0;

				do
				{
					Z = Z * Z + C;
					ITERACION++;
					if (abs(Z) > DIVERGE)break;
				} while (ITERACION < ITERMAX);

				if (ITERACION != ITERMAX)
					scrBitmap.putpixel(i, j, ITERACION);
			}
		}

		// Shows the rolling shutter effect every certain number of steps, while the fractal is plotted
		// Allows the user to see a preview of the fractal plot while it is calculated
		if( k%drawblind_step ==0)
			scrBitmap.draw(0,0);
	}

}

struct cuadricula
{
	int xmin;
	int ymin;
	int Ladox;
	int Ladoy;
};


void mandelpunto(int &i, int &j, RegionXY &PC, const double& DIVERGE, const unsigned int& ITERMAX, CScreenBitmap& scrBitmap)
{
	unsigned int  ITERACION = 0;
	complex  Z = 0;

	complex C = complex(PC.xmin + ((PC.xmax - PC.xmin)*i) / MAXX,
		PC.ymax - ((PC.ymax - PC.ymin)*j) / MAXY);
	do
	{
		Z = Z * Z + C;
		ITERACION++;
		if (abs(Z) > DIVERGE)break;
	} while (ITERACION < ITERMAX);

	if (ITERACION != ITERMAX)
		scrBitmap.putpixel(i, j, ITERACION);

	iter++;

	// Shows the Tesseral X effect every certain number of iterations, while the fractal is plotted
	// Allows the user to see a preview of the fractal plot while it is calculated
	if (iter % 50000 == 0)
		scrBitmap.draw(0, 0);
}

int analizar_region(int &rgbColor, cuadricula &rect, int &xmax, int &ymax, CScreenBitmap& scrBitmap)
{
	int i, desx = rect.Ladox / 4, desy = rect.Ladoy / 4;
	rgbColor = scrBitmap.getpixelRGB(rect.xmin, rect.ymin);

	for (i = 0; i < 3; i++)
	{
		if(rgbColor != scrBitmap.getpixelRGB(xmax - i * desx, rect.ymin) ||
			rgbColor != scrBitmap.getpixelRGB(rect.xmin + i * desx, ymax) ||
			rgbColor != scrBitmap.getpixelRGB(rect.xmin, rect.ymin + i * desy) ||
			rgbColor != scrBitmap.getpixelRGB(xmax, ymax - i * desy) )
			return 0;		
	}

	return 1;
}



void Mandelbrot2(RegionXY &PC, cuadricula rect, const double& DIVERGE, const unsigned int& ITERMAX, CScreenBitmap& scrBitmap )
{

	// getch();gotoxy(20,20);cout<<rect.Ladox;
	int i, j, xmax = rect.xmin + rect.Ladox, ymax = rect.ymin + rect.Ladoy,
		xmed = rect.xmin + rect.Ladox / 2, ymed = rect.ymin + rect.Ladoy / 2;
	if (rect.Ladox == MAXX-1)
	{
		for (i = rect.xmin; i < rect.Ladox; i++)
		{
			mandelpunto(i, rect.ymin, PC, DIVERGE, ITERMAX, scrBitmap);
			mandelpunto(i, ymax, PC, DIVERGE, ITERMAX, scrBitmap);
		}

		for (j = rect.ymin; j < rect.Ladoy; j++)
		{
			mandelpunto(rect.xmin, j, PC, DIVERGE, ITERMAX, scrBitmap);
			mandelpunto(xmax, j, PC, DIVERGE, ITERMAX, scrBitmap);
		}

	}

	int rgbColor;
	if (analizar_region(rgbColor, rect, xmax, ymax, scrBitmap))
	{
		//setfillstyle(1, color);
		scrBitmap.barRGB(rect.xmin + 1, rect.ymin + 1, xmax - 1, ymax - 1, rgbColor);
		return;
	}


	if (rect.Ladox < 8)
	{

		for (j = rect.ymin + 1; j < ymax; j++)
			for (i = rect.xmin + 1; i < xmax; i++)
				mandelpunto(i, j, PC, DIVERGE, ITERMAX, scrBitmap);
		return;
	}

	for (j = rect.ymin + 1; j < ymax; j++)
		mandelpunto(xmed, j, PC, DIVERGE, ITERMAX, scrBitmap);

	for (i = rect.xmin + 1; i < xmed; i++)
		mandelpunto(i, ymed, PC, DIVERGE, ITERMAX, scrBitmap);

	for (i = xmed + 1; i < xmax; i++)
		mandelpunto(i, ymed, PC, DIVERGE, ITERMAX, scrBitmap);

	int Ladox = rect.Ladox / 2, Ladoy = rect.Ladoy / 2;
	cuadricula rect1[4] =
	{
	 rect.xmin, rect.ymin, Ladox, Ladoy,
	 xmed, rect.ymin, rect.Ladox - Ladox, Ladoy,
	 xmed, ymed, rect.Ladox - Ladox, rect.Ladoy - Ladoy,
	 rect.xmin, ymed, Ladox, rect.Ladoy - Ladoy
	};
	
	for (i = 0; i < 4; i++)
		Mandelbrot2(PC, rect1[i], DIVERGE, ITERMAX, scrBitmap);

}


void Menu(unsigned int& option, unsigned int& mode)
{
	ModoGrafico(0);

	int resolucion = 0;

	cout << "FractalX-BGI\n"
		<< "GRAFICADOR DE FRACTALES\n"
		<< "\nTeclas que se usaran durante el ploteo del fractal:"
		<< "\n\nSeleccione un rectangulo con el mouse y luego pulse ENTER para Hacer ZOOM"
		<< "\nUse clic derecho para borrar el rectángulo de zoom"
		<< "\n\nESC: para cancelar la graficacion"
		<< "\ntecla M: para volver a este Menu"
		<< "\n+,- : cambia la paleta de colores del fractal para cancelar pulse ENTER"		
		<< "\n\n(1) 320x200\n"
		<< "(2) 640x400\n"
		<< "(3) 640x480\n"
		<< "(4) 800x600\n"
		<< "(5) 1024x768\n"
		<< "(6) Acerca del Autor\n"
		<< "(7) Salir\n"
		<< "\nElija su resolucion: ";

	cin >> option;



	if (option > 6 || option < 1) {
		option = 0;
		mode = 0;
		return; // Salir
	}

	// mostrar creditos del autor
	if (option == 6)
	{
		/*ModoGrafico(1);
		setgraphmode(1);
		PCX logos;
		logos.Dibujar(10, 150, 16, "logouni.pcx");
		logos.Dibujar(0, 0, 32, "fxlogo.pcx");
		setrgbpalette(0, 0, 0, 0);

		setcolor(LIGHTRED);
		outtextxy(220, 70, "FractalX para DOS versi¢n 1.2");
		outtextxy(220, 80, "GRAFICADOR DE FRACTALES");
		setcolor(LIGHTGREEN);
		outtextxy(160, 150, "Programado por: Jos‚ Luis De la Cruz Lazaro");
		setcolor(LIGHTMAGENTA);
		outtextxy(160, 170, "Universidad Nacional de Ingenier¡a - Lima Per£ - 1999");
		setcolor(YELLOW);
		outtextxy(160, 190, "Por el momento solo tengo implementado");
		outtextxy(160, 200, "el escarabajo de Mandelbrot");
		setcolor(WHITE);
		outtextxy(160, 220, "Pulse cualquier tecla para Salir");
		getch();*/

		option = 0;
		mode = 0;
	}
	else
		//if (!Cambiar_Paleta_Fractal(tecla, 3, 2, 1))
	{
		//cleardevice();
		clrscr();
		cout << endl << endl;
		cout << " (1) Diagramado Persiana" << endl << endl;
		cout << " (2) Diagramado TesseralX" << endl << endl;
		cout << " Ingrese el tipo de diagramado: ";
		cin >> mode;
	}

}

int main()
{			
	//PROCESO ESCARABAJO DE MANDELBROT

	//////////////////////////
	double DIVERGE = 200;   // valor de divergencia
	unsigned int ITERMAX = 500;	// iteracion maxima

	// Variables de GUI
	char tecla = 0;
	unsigned int mode, option;

	clock_t inicio, fin;

	do
	{
		RegionXY PlanoComplejo = { -3,2,-2,2 };

		Menu(option, mode);

		if (option == 0)
			break;// Salir

		ModoGrafico(option);

		MAXX = getmaxx()+1;
		MAXY = getmaxy()+1;

		cuadricula rect = { 0,0,MAXX-1,MAXY-1 };

		CScreenBitmap scrBitmap(MAXX, MAXY);
		scrBitmap.setpalette(10, 5, 1);

		do {

			//cleardevice();
			scrBitmap.clear();

			iter = 0;

			inicio = clock();

			switch (mode)
			{
			case 1:  
				Mandelbrot1(PlanoComplejo, DIVERGE, ITERMAX, scrBitmap);
				iter = MAXX * MAXY;
				break;
			case 2:				
				Mandelbrot2(PlanoComplejo, rect, DIVERGE, ITERMAX, scrBitmap);
				break;
			}

			scrBitmap.draw(0,0);

			fin = clock();
			cout << "\n\n" << double((fin - inicio)) / CLK_TCK << "\nIter: " << iter;

			tecla = zoom(PlanoComplejo);

			switch (tecla) {
			case 'M':
				break;
			case '+':
			case '-':
				//Cambiar_Paleta_Fractal(tecla, 3, 2, 1);
				break;
			}
		} while (tecla != 27 && tecla!='M');

	} while (1);

	ModoGrafico(0);

	return 1;
}