/***********************************************************************
 ::: 3D FUNCTION PLOTTER ::: EXAMPLE 1 :::

Rotates a 3D surface z=f(x,y) randomly around each of the three
axes (X,Y,Z), modeling this function as a wireframe
(like a mesh or grid...)

Developed by:

	JOSE LUIS DE LA CRUZ LAZARO
	contact@theworldofchaos.com

	YACSHA - Software & Desing
	>> The World of chaos - EL MUNDO DEL CAOS - Unlimited Programming
	www.theworldofchaos.com

LICENSE
	This file is released under the terms of the BSD 3-Clause License.
	Read LICENSE.txt file for more information.

HISTORY...

 >> Version 2 - 25-III-2024
- Update graphics/graf3d0 - Porting to VC++ 2017 using winbgi

 >> Versión 1.0 15-V-2000
 - First version for Borland C++ 3.1 and Turbo C 3.0

***********************************************************************/

#include "graphics.h"
//#include "conio.h"
//#include "math.h"

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

 // Init WinBGI window
 initwindow(1024, 768, "The world of chaos in C++ - Unlimited Programming");

 DibujarEjes();

 const int Xn=30,Yn=30;

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
