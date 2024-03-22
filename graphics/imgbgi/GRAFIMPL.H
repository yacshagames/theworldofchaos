/***********************************************************************
IMPLEMENTACION GRAFICA

>> Version 2 - 21 - III - 2024
	- Porting to VC++ 2017 using winbgi

***********************************************************************/

#ifndef __GRAPHICS_H
#include "graphics.h"
#endif

//se definen todos los modos de resolucion grafica
#define  _320x200 0
#define  _640x400 1
#define  _640x480 2
#define  _800x600 3
#define _1024x768 4

/*int huge detec0(void)
{
 return _320x200; //resolucion grafica alto x ancho pixeles
}

int huge detec1(void)
{
 return _640x400; //resolucion grafica alto x ancho pixeles
}

int huge detec2(void)
{
 return _640x480; //resolucion grafica alto x ancho pixeles
}

int huge detec3(void)
{
 return _800x600; //resolucion grafica alto x ancho pixeles
}

int huge detec4(void)
{
 return _1024x768; //resolucion grafica alto x ancho pixeles
}*/

void IniciarSVGA(int resolucion)
{
	std::string sTittle = "The world of chaos in C++ - Unlimited Programming";
	
	//se instala la resolucion deseada
	switch (resolucion)
	{
	case _320x200:
		//installuserdriver("Svga256",detec0);
		initwindow(320, 200, sTittle.c_str());
		break;
	case _640x400:
		//installuserdriver("Svga256",detec1);
		initwindow(640, 400, sTittle.c_str());
		break;
	case _640x480:
		//installuserdriver("Svga256",detec2);
		initwindow(640, 480, sTittle.c_str());
		break;
	case _800x600:
		//installuserdriver("Svga256",detec3);
		initwindow(800, 600, sTittle.c_str());
		break;
	case _1024x768:
		//installuserdriver("Svga256",detec4);
		initwindow(1024, 768, sTittle.c_str());
	}

	//int gdriver = VGA, gmode = VGAHI;
	//initgraph(&gdriver,&gmode,(char*)"");  //se busca el controlador bgi en la ruta de la carpeta especificada
}


///////////////////////////////////////////////////////////////////////////
//Dibuja un cuadro con efecto 3D
void cuadro(int x, int y, int x1, int y1, int modo3D, int color_fondo = LIGHTGRAY )
{

// Solo borra cuando las coordenadas son positivas
if (x < 0 || y < 0)
	return;

//  modo3D=0 -> muestra una ventana sin efecto 3D
//  modo3D=1 -> muestra una ventana saliente
//  modo3D=2 -> muestra una ventana entrante

int marco1,marco2,color_actual;

switch( modo3D )
{
 case 0:
  marco1=marco2=color_fondo;
  setfillstyle(1, color_fondo);
  bar(x, y, x1+1, y1+1);
  return;
  break;
 case 1:
  marco1=15;
  marco2=8;
  break;
 case 2:
  marco1=8;
  marco2=15;
}

 setfillstyle(1,color_fondo);
 bar3d(x,y,x1,y1,0,0);
 
 color_actual=getcolor();

 setcolor(marco1);
 line(x,y,x1,y);
 line(x,y,x,y1);

 setcolor(marco2);
 line(x,y1,x1,y1);
 line(x1,y,x1,y1);

 setcolor(color_actual);
 
}

void ventana(int izquierda, int arriba, int derecha, int abajo )
{
 cuadro(izquierda, arriba, derecha, abajo, 1);
 cuadro(izquierda, arriba, derecha, arriba+10, 1, 1);
}
