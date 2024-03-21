/***************************************************************************
CALIJOY.H
RUTINAS PARA CALIBRAR EL JOYSTICK o JOYPAD

programado por:
JOSE LUIS DE LA CRUZ LAZARO 
ramondc@hotmail.com
Pagina Web: http://www.geocities.com/joseluisdl/jldl.htm

Version 1.0 ( 21 Dic 1999 )
 - se calibra el joystick en modo texto
 - se calibra el joystick usando graphics.h

***************************************************************************/

#ifndef __CALIJOY_H
#define __CALIJOY_H

#ifndef __GRAPHICS_H
#include <graphics.h>
#endif

#ifndef __CONIO_H
#include <conio.h>
#endif

#ifndef __IOSTREAM_H
#include <iostream.h>
#endif

#ifndef __JOYSTICK_H
#include "joystick.h"
#endif

void Calibrar_Joystick( void )
{
      // Determina el centro
      joy.cenx = joy.ceny = 0;

       clrscr();
       cout<<"\nSin mover el control presione un boton\n";
       Joy_Pausa();
       joy.cenx = joy.x;
       joy.ceny = joy.y;

       clrscr();
       cout<<"mueva el control hacia arriba y a la izquierda y presione cualquier boton";
       Joy_Pausa();
       joy.minx = joy.x;
       joy.miny = joy.y;

       clrscr();
       cout<<"mueva el control hacia abajo y a la derecha y presione cualquier boton";
       Joy_Pausa();
       joy.maxx = joy.x;
       joy.maxy = joy.y;
}

void ModoGrafico( void )
{
 int gd=DETECT,gm;
 initgraph(&gd,&gm,"");
}

void Ventana_de_Calibracion_Joystick( int x, int y)
{
 int ancho = joy.maxx - joy.minx;
 int alto  = joy.maxy - joy.miny;

 rectangle(x,y,x+ancho/2,y+alto/2);
}

void Mostrar_Posicion_Joystick( int x, int y )
{
 int posx = (joy.x - joy.minx)/2;
 int posy = (joy.y - joy.miny)/2;

 //gotoxy(60,10);cout<<posx<<" "<<posy;

 int color=12;
 if( boton[0].evento ) color+=13;
 if( boton[1].evento ) color+=14;

 setcolor(color);
 setfillstyle(1,color);
 fillellipse(x+posx,y+posy,2,2);
 setfillstyle(1,0);
 setcolor(0);
 fillellipse(x+posx,y+posy,2,2);

}

void Ventana_de_Calibracion_JoyPad( int x1, int y1, int x2, int y2  )
{
 int ancho = x2-x1+10;
 int alto  = y2-y1+10;

 x1-=5;
 x2-=5;

 rectangle(x1,y1,x1+ancho,y1+alto);

}

void Mostrar_Posicion_JoyPad( int x1, int y1, int x2, int y2  )
{
 int color=12,x,y;
 if( boton[0].evento ) color+=13;
 if( boton[1].evento ) color+=14;

 setfillstyle(1,color);
 if( joy.Padx == CEN_ ) x=(x2-x1)/2;
 else if( joy.Padx == IZQ_ ) x=x1;
 else if( joy.Padx == DER_ ) x=x2;

 if( joy.Pady == CEN_ ) y=(y2-y1)/2;
 else if( joy.Pady == ARR_ ) y=y1;
 else if( joy.Pady == ABA_ ) y=y2;

 bar(x,y,x+10,y+10);

}

#endif

/*
//EJEMPLO
main()
{
   clrscr();
   Calibrar_Joystick();

   ModoGrafico();
   cleardevice();

   Ventana_de_Calibracion_JoyPad(10,10,200,200);

   while ( !kbhit() )
    {

    LeerEventos();

    //LeerPosicionPrecisa();
    LeerPosicionPad();

    //Mostrar_Posicion_Joystick(10,10);
    Mostrar_Posicion_JoyPad(10,10,200,200);

    gotoxy(1,2);cout<<joy.Padx<<" "<<joy.Pady;

    }

   closegraph();
}
*/