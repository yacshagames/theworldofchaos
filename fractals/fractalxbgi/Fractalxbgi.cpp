/*****************************************************************************
FractalX for WinBGI
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

 >> Version 2 - 14-IV-2024
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
	- The Change_Fractal_Palette function is enabled, to be able to
	  change the color palette of the fractal using the + and - keys,
	  using the CScreenBitmap version 2 class
	- The About screen is enabled showing the software credits
	- The *.pcx files loaded in the credits are changed to *.bmp files,
	  in such a way as to load them natively using the readimagefile
	  function of WinBGI
	- Translate GUI, credits and history version, from spanish to english
	- Add colors to console GUI
	- The modifications made in version 1.3 are added to the History version
	- After each plot the coordinates (xmin,xmax) and (ymin, ymax) are shown.
	  In addition to formatting the elapsed seconds and the number of
	  iterations displayed
	- The change parameters option is added, to change the parameters of
	  maximum divergence, maximum iteration, and initial coordinates of the
	  corners of the complex plane, this last option is great for loading
	  a particular area of the mandelbrot beetle that you liked, just knowing
	  its coordinates

>> Version 1.3 - 02-XI-1999
	- The Blind plotting mode is added (fuction Mandelbrot1), in such a
	  way as to show the plot progressively as if it were a blind
	- The TesseralX plotting mode is added (function Mandelbrot2),
	  which uses an algorithm that divides the screen into 4 quadrants and
	  in each quadrant analyzes whether the 4 corners of the quadrant have
	  the same color, if so, a rectangle filled with the color of one of
	  them is painted the corners and otherwise the same algorithm is
	  carried out in each of the quadrants recursively.
	  This algorithm is more efficient when the fractal has several areas
	  with the same color, since it avoids iterating the complex equation
	  in the quadrants that have the same color in their corners.

 >> Version 1.2 - 08-X-1999
	- Plots the Mandelbrot set, using only the SVGA256.BGI bgi driver,
      has 5 graphic resolution modes and 256 colors
	- The pcxbgi.h and mousebgi.h headers are used to load graphic files
	  and the mouse pointer respectively using only the bgi.
	  previous mode that swept the screen from top to bottom.
	- With the + and - keys the colors of the palette are rotated
	  clockwise and counterclockwise respectively.
	- the routine for zooming is improved, now only a rectangle is made
	  proportional to the screen so that the scale of the fractal
	  is not changed
	- a credits screen is added.

 >> Version 1.1 - 02-V-1999
	- Plots only the Mandelbrot set, using the interrupt 10h subfunction 13h
	  (320x200 resolution and 256 colors) includes graphical subroutines in
	  assembly language, included in the Color256.h header
	- The colors of the fractal palette are rotated clockwise
	- A routine is implemented for zooming, using the mouse.

 >> Version 1.0 - 17-IX-1999
	- Plot Julia's sets, using the 16-color VGA bgi mode

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
			if (Lx > 0 && Ly > 0) {
				double ex = (PC.xmax - PC.xmin) / MAXX;//escalax
				double ey = (PC.ymax - PC.ymin) / MAXY;//escalay

				PC.xmin = PC.xmin + (x0 - Lx) * ex;
				PC.ymax = PC.ymax - (y0 - Ly) * ey;
				PC.xmax = PC.xmin + 2 * Lx * ex;
				PC.ymin = PC.ymax - 2 * Ly * ey;
				return raton.key;
			}
		break;
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
				// Erase rectangle selection
				rectangle(x0 - Lx, y0 - Ly, x0 + Lx, y0 + Ly);
				// Reset flag
				ButonDown = 1;
				// Reset rectangle selectión
				Lx = Ly = 0.0;
			}
			break;
		}		
	}
}


int Change_Fractal_Palette(char tecla, unsigned char r, unsigned char g, unsigned char b, CScreenBitmap& scrBitmap)
{
	unsigned char esc = 0, i = 1;

	if (tecla == '+' || tecla == '-')
	{
		//mousehide();
		while (1)
		{

			switch (tecla)
			{
			case '+':
				i++;
				break;
			case'-':
				i--;
				break;
			}
			if (i) {
				//Paleta(r + i, g + i, b + i);
				scrBitmap.setpalette(r + i, g + i, b + i);
				scrBitmap.draw();
			}
			
			delay(100);
			
			if (kbhit())
				esc = getch();
			
			if (esc == 13)
				return 1;

			if (esc == '+' || esc == '-')
				tecla = esc;

		}
	}
	return 0;
}


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

int analizar_region(unsigned char &paletteColor, cuadricula &rect, int &xmax, int &ymax, CScreenBitmap& scrBitmap)
{
	int i, desx = rect.Ladox / 4, desy = rect.Ladoy / 4;
	paletteColor = scrBitmap.getpixel(rect.xmin, rect.ymin);

	for (i = 0; i < 3; i++)
	{
		if( paletteColor != scrBitmap.getpixel(xmax - i * desx, rect.ymin) ||
			paletteColor != scrBitmap.getpixel(rect.xmin + i * desx, ymax) ||
			paletteColor != scrBitmap.getpixel(rect.xmin, rect.ymin + i * desy) ||
			paletteColor != scrBitmap.getpixel(xmax, ymax - i * desy) )
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

	unsigned char paletteColor;
	if (analizar_region(paletteColor, rect, xmax, ymax, scrBitmap))
	{
		//setfillstyle(1, color);
		scrBitmap.bar(rect.xmin + 1, rect.ymin + 1, xmax - 1, ymax - 1, paletteColor);
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


void Menu(unsigned int& option, unsigned int& mode, RegionXY& PlanoComplejo, double& DIVERGE, unsigned int& ITERMAX )
{
	ModoGrafico(0);
	clrscr();

	int resolucion = 0;

	textcolor(LIGHTCYAN);
	cout << "FractalX for WinBGI\n";
	textcolor(LIGHTRED);
	cout << "MANDELBROT'S BEETLE FRACTAL PLOTTER\n";

	textcolor(WHITE);
	cout << "\nKeys that will be used during fractal plotting:"
		<< "\n\nSelect a rectangle with the mouse and then press ENTER to ZOOM"
		<< "\nUse right click to delete the zoom rectangle"
		<< "\n\nESC: to cancel the graph"
		<< "\nkey M: to return to this Menu"
		<< "\n+,- : change the color palette of the fractal to cancel press ENTER";
		
	textcolor(LIGHTGRAY);
	cout << "\n\n(1) 320x200\n"
		<< "(2) 640x400\n"
		<< "(3) 640x480\n"
		<< "(4) 800x600\n"
		<< "(5) 1024x768\n"
		<< "(6) Change plotting parameters\n"
		<< "(7) About the Author\n"
		<< "(8) Exit\n"
		<< "\nChoose your resolution: ";

	cin >> option;



	if (option > 7 || option < 1) {
		option = 0;
		mode = 0;
		return; // Salir
	}

	// mostrar creditos del autor
	if (option == 6){

		clrscr();
		textcolor(YELLOW);
		cout << "Change plotting parameters: " << endl;
		
		textcolor(WHITE);
		cout << endl << "Divergence : [current value = " << DIVERGE << "]. Enter new value: ";
		cin >> DIVERGE;
		
		cout << endl <<"Maximum iteration [current value = " << ITERMAX << "] Enter new value: ";
		cin >> ITERMAX;

		textcolor(LIGHTGRAY);
		cout << endl << "Example: Coordinates for Lightning-Mandelbrot: (X: Real part, Y: Imaginary part)";
		cout << endl << "Xmin:-1.19172737578084, Xmax:-1.18215986353386, Ymin: 0.307841264022174, Ymax= 0.298345102426701" <<endl;		

		textcolor(WHITE);
		cout << endl << "Xmin [current value = " << PlanoComplejo.xmin << "] Enter new value: ";
		cin >> PlanoComplejo.xmin;

		cout << endl << "Xmax [current value = " << PlanoComplejo.xmax << "] Enter new value: ";
		cin >> PlanoComplejo.xmax;

		cout << endl << "Ymin [current value = " << PlanoComplejo.ymin << "] Enter new value: ";
		cin >> PlanoComplejo.ymin;

		cout << endl << "Ymax [current value = " << PlanoComplejo.ymax << "] Enter new value: ";
		cin >> PlanoComplejo.ymax;

		//PlanoComplejo.ymax = PlanoComplejo.ymin + (PlanoComplejo.xmax - PlanoComplejo.xmin) * 1.3;


	}else if (option == 7) {
		ModoGrafico(5);

		readimagefile("logouni.bmp", 10, 150, 10+130, 150+167);
		readimagefile("fxlogo.bmp", 0, 0, 204, 135);		

		setcolor(LIGHTRED);
		outtextxy(220, 70, "FractalX for WinBGI");
		outtextxy(220, 90, "MANDELBROT'S BEETLE FRACTAL PLOTTER");
		setcolor(LIGHTGREEN);
		outtextxy(160, 150, "Developed by: Jose Luis De la Cruz Lazaro");
		setcolor(LIGHTMAGENTA);
		outtextxy(160, 170, "Universidad Nacional de Ingenieria - Lima Peru - Since 1999");
		setcolor(YELLOW);
		outtextxy(160, 190, "At the moment I only have implemented");
		outtextxy(160, 210, "Mandelbrot's beetle");
		setcolor(WHITE);
		outtextxy(160, 300, "Press any key to Exit");
		getch();

	} else {

		//cleardevice();
		clrscr();
		cout << endl << endl;
		cout << " (1) Blind plot" << endl << endl;
		cout << " (2) TesseralX Plot" << endl << endl;
		cout << " Enter the type of plotting: ";
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

		do {
			Menu(option, mode, PlanoComplejo, DIVERGE, ITERMAX);
		} while (option == 6 || option == 7);

		if (option == 0)
			break;// Salir

		ModoGrafico(option);

		MAXX = getmaxx()+1;
		MAXY = getmaxy()+1;

		cuadricula rect = { 0,0,MAXX-1,MAXY-1 };

		CScreenBitmap scrBitmap(MAXX, MAXY, true);
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

			cout << endl << endl;
			cout << "xmin,xmax : " << PlanoComplejo.xmin << "," << PlanoComplejo.xmax << endl;
			cout << "ymin,ymax : " << PlanoComplejo.ymin << "," << PlanoComplejo.ymax << endl;
			cout << "Elapsed time: " << double((fin - inicio)) / CLK_TCK << " seconds" << endl;
			cout << "Iterations: " << iter;

			tecla = zoom(PlanoComplejo);

			switch (tecla) {
			case 'M':
				break;
			case '+':
			case '-':
				Change_Fractal_Palette(tecla, 3, 2, 1, scrBitmap);
				break;
			}
		} while (tecla != 27 && tecla!='M');

	} while (1);

	ModoGrafico(0);

	return 1;
}