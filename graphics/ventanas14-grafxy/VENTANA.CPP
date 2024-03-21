//VENTANAS version 1.0
#include <graphics.h>
#include <conio.h>
#include <iostream.h>
#include <string.h>
#include "mouse.h"

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
  void mostrar_titulo();

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
 mocultar();
 ventana(posx,posy,posx+ancho,posy+alto,modo);

 switch( modo )
 {
   case CON_FOCO:
   setcolor(15);
   break;
   case SIN_FOCO:
   setcolor(0);
   break;
   case PRESIONADO:
   setcolor(8);
 }
 mostrar_titulo();
 mver();

}
estado_anterior=estado;

}

int CBoton::mousemove(int x, int y)
{
 if( ( posx<x && x<(posx+ancho) ) && ( posy<y && y<(posy+alto) ) ) return 1;
 else return 0;
}


int CBoton::mostrar(Evento &raton)
{

  if( mousemove(raton.x,raton.y) )
   mostrar(CON_FOCO);
  else
   mostrar(SIN_FOCO);

  if( raton.boton==1 && mousemove(raton.x,raton.y) )
   {
    mostrar(PRESIONADO);
    while( mclick()==1);
    if( mousemove(mxpos(1),mypos(1)) ) return 1;
   }

   return 0;
}

void CBoton::mostrar_titulo()
{
 int longitud=strlen( titulo );

outtextxy(posx+ancho/2-textwidth("W")/2*longitud,posy+alto/2-3,titulo);
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

//    cout<<mclick();getch();

  if( mclick() )
  {
   p.boton = mclick();

   delay(200); //retrasa 200 milisegundos para que se actualice el registro de no tener ningun boton presionado
  }

 return p;
}


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


