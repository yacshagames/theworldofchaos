/***************************************************************************
MouseBGI

Utility that allows to see the mouse cursor in bgi mode either in 16 colors
or 256 colors, also uses event programming, similar to visual programming
only in DOS, brings an example (DBZCARDS GOKU vs FREEZER) whoever puts more
cards on the screen wins everything is done with left and right mouse clicks

Spanish:
Ejemplo de como controlar las rutinas del mouse en el modo grafico de
256 colores

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
	- Update graphics/mousebgi - Porting to VC++ 2017 using winbgi
	
 >>	Version 1 - 16-XI-1999
	- First version for Borland C++ 3.1 and Turbo C 3.0

***************************************************************************/

#include "graphics.h"
//#include "conio.h"
#include "grafimpl.h"
//#include "mousebgi.h"
#include "imgbgi.h"

/*
#define wait1 1
#define wait2 2

void WaitRetrace(void)
{
 Espera el retrace horizontal, es decir el retorno horizontal
del rayo en el CRT. Es conveniente ejecutarlo antes de dibujar en una
animación para asegurar que los cambios se hagan durante el retrace delrayo

 asm{
  mov dx,3dah
  wait1:
  in al,dx
  test al,08h
  jnz wait1
  wait2:
  in al,dx
  test al,08h
  jz wait2
  }

}//WaitRetrace
  */

int DetectarTecla()
{
	if (kbhit())
	{
		int tecla = getch();
		if (tecla == 0)getch();

		return tecla;
	}

	return 0;
}
int main()
{
	IniciarSVGA(_1024x768); //se inicia la supervga (256 colores ) con una resolucion de 1024x768

	cuadro(0, 0, getmaxx(), getmaxy(), 1); //se dibuja el cuadro de fondo

	//Evento raton, raton_anterior;

	//movemouse(100,100); //se mueve el puntero a la posicion (100,100)
	//mouseshow();//se muestra el raton

	IMG freezer, goku; // se crea el objeto grafico

	freezer.leer_cabecera("freezer.pcx"); // se lee informacion del archivo pcx
	goku.leer_cabecera("goku.pcx");

	outtextxy(10, 20, "Press the left mouse button to see KAKAROTO");
	outtextxy(10, 40, "Press the right mouse button to see FREEZER");

	//raton = Detectar_click_o_tecla();
	int xMouse = -1, yMouse = -1;
	int xMouse_last, yMouse_last;
	do
	{
		//raton_anterior = raton;
		//raton = Detectar_click_o_tecla(); //se obtiene informacion sobre las coordenadas del raton

		//muestra la card de Goku
		if ( ismouseclick(WM_LBUTTONDOWN) ) {

			xMouse_last = xMouse;
			yMouse_last = yMouse;

			xMouse = mousex();
			yMouse = mousey();
			clearmouseclick(WM_LBUTTONDOWN);
			
			cuadro(xMouse_last, yMouse_last,
				xMouse_last + 160, yMouse_last + 150, 0); //borra la ventana
			ventana(xMouse, yMouse, xMouse + 160, yMouse + 150); //dibuja la ventana

			goku.Dibujar(xMouse + 10, yMouse + 20); //dibuja a GOKU sobre la ventana en la posicion indicada

			outtextxy(xMouse + 30, yMouse + 130, "GOKU");
		}		

		// muestra la card de Freezer
		if (ismouseclick(WM_RBUTTONDOWN)) {

			xMouse_last = xMouse;
			yMouse_last = yMouse;

			xMouse = mousex();
			yMouse = mousey();
			clearmouseclick(WM_RBUTTONDOWN);

			cuadro(xMouse_last, yMouse_last,
				xMouse_last + 160, yMouse_last + 150, 0); //borra la ventana
			ventana(xMouse, yMouse, xMouse + 160, yMouse + 150); //dibuja la ventana

			freezer.Dibujar(xMouse + 10, yMouse + 20); //dibuja a GOKU sobre la ventana en la posicion indicada

			outtextxy(xMouse + 30, yMouse + 130, "FREEZER");
		}	

	} while ( DetectarTecla() != 27 );

	//mousehide();
	//mousedestroy();

	closegraph();

	//textcolor( GREEN+BLINK );

	printf("DBZ CARDS -- programado por Jose Luis De la Cruz Lazaro\n\n");

	//getch();

	return 1;
}