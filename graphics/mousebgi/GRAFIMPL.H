//IMPLEMENTACION GRAFICA
#ifndef __GRAPHICS_H
#include "graphics.h"
#endif

#ifndef __MOUSEBGI_H
#include "mousebgi.h"
#endif

//se definen todos los modos de resolucion grafica
#define  _320x200 0
#define  _640x400 1
#define  _640x480 2
#define  _800x600 3
#define _1024x768 4
/*
int huge func(void)
{
 return _640x480; //resolucion grafica que se utilizara por defecto
}*/

void IniciarSVGA( int resolucion )
{
 int controlador=0,modo=0;

 /*controlador=DETECT;
 installuserdriver("Svga256",func);
 initgraph(&controlador,&modo,"");  //se busca el controlador bgi en la ruta de la carpeta especificada*/
 initwindow(1024, 768, "El mundo del caos");

 setgraphmode( resolucion );

 //mousesetup(graphics);//inicia el raton
 //mousehide(); //oculta el raton

}

///////////////////////////////////////////////////////////////////////////
//Dibuja un cuadro con efecto 3D
void cuadro(int x, int y, int x1, int y1, int modo3D, int color_fondo = LIGHTGRAY )
{
//  modo3D=0 -> muestra una ventana sin efecto 3D
//  modo3D=1 -> muestra una ventana saliente
//  modo3D=2 -> muestra una ventana entrante

int marco1,marco2,color_actual;

switch( modo3D )
{
 case 0:
  marco1=marco2=color_fondo;
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
