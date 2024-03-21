/*****************************************************************************
VENTANAS.H version 1.1
SIMULA UN ENTORNO GRAFICO SIMILAR A WINDOWS 98

14/08/1999 version 1.0
 creacion de:
 * Funcion Ventana
 * Clase CBoton

10/09/1999
 * modificacion la funcion CBoton::Mostrar
   se agrego el efecto de mostrar el boton SIN_FOCO cuando se mantiene
   presionado el click y se esta fuera del area del boton, y mostrarlo
   PRESIONADO cuando se esta en su area.

*****************************************************************************/

#if !defined(__GRAPHICS_H)
#include <graphics.h>
#endif

#if !defined(__CONIO_H)
#include <conio.h>
#endif

#if !defined(__STRING_H)
#include <string.h>
#endif

#include "mouse.h"

//#include <iostream.h>

//Define los estados del boton
#define SIN_FOCO 0
#define CON_FOCO 1
#define PRESIONADO 2

struct Evento
{
 int x;
 int y;
 int boton;
 char tecla;
};


void ventana(int x, int y, int x1, int y1, int modo3D = 0,int color_fondo = 7);

///////////////////////////////////////////////////////////////////////////
//Clase Boton
class CBoton
{
 public:
 int posx,posy;
 int alto,ancho;
 int estado,estado_anterior;
 char *titulo;

 CBoton(int _posx, int _posy, int _alto, int _ancho, char *_titulo);

 int mostrar(Evento &raton);

 private:
  void mostrar( int modo);
  int mousemove(int x, int y);
  void mostrar_titulo(int x = 0, int y = 0);

};

CBoton::CBoton(int _posx, int _posy, int _alto, int _ancho, char *_titulo)
{
posx=_posx;
posy=_posy;
alto=_alto;
ancho=_ancho;
strcpy(titulo,_titulo);
}

void CBoton::mostrar( int modo )
{

estado=modo;

if(estado!=estado_anterior)
{
 mocultar();  //oculta el puntero para que este no corte el grafico del boton
 ventana(posx,posy,posx+ancho,posy+alto,modo);

 switch( modo )
 {
   case CON_FOCO:
   setcolor(15);
   mostrar_titulo();
   break;
   case SIN_FOCO:
   setcolor(0);
   mostrar_titulo();
   break;
   case PRESIONADO:
   setcolor(8);
   mostrar_titulo(2,2);
 }

 mver(); //el puntero se ve otra vez

}
estado_anterior=estado;

}

int CBoton::mousemove(int x, int y)
{
 if( ( posx<x && x<(posx+ancho) ) && ( posy<y && y<(posy+alto) ) ) return 1;
 else return 0;
}


//Muestra los estados del boton dependiendo de la posicion del cursor
int CBoton::mostrar(Evento &raton)
{

 switch( raton.boton )
 {
  case 0: //No se hizo click

  if( mousemove(raton.x,raton.y) )
   mostrar(CON_FOCO);
  else
   mostrar(SIN_FOCO);

  break;

 case 1: //se hizo un click izquierdo
  if( mousemove(raton.x,raton.y) )
   {
    mostrar(PRESIONADO);
    delay(100);
    while( mclick()==1) //mientras no se suelte el boton
     if( !mousemove(mxpos(1),mypos(1)) )
      mostrar(SIN_FOCO);
     else
      mostrar(PRESIONADO);

    if( mousemove(mxpos(1),mypos(1)) ) return 1; //se ejecuta la orden del boton
   }


 }
 return 0;//no se ejecuta la orden del boton
}

void CBoton::mostrar_titulo(int x, int y)
{
 int longitud=strlen( titulo );
 outtextxy(x+posx+ancho/2-textwidth("W")/2*longitud,y+posy+alto/2-3,titulo);
}
///////////////////////////////////////////////////////////////////////////

//Dibuja una ventana vacia tipo WINDOWS98
void ventana(int x, int y, int x1, int y1, int modo3D, int color_fondo )
{
//  modo3D=0 -> muestra una ventana sin efecto 3D
//  modo3D=1 -> muestra una ventana saliente
//  modo3D=2 -> muestra una ventana entrante


int marco1,marco2;

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

 setcolor(marco1);
 line(x,y,x1,y);
 line(x,y,x,y1);

 setcolor(marco2);
 line(x,y1,x1,y1);
 line(x1,y,x1,y1);

}


Evento Detectar_click_o_tecla(int modo)
{
 Evento p;

 p.boton=p.tecla=0;

   p.x= mxpos(modo);
   p.y= mypos(modo);


  if( kbhit() )
    p.tecla=getch();

  if( mclick() )
  {
   p.boton = mclick();

   delay(200); //retrasa 200 milisegundos para que se actualice el registro de no tener ningun boton presionado
  }

 return p;
}


//EJEMPLO

void main()
{
 int gdriver = DETECT, gmode;
 initgraph(&gdriver, &gmode, "c:\\bc31\\bgi");

 ventana(0,0,640,480,1);

 Evento raton;

 CBoton Aceptar(10,40,20,80,"Aceptar"),Salir(10,10,20,50,"Salir");

 mver();
 msituar(1,0,0);

  do
  {

  if( Salir.mostrar(raton) )break;
  Aceptar.mostrar(raton);


  raton=Detectar_click_o_tecla(1);


  }while(raton.tecla!=27);


// getch();
mocultar();
 closegraph();

}

