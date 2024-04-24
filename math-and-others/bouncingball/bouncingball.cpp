/***********************************************************************
 ::: PELOTAS REBOTANDO :::
  >> Versión 1.0 28-XI-2000
 Un ejemplo simple de POO (Programación Orientada a objetos), en el
 cual unas pelotas rebotan en los límites de nuestra pantalla en
 modo texto.

 :::Programado por:::
 José Luis De La Cruz Lázaro
 YACSHA - Software & Desing 2002
  >> yacsha@elmundodelcaos.tk    
  >> www.elmundodelcaos.tk -> EL MUNDO DEL CAOS - Unlimited Programming
  >> www.foros3d.tk  -> Foros de discusión  Flash/ActionScript - C/C++

***********************************************************************/

#include <iostream.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>

class Pelota
{
 public:

 int X,Y;
 int dx,dy;

 Pelota();
 Pelota(int x, int y);

 void Mover();

};

Pelota::Pelota()
{
 X=40;
 Y=12;
 dx=1;
 dy=1;
}

Pelota::Pelota( int x, int y)
{
 X=x;
 Y=y;
 dx=1;
 dy=1;
}

void Pelota::Mover()
{
 if( X==80 ) dx=-1;
 if( X==1 ) dx=1;

 if( Y==25 ) dy=-1;
 if( Y==1 ) dy=1;

 gotoxy(X,Y);
 cout<<' ';

 X+=dx;
 Y+=dy;

 gotoxy(X,Y);
 cout<<'O';

}

void main()
{
 Pelota bola[8];
 int i;
 clrscr();

 randomize();

 for( i=0;i<8;i++)
 {
  bola[i].X = 1+random(80);
  bola[i].Y = 1+random(25);
 }

 while( !kbhit() )
 {
  delay( 100 );
  //clrscr();
  for( i=0;i<8;i++)
   bola[i].Mover();
 }

}
