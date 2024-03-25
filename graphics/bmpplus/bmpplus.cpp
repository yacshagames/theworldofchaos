/***********************************************************************
 ::: BMPPlus :::

 >> Version 2 - 25-III-2024
	- Update: Porting to VC++ 2017 using winbgi
	- Load and fast plot a BMP and JPG using WinBGI
	- Show BMP Data from header for bella.bmp
	- Show BMP and JPG in original size and fit size using readimagefile
	- Fix: The readimagefile parameters were defined well so as not to
	  distort the image when displayed in the original size
	- The drawing order of text and images is optimized, the text is
	  always displayed first and then the images.

  >> Versión 1.0 8-IX-2000
 Similar al PCXPlus pero grafica mapas de bits (BMP) utilizando
 rutinas de dibujo a bajo nivel en las resoluciones de 320x200
 y 640x480 con 256 colores.

 :::Programado por:::
 José Luis De La Cruz Lázaro
 YACSHA - Software & Desing
  >> ramondc@hotmail.com  
  >> EL MUNDO DEL CAOS - Unlimited Programming
  >> Foros de discusión  Flash/ActionScript - C/C++

***********************************************************************/
#include <iostream>
#include "graphics.h"
#include "bmpplus.h"
using namespace std;

int main()
{
	BMP bmp;
	bmp.abrir("bella.bmp", false);    // load a bmp to access its structure

	cout << "BMPPlus: Load and fast plot a BMP and JPG using WinBGI" << endl << endl;

	cout << "BMP Data from header for bella.bmp:" << endl;	
	cout << "Type (2 bytes): " << bmp.tipo << endl;
	cout << "Size (4 bytes): " << bmp.tamano << endl;
	cout << "Reserved (4 bytes): " << bmp.reservado << endl;
	cout << "Offset (4 bytes): " << bmp.desplazamiento << endl;
	cout << "Bytes in header (4 bytes): " << bmp.bytes_en_cabecera << endl;
	cout << "Width (4 bytes): " << bmp.ancho << endl;
	cout << "Height (4 bytes): " << bmp.alto << endl;
	cout << "Number of color planes (2 bytes): " << bmp.planos << endl;
	cout << "Bits per pixel (2 bytes): " << bmp.bits_por_pixel << endl;
	cout << "Compression (4 bytes): " << bmp.compresion << endl;
	cout << "Image Size (4 bytes): " << bmp.tamano_de_imagen << endl;
	cout << "Horizontal resolution (4 bytes): " << bmp.resolucion_h << endl;
	cout << "Vertical resolution (4 bytes): " << bmp.resolucion_v << endl;
	cout << "Number of actually used colors - n Index (4 bytes): " << bmp.n_indices << endl;
	cout << "Number of important colors 0=all - n_i Index (4 bytes): " << bmp.n_i_indices << endl;

	cout << endl;

	cout << "Enter 1 to continue : ";
	int opt;
	cin >> opt;
	
	// Init WinBGI window
	initwindow(1024, 768, "The world of chaos in C++ - Unlimited Programming");

	outtextxy(0,0, "BMP load test in original size");	
	outtextxy(0,20,"Press any key to continue ...");
	readimagefile("bella.bmp", 0, 40, bmp.ancho, 40+bmp.alto);
	getch();

	cleardevice(); // clear screen
	
	readimagefile("bella.bmp", 0, 0, getmaxx()+1, getmaxy() + 1);
	outtextxy(0, 0, "BMP load test in fit size");
	outtextxy(0, 20, "Press any key to continue ...");
	getch();

	cleardevice(); // clear screen

	readimagefile("bella.jpg", 0, 40, bmp.ancho, 40 + bmp.alto);
	outtextxy(0, 0, "JPG load test in original size");
	outtextxy(0, 20, "Press any key to continue ...");	
	getch();

	cleardevice(); // clear screen

	readimagefile("bella.jpg", 0, 0, getmaxx() + 1, getmaxy() + 1);
	outtextxy(0, 0, "JPG load test in fit size");
	outtextxy(0, 20, "Press any key to continue ...");	
	getch();

	closegraph();

	return 1;
}
