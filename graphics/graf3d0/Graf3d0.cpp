/***********************************************************************
 ::: GRAFICADOR DE FUNCIONES 3D :::
 >> Versión 1.0 15-V-2000
 Rota una superficie 3D z=f(x,y) aleatoriamente alrededor de cada uno
 de los tres ejes (X,Y,Z), modelando esta función como una estructura
 alámbrica (como una malla o cuadrícula..)

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

 double ox,oy,ix,iy,jx,jy,ky;

void DibujarEjes()
{
   moveto(ox,oy);
   lineto(ox+100*ix,oy+100*iy);
   moveto(ox,oy);
   lineto(ox+100*jx,oy+100*jy);
   moveto(ox,oy);
   lineto(ox,oy+100*ky);
}



void main()
{

 //coordenadas del origen de coordenadas
 //en el plano 2D de la pantalla
 ox=250; //coordenada x
 oy=200; //coordenada y
 //coordenadas de los vectores unitarios i,j,k
 //en el plano 2D de la pantalla
 //se considera que 1 unidad = p pixels
 double p=100;
 ix=-0.9659258*p; //ix=-cos(15)
 iy=0.2588190*p;  //iy=sin(15)
 jx=0.8660254*p;  //jx=cos(30)
 jy=0.5*p;       //jy=sin(30)
 //kx=0;       //no es nesesario declararlo
 ky=-1*p;		  //ky=-1

 double x,y,z;

 int gd=DETECT,gm;
 initgraph(&gd,&gm,"");

 DibujarEjes();

 const Xn=30,Yn=30;

 int Malla[Xn][Yn][2];
 int i,j;

 //x pertenece al intervalo [a,b]
 //y pertenece al intervalo [a,b]
 double a=-1,b=1;

 for( i=0;i<Xn;i++ )
 {
  x=a+((b-a)/Xn)*i;
  for( j=0;j<Yn;j++ )
  {
   y=a+((b-a)/Yn)*j;
   z=-sin(3*(x*x-y*y));
   Malla[i][j][0]=(int)(ox+x*ix+y*jx);
   Malla[i][j][1]=(int)(oy+x*iy+y*jy+z*ky);
  }
 }
 setcolor(14);

 int n,m;

 for( i=0;i<Xn;i++ )
  for( j=0;j<Yn;j++ )
  {

   if( Malla[i][j][0] >0 && Malla[i][j][0] < 640 &&
       Malla[i][j][1] >0 && Malla[i][j][1] < 480 )
   {
    moveto(Malla[i][j][0],Malla[i][j][1]);
    n=i+1;
    if(n<Xn)
     lineto(Malla[n][j][0],Malla[n][j][1]);

    moveto(Malla[i][j][0],Malla[i][j][1]);
    m=j+1;
    if(m<Yn)
     lineto(Malla[i][m][0],Malla[i][m][1]);

   }
 }
  getch();
  closegraph();


}
