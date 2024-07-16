/*************************************************************************

LICENSE

	This file is released under the terms of the BSD 3-Clause License.
	Read LICENSE.txt file for more information.

*************************************************************************/

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
