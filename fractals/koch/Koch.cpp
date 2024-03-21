/***********************************************************************
 ::: LA CURVA DE KOCH :::
  >> Versión 1.0 28-XII-2001

 Diagramado de la curva de Koch:

 "Partiendo de un segmento el cual es dividido en tres partes iguales.
 La parte central se sustituye por dos segmentos del mismo tamaño que
 el eliminado. Sucesivamente se repite el mismo proceso por cada
 segmento formado".

 :::Programado por:::
 José Luis De La Cruz Lázaro
 YACSHA - Software & Desing 2002
  >> yacsha@elmundodelcaos.tk    
  >> www.elmundodelcaos.tk -> EL MUNDO DEL CAOS - Unlimited Programming
  >> www.foros3d.tk  -> Foros de discusión  Flash/ActionScript - C/C++

***********************************************************************/

#include "graphics.h"
#include "conio.h"
#include "math.h"
#include "dos.h"

int n=0;

void koch( double x0, double y0, double x1, double y1 ){

 line( x0, 480-y0, x1, 480-y1 );
 delay(10);
 n++;

 double x2,y2,x3,y3,x4,y4,dx,dy;

 dx = (x1-x0)/3;
 dy = (y1-y0)/3;

 x2 = x0 + dx;
 y2 = y0 + dy;
 x3 = x2 + dx;
 y3 = y2 + dy;
 x4 = (x0+x1)/2 - 0.866025*dy;
 y4 = (y0+y1)/2 + 0.866025*dx;

 if( fabs(x0-x2)>1 )
  koch( x0, y0, x2, y2 );
 if( fabs(x2-x4)>1 )
  koch( x2, y2, x4, y4 );
 if( fabs(x4-x3)>1 )
  koch( x4, y4, x3, y3 );
 if( fabs(x3-x1)>1 )
  koch( x3, y3, x1, y1 );
}


void main(){

 int gd=DETECT, gm;
 initgraph( &gd, &gm, "");
 koch( 10, 100, 600, 100 );
 getch();
 closegraph();

}
