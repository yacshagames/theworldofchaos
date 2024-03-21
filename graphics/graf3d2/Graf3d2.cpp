/***********************************************************************
 ::: GRAFICADOR DE FUNCIONES 3D :::

 Rota una superficie 3D z=f(x,y) aleatoriamente alrededor de cada uno
 de los tres ejes (X,Y,Z), modelando esta función como una estructura
 alámbrica (como una malla o cuadrícula..)

  >> Versión 1.1 20-VII-2000
 Optimización de los algoritmos de dibujo de la versión 1.0 .
 Algunas nuevas superficies matemáticas 3D.

  >> Versión 1.0 15-V-2000
  Primera Versión.

 :::Programado por:::
 José Luis De La Cruz Lázaro
 YACSHA - Software & Desing 2002
  >> yacsha@elmundodelcaos.tk    
  >> www.elmundodelcaos.tk -> EL MUNDO DEL CAOS - Unlimited Programming
  >> www.foros3d.tk  -> Foros de discusión  Flash/ActionScript - C/C++

***********************************************************************/

#include "iostream.h"
#include "graphics.h"
#include "conio.h"
#include "math.h"
#include "dos.h"//delay()
#include "stdlib.h"//srand(), random()
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
//del rayo en el CRT( Tubo de rayos cat¢dicos del monitor).
//Es conveniente ejecutarlo antes de dibujar en una animaci¢n
//para asegurar que los cambios se hagan durante el retrace del rayo
void WaitRetrace()
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
}

//se obtiene los valores de los angulos
double tsen=0.099833, //sen(0.1)
       tcos=0.995004; //cos(0.1)

void main()
{

 //coordenadas del origen de coordenadas ( en pixels )
 //en el plano 2D de la pantalla
 ox=250; //coordenada x
 oy=200; //coordenada y

  double p=20; //escala
  //se considera que 1 unidad = p pixels

 //coordenadas de los vectores unitarios i,j,k
 //en el plano 2D de la pantalla

 ix=-0.9659258*p; //ix=-cos(15)
 iy=0.2588190*p;  //iy=sin(15)
 jx=0.8660254*p;  //jx=cos(30)
 jy=0.5*p;       //jy=sin(30)
 //kx=0;       //no es nesesario declararlo
 ky=-1*p;		  //ky=-1

 double x,y,z;

 int gd=DETECT,gm;
 initgraph(&gd,&gm,"");

// DibujarEjes();

 const Xn=25,Yn=25;

 int Malla[Xn][Yn][2];
 double Superficie[Xn][Yn][3];
 int i,j;

 //x pertenece al intervalo [a,b]
 //y pertenece al intervalo [a,b]
 double a=-10,b=10;

 for( i=0;i<Xn;i++ )
 {
  x=a+((b-a)/Xn)*i;
  for( j=0;j<Yn;j++ )
  {
   y=a+((b-a)/Yn)*j;

   z=cos(sqrt(x*x+y*y));
  // z=-sin(3*(x*x+y*y));
  // z=1-x*x/25-y*y/9;
//  z=sqrt(1-x*x+y*y);
  //if(z>0)z=4*sqrt(z);else z=0;//-sqrt(z);
 // z=cos(x*x+y*y)-3*cos(x*y)+2*sin(x)+sin(y);

   Superficie[i][j][0]=x;
   Superficie[i][j][1]=y;
   Superficie[i][j][2]=z;
  }
 }

int k,ejerot=0;

 setcolor(LIGHTCYAN);

 time_t t;
 srand((unsigned) time(&t));

for( k=0;k<300;k++)
{
 if( !(k%30) ) ejerot = random(3);

  for( i=0;i<Xn;i++ )
 {

  for( j=0;j<Yn;j++ )
  {

   x=Superficie[i][j][0];
   y=Superficie[i][j][1];
   z=Superficie[i][j][2];

   switch(ejerot)
   {
   case 0:
    Superficie[i][j][1]=y*tcos-z*tsen;
    Superficie[i][j][2]=y*tsen+z*tcos;
    break;
   case 1:
    Superficie[i][j][0]=x*tcos+z*tsen;
    Superficie[i][j][2]=-x*tsen+z*tcos;
    break;
   case 2:
    Superficie[i][j][0]=x*tcos-y*tsen;
    Superficie[i][j][1]=x*tsen+y*tcos;
   }

   Malla[i][j][0]=(int)(ox+Superficie[i][j][0]*ix+Superficie[i][j][1]*jx);
   Malla[i][j][1]=(int)(oy+Superficie[i][j][0]*iy+Superficie[i][j][1]*jy+Superficie[i][j][2]*ky);
  }
 }


 int n,m;
/*
int p=0;
p++;
p%=2;
setvisualpage(p);
setactivepage(!p);*/
cleardevice();

// cleardevice();
//  WaitRetrace();


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
 delay(50);
}
 getch();
 closegraph();


}
