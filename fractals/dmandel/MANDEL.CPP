/*****************************************************************************
MANDELBROT SET PLOTTER
BY JOSE LUIS DE LA CRUZ LAZARO 

>> Version 2 - 25 - III - 2024
- Update graphics/dmandel - Porting to VC++ 2017 using winbgi

>> Version 1 - 01 - XI - 1999
- First version for Borland C++ 3.1 and Turbo C 3.0
 
ramondc@hotmail.com
Pagina web: www.geocities.com/SiliconValley/Screen/2767/jldl.htm");

*****************************************************************************/

#include "graphics.h"
//#include "conio.h"
#include "complex.h"

int main()
{

double
  //////////////////////////
  //COORDENADAS DEL PLANO COMPLEJO
  REALMIN=-2,
  REALMAX=1,
  IMAGMIN=-1.2,
  IMAGMAX=1.2,
  //////////////////////////
  DIVERGE=4,   //valor de divergencia
  ITERMAX=155; //iteracion maxima

int  i,j,ITERACION;

complex Z,C;

 // Init WinBGI window
int maxx = 1024, maxy = 768;
 initwindow(maxx+10, maxy+10, "The world of chaos in C++ - Unlimited Programming");

cleardevice();

//PROCESO DE DIAGRAMADO
    for(j=0;j<maxy;j++)
      for(i=0;i<maxx;i++)
	{

	C=complex((REALMAX-REALMIN)/ maxx *i+REALMIN,
		   IMAGMAX-(IMAGMAX-IMAGMIN)/ maxy *j);
	ITERACION=0;

	Z=0;
	 do{

	   Z=Z*Z+C; //cambiar aqui la ecuacion

	  ITERACION++;
	  if( abs(Z) > DIVERGE)break;
	  }while( ITERACION<ITERMAX );

	if(ITERACION!=ITERMAX)putpixel(i,j,ITERACION+50);

	}


getch();
setcolor(GREEN);
printf("<< Mandel 2.0 >>\n");
printf("Programmed by Jose Luis De la Cruz Lazaro\n\n\n\n\n\n\n\n\n");
closegraph();
return 1;
}