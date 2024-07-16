/*********************************************************************
::: 3D FUNCTION PLOTTER ::: EXAMPLE 2 :::

Rotates a 3D surface z=f(x,y) randomly around each of the three
axes (X,Y,Z), modeling this function as a wireframe
(like a mesh or grid...)

Developed by:

	JOSE LUIS DE LA CRUZ LAZARO
	contact@theworldofchaos.com

	YACSHA - Software & Desing, since 1999, Lima-Peru
	>> The World of Chaos - EL MUNDO DEL CAOS - Unlimited Programming
	www.theworldofchaos.com

LICENSE
	This file is released under the terms of the BSD 3-Clause License.
	Read LICENSE.txt file for more information.

HISTORY...

 >> Version 2 - 25-III-2024
- Update graphics/graf3d1 - Porting to VC++ 2017 using winbgi

 >> Version 1.0 - 15-V-2000
 - First version for Borland C++ 3.1 and Turbo C 3.0

 *********************************************************************/

//#include "iostream.h"
#include "graphics.h"
#include "conio.h"
//#include "math.h"
//#include "dos.h"//delay()
//#include "stdlib.h"//srand(), random()
#include "time.h" //time()

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


//Espera el retrace horizontal, es decir el retorno horizontal
//del rayo en el CRT( Tubo de rayos catódicos del monitor).
//Es conveniente ejecutarlo antes de dibujar en una animación
//para asegurar que los cambios se hagan durante el retrace del rayo
/*void WaitRetrace()
{
  _DX = 0x03DA;

  l1: asm {
	in  al,dx;
	and al,0x08;
	jnz l1;
      }

  l2: asm {
	in  al,dx;
	and al,0x08;
	jz  l2;
      }
}*/

 //Aceleradores de calculos trigonometricos
 //esto se hace para no emplear las funciones sin() y cos() 
 //que vuelven lento el proceso de animacion y hace que la imagen
 //parpadee mucho
 //La rotacion sera de 0.1 radianes
double tsen=0.099833, //sen(0.1)
       tcos=0.995004; //cos(0.1)

void main()
{

/***********************************************************
  PROYECCION DE LOS EJES COORDENADOS XYZ SOBRE EL PLANO
  DE LA PANTALLA X'Y'

  O : origen respecto al origen de coordenadas de los ejes
  O': origen respecto a la pantalla del ordenador

     O'__________________ X'
      |
      |      eje Z
      |        |k
      |        |
      |  _ _ _ |_ _ _ _
      | 15ø ( /O\ ) 30ø
      |     /     \
      |    i       j
      Y' eje X      eje Y
************************************************************/

 //coordenadas del origen de los ejes coordenados ( en pixels )
 //en el plano 2D de la pantalla ( coordenadas de O , ver grafico )
 ox=250; //coordenada x
 oy=200; //coordenada y

  double p=80; //escala
  //se considera que 1 unidad = p pixels


 //coordenadas de los vectores unitarios i,j,k
 //proyectados en el plano 2D de la pantalla
 //( para deducir los vectores solo hay que descomponer i,j,k 
 //  sobre el plano X'Y' , ver grafico )

 //vector i ( unitario en el eje X )
 ix=-0.9659258*p; //ix=-cos(15) ...componente x
 iy=0.2588190*p;  //iy=sin(15)  ...componente y
 //vector j ( unitario en el eje Y )
 jx=0.8660254*p;  //jx=cos(30)  ...componente x
 jy=0.5*p;        //jy=sin(30)  ...componente y
 //vector k ( unitario en el eje Z )
 //kx=0;          //no es nesesario declararlo ...componente x
 ky=-1*p;	  //ky=-1       ...componente y

 double x,y,z;

 // Init WinBGI window
 initwindow(1024, 768, "The world of chaos in C++ - Unlimited Programming");

 //DibujarEjes();

 const int Xn=25,Yn=25; //ancho y alto de cuadricula ( Malla )

 int Malla[Xn][Yn][2]; //Malla 2D de proyeccion de la superficie en la pantalla
 double Superficie[Xn][Yn][3]; //Malla 3D de puntos originales
 int i,j;

 //x pertenece al intervalo [a,b]
 //y pertenece al intervalo [a,b]
 double a=-1.2, //coordenada minima
	    b=1.2;  //coordenada maxima

 //construccion de la Malla 3D a partir de una ecuacion
 //de superficie z=f(x,y)
 for( i=0;i<Xn;i++ )
 {
  x=a+((b-a)/Xn)*i;
  for( j=0;j<Yn;j++ )
  {
   y=a+((b-a)/Yn)*j;

   z=-cos(3*(x*x+y*y)); //El Sombrero de Bufon cosenoidal
   //z=-sin(3*(x*x+y*y)); //El Sombrero de Bufon senoidal
   //z=x*x-y*y; //La silla de Montar
   //z=5*sqrt(fabs(1-x*x/25-y*y/16)); //Una elipse
   //z=sqrt(1-x*x+y*y);
   //if(z>0)z=4*sqrt(z);else z=0;//-sqrt(z);
   //z=cos(x*x+y*y)-3*cos(x*y)+2*sin(x)+sin(y);

   //Obteniendo Matriz de Superficie 3D
   Superficie[i][j][0]=x;
   Superficie[i][j][1]=y;
   Superficie[i][j][2]=z;
  }
 }

int k,ejerot=0;

 setcolor(LIGHTCYAN);

 time_t t;
 srand((unsigned) time(&t));

//Muestra la superficie 3D rotando aleatoriamente alrededor de los 3 ejes
//La animacion consiste de 300 cuadros
for( k=0;k<300;k++)
{
  
  //Se cambia el eje de rotacion cada 30 cuadros	
  if( !(k%30) ) ejerot = random(3);

  //rotacion de la Malla 3D
  for( i=0;i<Xn;i++ )
 {

  for( j=0;j<Yn;j++ )
  {

   x=Superficie[i][j][0];
   y=Superficie[i][j][1];
   z=Superficie[i][j][2];

   switch(ejerot)
   {
   case 0://rotacion alrededor del eje X
    Superficie[i][j][1]=y*tcos-z*tsen;
    Superficie[i][j][2]=y*tsen+z*tcos;
    break;
   case 1://rotacion alrededor del eje Y
    Superficie[i][j][0]=x*tcos+z*tsen;
    Superficie[i][j][2]=-x*tsen+z*tcos;
    break;
   case 2://rotacion alrededor del eje Z
    Superficie[i][j][0]=x*tcos-y*tsen;
    Superficie[i][j][1]=x*tsen+y*tcos;
   }

 //Se Proyecta los puntos 3D al plano 2D de la pantalla
   Malla[i][j][0]=(int)(ox+Superficie[i][j][0]*ix+Superficie[i][j][1]*jx);
   Malla[i][j][1]=(int)(oy+Superficie[i][j][0]*iy+Superficie[i][j][1]*jy+Superficie[i][j][2]*ky);
  }
 }


 int n,m;

  cleardevice();
 //WaitRetrace(); //espera el retrazo del CRT

//Muestra la Malla 2D ( Proyeccion de la superficie sobre la pantalla)
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
 //Pone una pausa de 50 milisegundos entre cada cuadro
 delay(50);
}
 getch();
 closegraph();


}