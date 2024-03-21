/*
FractalX para DOS versi¢n 1.2
GRAFICADOR DE FRACTALES

Programado por: Jos‚ Luis De la Cruz Lazaro
Universidad Nacional de Ingenier¡a - Lima Per£

-Version 1.2 08/10/1999
 *Grafica el conjunto de Mandelbrot, utilizando solo el controlador bgi
  SVGA256.BGI, posee 5 modos de resolucion grafica y 256 colores
 *Se utilizan las cabeceras pcxbgi.h y mousebgi.h para cargar archivos
  graficos y el puntero del mouse respectivamente utilizando solo la bgi.
 *Se implementa el modo de graficacion tipo persiana, a diferencia
  del modo anterior que barria la pantalla de arriba a abajo.
 *Se implementa un menu en modo texto para cambiar la resolucion.
 *Con las teclas + y - se rotan los colores de la paleta en sentido
  horario y antihorario respectivamente.
 *se mejora la rutina para hacer zoom, ahora solo se hace un rectangulo
  proporcional a la pantalla para que la escala del fractal no se cambie
 *se a¤ade una pantalla de creditos.

-Version 1.1 02/05/1999
 *grafica solo el conjunto de Mandelbrot, utilizando la interrupcion 10h
  subfuncion 13h (320x200 de resolucion y 256 colores) incluye
  subrutinas graficas en lenguaje ensamblador, incluidas en la
  cabecera Color256.h
 *Se rota los colores de la paleta del fractal en sentido horario
 *Se implementa una rutina para el zoom, utilizando el mouse.

-version 1.0 17/09/1998
 Grafica los conjuntos de Julia, ulizando el modo bgi VGA 16 colores

*/

#include <iostream.h>
#include <graphics.h>
#include <math.h>
#include <conio.h>
#include <complex.h>
#include <time.h>
#include <ctype.h>

#include "mousebgi.h"

void Paleta(unsigned char r, unsigned char g, unsigned char b)
{
	unsigned char cont1,Paleta[256][3];
	int cont;

	for (cont=0;cont<256;cont++)
		{
		      Paleta[cont][0]=r*(cont+1);
		      Paleta[cont][1]=g*(cont+1);
		      Paleta[cont][2]=b*(cont+1);
		}


	cont=0;
	cont1=0;

	/* El c¢digo que sigue a continuaci¢n pasa el contenido del array "Paleta"
	a la paleta de la VGA */
	for (cont=0;cont<256;cont++)
	{
		outportb (0x03c8,cont);
		for (cont1=0;cont1<3;cont1++)
			outportb (0x03c9,Paleta[cont][cont1]);
			//cout<<Paleta
	}

}


void linea_inversa(int x1, int y1, int x2, int y2)
{
 float m;
 int x,y;

 //si x1>x2 se intercambia valores
 if(x1>x2)
 {
  x=x1;
  x1=x2;
  x2=x;
 }
 //si y1>y2 se intercambia valores
 if(y1>y2)
 {
  y=y1;
  y1=y2;
  y2=y;
 }

 //se nesecita x1>y2 y y1>y2
 if(x1!=x2)
 {
  m=(y2-y1)/(float)(x2-x1);

  for(x=x1;x<=x2;x++)
  {
   y=m*x+y1-m*x1;
   putpixel(x,y,getpixel(x,y)^200);
  }
 }
 else
 for(y=y1;y<=y2;y++)
   putpixel(x1,y,getpixel(x1,y)^200);


}

void rectangulo_inverso(int x1, int y1, int x2, int y2)
{
 linea_inversa(x1,y1,x1,y2);
 linea_inversa(x1,y2,x2,y2);
 linea_inversa(x2,y2,x2,y1);
 linea_inversa(x2,y1,x1,y1);
}

struct RegionXY
{
 double xmin;
 double xmax;
 double ymin;
 double ymax;
};

int zoom(RegionXY &PC)
{
 mouseshow();

 int x = 0, y = 0, c;
 int ButonDown =1,Lx,Ly,x0,y0;

 while(1)
 {

  if( kbhit() )
  {
   c = toupper(getch());

   switch(c)
   {
    case 13:

    double ex = (PC.xmax - PC.xmin)/getmaxx();//escalax
    double ey = (PC.ymax - PC.ymin)/getmaxy();//escalay

    PC.xmin = PC.xmin + (x0-Lx) * ex;
    PC.ymax = PC.ymax - (y0-Ly) * ey;
    PC.xmax = PC.xmin + 2*Lx * ex;
    PC.ymin = PC.ymax - 2*Ly * ey;
    return c;
    case 27:
    case 'M':
    case'+':
    case'-':
    return c;
   }

  }
		 switch( mouseevent(&x,&y) )
		 {

		 case LBUTTON_STILL_DOWN:

		  if( ButonDown ){

		  mousestatus(&x0,&y0);
		  ButonDown=0;
		  }
		  else rectangulo_inverso(x0-Lx, y0-Ly, x0+Lx, y0+Ly);

		  Lx = abs(x-x0);
		  Ly = getmaxy()*(double)Lx/getmaxx();

		  rectangulo_inverso(x0-Lx, y0-Ly, x0+Lx, y0+Ly);
		  break;

		 case RBUTTON_DOWN:
		  rectangulo_inverso(x0-Lx, y0-Ly, x0+Lx, y0+Ly);
		  ButonDown = 1;
		  break;
		 }

 }


}


int Cambiar_Paleta_Fractal( char tecla, unsigned char r, unsigned char g, unsigned char b )
{
 unsigned char esc=0,i=1;

  if( tecla=='+' || tecla =='-')
  {
   mousehide();
   while(1)
   {

    switch(tecla)
    {
    case '+':
    i++;
    break;
    case'-':
    i--;
    }
    if(i)Paleta(r+i,g+i,b+i);
    delay(400);
    if(kbhit())esc=getch();
    if(esc==13)return 1;
    if( esc=='+' || esc =='-') tecla=esc;

   }
  }
 return 0;
}



int huge Detect ()
{
  return ( 0 );
}

void ModoGrafico( int modo )
{
 switch(modo)
 {
 case 0:
  closegraph();
 break;
 case 1:
  int gd=DETECT,gm;
  installuserdriver ( "svga256", Detect );
  initgraph (&gd, &gm, "");
 break;
 }
}


void Mandelbrot(RegionXY PC, double DIVERGE=4, double ITERMAX=155)
{

int  i,j,INDICE,des=10,k,q;

complex Z,C;

int maxy=getmaxy(), maxx=getmaxx();

//clock_t inicio,fin;
//inicio=clock();

//Modo de graficacion: TIPO PERSIANA
for(k=0;k<des;k++)

 for(j=k;j<maxy;j+=des)
 {
  if(kbhit())return /*getch()*/;
  for(i=0;i<maxx;i++)
  {

   C=complex( PC.xmin+((PC.xmax-PC.xmin)*i)/maxx,
	    PC.ymax-((PC.ymax-PC.ymin)*j)/maxy);
   INDICE=0;
   Z=0;

   do
   {
     Z=Z*Z+C;
     INDICE++;
     if( norm(Z) > DIVERGE)break;
   }
   while( INDICE<ITERMAX );

   if(INDICE!=ITERMAX) putpixel(i,j,INDICE);

  }
 }

//fin = clock();

//return (fin-inicio)/CLK_TCK;
}

int mandelpunto( complex &C, double DIVERGE=4, int ITERMAX=155 )
{
 int  INDICE=0;
 complex  Z=0;

   do
   {
     Z=Z*Z+C;
     INDICE++;
     if( norm(Z) > DIVERGE)break;
   }
   while( INDICE<ITERMAX );

   if(INDICE!=ITERMAX) return INDICE;
   else return 200;
}

long iter=0;
int MAXX,MAXY;

void Mandelbrot1(RegionXY PC, complex esq[4])
{

  int i,j,k, I, J, maxx, maxy;

   I=real(esq[0]);
   J=imag(esq[0]);
   maxx=real(esq[1])-I-1;
   maxy=imag(esq[3])-J-1;

   int ITERACION[4];

   int ii[4]={ I, I+maxx, I+maxx, I};
   int jj[4]={ J, J, J+maxy, J+maxy};

 for(k=0;k<4;k++)
 {
 //  if(getpixel(ii[k],jj[k])!=0)continue;
   complex C=complex( PC.xmin+((PC.xmax-PC.xmin)*ii[k])/MAXX,
		    PC.ymax-((PC.ymax-PC.ymin)*jj[k])/MAXY);
   iter++;
   putpixel(ii[k],jj[k], ITERACION[k]=mandelpunto(C));
 }


  if( ITERACION[0]==ITERACION[1] && ITERACION[0]==ITERACION[2] && ITERACION[0]==ITERACION[3] )
  {
   setfillstyle(1,ITERACION[0]);
   bar(I,J,I+maxx,J+maxy);
   return;
   }
  else
  {

  if( maxx<2 /*|| maxy <2*/ )return;

  complex ESQ[9]=
  { esq[0], (esq[0]+esq[1])/2, esq[1], (esq[0]+esq[3])/2, (esq[1]+esq[3])/2,
   (esq[1]+esq[2])/2, esq[3], (esq[2]+esq[3])/2, esq[2] };

 complex plano4[4][4] =
 { ESQ[0],ESQ[1],ESQ[4],ESQ[3],
   ESQ[1],ESQ[2],ESQ[5],ESQ[4],
   ESQ[4],ESQ[5],ESQ[8],ESQ[7],
   ESQ[3],ESQ[4],ESQ[7],ESQ[6] };

   for(int i=0; i<4; i++)
   Mandelbrot1( PC, plano4[i] );
 }

}

void Mandelbrot2(RegionXY PC, complex esq[4])
{

  int i,j,k, I, J, maxx, maxy;

   I=real(esq[3]);
   J=imag(esq[0]);
   maxx=real(esq[1])-I;
   maxy=imag(esq[2])-J;

   int ITERACION[4];

   int ii[4]={ I+maxx/2, I+maxx, I+maxx/2, I};
   int jj[4]={ J, J+maxy/2, J+maxy, J+maxy/2};

 for(k=0;k<4;k++)
 {
   //if(getpixel(ii[k],jj[k])!=0)continue;
   complex C=complex( PC.xmin+((PC.xmax-PC.xmin)*ii[k])/getmaxx(),
		    PC.ymax-((PC.ymax-PC.ymin)*jj[k])/getmaxy());

   putpixel(ii[k],jj[k], ITERACION[k]=mandelpunto(C));
 }


  if( ITERACION[0]==ITERACION[1] && ITERACION[0]==ITERACION[2] && ITERACION[0]==ITERACION[3] )
  {
   setfillstyle(1,ITERACION[0]);
   bar(I,J,I+maxx,J+maxy);
   return;
   }
  else
  {
if( maxx<4/*|| maxy <2*/ )return;

  int Rx=maxx/4,Ry=maxy/4;
  complex ESQ[12]=
  {
   complex(I+Rx,J), complex(I+3*Rx,J),
   complex(I,J+Ry),complex(I+2*Rx,J+Ry),complex(I+maxx,J+Ry),
   complex(I+Rx,J+2*Ry),complex(I+3*Rx,J+2*Ry),
   complex(I,J+3*Ry),complex(I+2*Rx,J+3*Ry),complex(I+maxx,J+3*Ry),
   complex(I+Rx,J+maxy),complex(I+3*Rx,J+maxy)};

 complex plano4[4][4] =
 { ESQ[0],ESQ[3],ESQ[5],ESQ[2],
   ESQ[1],ESQ[4],ESQ[6],ESQ[3],
   ESQ[6],ESQ[9],ESQ[11],ESQ[8],
   ESQ[5],ESQ[8],ESQ[10],ESQ[7] };

   for(int i=0; i<4; i++)
   Mandelbrot2( PC, plano4[i] );
 }

}

struct cuadricula
{
int xmin;
int ymin;
int Ladox;
int Ladoy;
};

void mandelpunto1( int &i, int &j, RegionXY &PC, double DIVERGE=4, int ITERMAX=155 )
{
 int  INDICE=0;
 complex  Z=0;

    complex C=complex( PC.xmin+((PC.xmax-PC.xmin)*i)/MAXX,
		    PC.ymax-((PC.ymax-PC.ymin)*j)/MAXY);
   do
   {
     Z=Z*Z+C;
     INDICE++;
     if( norm(Z) > DIVERGE)break;
   }
   while( INDICE<ITERMAX );

   if(INDICE!=ITERMAX) putpixel(i,j,INDICE);
//   else putpixel(i,j,0);
}

int analizar_region(cuadricula &rect ,int &xmax, int &ymax)
{
  int i,j,desx,desy;

//  if(rect.Ladox>8)
  //{
   desx=rect.Ladox/4;
   desy=rect.Ladoy/4;
//  }
//  else desx=desy=1;
   int color=getpixel(rect.xmin,rect.ymin);

for(i=0;i<3;i++)
  {
   if( color!=getpixel(xmax-i*desx,rect.ymin) ) return 0;
   if( color!=getpixel(rect.xmin+i*desx,ymax) ) return 0;
   if( color!=getpixel(rect.xmin,rect.ymin+i*desy) ) return 0;
   if( color!=getpixel(xmax,ymax-i*desy) ) return 0;
  }

  return 1;
}



void Mandelbrot3(RegionXY &PC, cuadricula rect)
{



// getch();gotoxy(20,20);cout<<rect.Ladox;
  int i,j, xmax=rect.xmin+rect.Ladox, ymax=rect.ymin+rect.Ladoy,
       xmed= rect.xmin+rect.Ladox/2,ymed= rect.ymin+rect.Ladoy/2;
 if(rect.Ladox==MAXX)
 {
  for(i=rect.xmin; i<rect.Ladox; i++)
  {
  mandelpunto1( i, rect.ymin, PC);
  mandelpunto1( i, ymax, PC);
  iter+=2;
  }

  for(j=rect.ymin; j<rect.Ladoy; j++)
  {
  mandelpunto1( rect.xmin, j, PC);
  mandelpunto1( xmax, j, PC);
  iter+=2;
  }

 }



/* int ITERACION[4]={ getpixel( rect.xmin, rect.ymin), getpixel(xmax,rect.ymin),
		    getpixel( xmax, ymax), getpixel(rect.xmin, ymax) };


  if( ITERACION[0]==ITERACION[1] )
  if( ITERACION[0]==ITERACION[2] )
  if( ITERACION[0]==ITERACION[3] )
  {*/

  if( analizar_region(rect,xmax,ymax) )
  {
   setfillstyle(1,150/*ITERACION[0]*/);
   bar(rect.xmin+1,rect.ymin+1,xmax-1,ymax-1);
   return;
  }


 if(rect.Ladox<8)
 {

 for(j=rect.ymin+1;j<ymax;j++)
  for(i=rect.xmin+1;i<xmax;i++)
  {
   mandelpunto1( i, j, PC);
   iter++;
  }

  return;
 }

  for(j=rect.ymin+1; j<ymax; j++)
  {
   mandelpunto1( xmed, j, PC);
   iter++;
  }

  for(i=rect.xmin+1; i<xmed; i++)
  {
   mandelpunto1( i, ymed, PC);
   iter++;
  }

  for(i=xmed+1; i<xmax; i++)
  {
   mandelpunto1( i, ymed, PC);
   iter++;
  }

 int Ladox=rect.Ladox/2, Ladoy=rect.Ladoy/2;
 cuadricula rect1[4]=
 {
  rect.xmin, rect.ymin, Ladox, Ladoy,
  xmed, rect.ymin, rect.Ladox-Ladox, Ladoy,
  xmed, ymed, rect.Ladox-Ladox, rect.Ladoy-Ladoy,
  rect.xmin, ymed, Ladox, rect.Ladoy-Ladoy
 };

 for(i=0;i<4; i++)
  Mandelbrot3(PC, rect1[i]);

}




int Menu()
{
 int resolucion;

 do
 {
  ModoGrafico(0);
  clrscr();

  cout<<"FractalX para DOS versi¢n 1.2\n"
     <<"GRAFICADOR DE FRACTALES\n"
     <<"\nTeclas que se usar n:"
     <<"\n\nESC: para cancelar la graficaci¢n"
     <<"\ntecla M: para volver a este Men£"
     <<"\n+,- : cambia la paleta de colores del fractal para cancelar pulse ENTER"
     <<"\n\nSeleccione un rectangulo con el mouse y luego pulse ENTER para Hacer ZOOM"
     <<"\n\n(1) 320x200\n"
     <<"(2) 640x400\n"
     <<"(3) 640x480\n"
     <<"(4) 800x600\n"
     <<"(5) 1024x768\n"
     <<"(6) Acerca del Autor\n"
     <<"(7) Salir\n"
     <<"\nElija su resoluci¢n: ";

  cin>>resolucion;

  //mostrar creditos del autor
  if( resolucion > 6 || resolucion<1) return 0; ///salir
   if(resolucion==6)
   {
    ModoGrafico(1);
    setgraphmode(1);
    PCX logos;
    logos.Dibujar(10,150,16,"logouni.pcx");
    logos.Dibujar(0,0,32,"fxlogo.pcx");
    setrgbpalette(0,0,0,0);

    setcolor(LIGHTRED);
    outtextxy(220,70,"FractalX para DOS versi¢n 1.2");
    outtextxy(220,80,"GRAFICADOR DE FRACTALES");
    setcolor(LIGHTGREEN);
    outtextxy(160,150,"Programado por: Jos‚ Luis De la Cruz Lazaro");
    setcolor(LIGHTMAGENTA);
    outtextxy(160,170,"Universidad Nacional de Ingenier¡a - Lima Per£ - 1999");
    setcolor(YELLOW);
    outtextxy(160,190,"Por el momento solo tengo implementado");
    outtextxy(160,200,"el escarabajo de Mandelbrot");
    setcolor(WHITE);
    outtextxy(160,220,"Pulse cualquier tecla para Salir");
    getch();
   }
   else break;

 }while(1);


 ModoGrafico(1);
 setgraphmode(resolucion-1);
 mousesetup(graphics);
 Paleta(10,5,1);
 return 1;
}





void main()
{

 Menu();

 RegionXY PlanoComplejo={-3,1,-1.5,2};


//PROCESO ESCARABAJO DE MANDELBROT
 char tecla=0,salir=1;
 int modo;
 clock_t inicio,fin;

 do
 {

  if( !Cambiar_Paleta_Fractal(tecla,3,2,1) )
  {
   cleardevice();
   MAXX=getmaxx();
   MAXY=getmaxy();
   iter=0;
   gotoxy(1,1);cout<<"Modo: ";
   cin>>modo;
   inicio=clock();
   switch( modo )
   {
    case 0:  Mandelbrot(PlanoComplejo); break;
    case 1:
       complex esq[4]={ complex(0,0), complex(getmaxx(),0), complex(getmaxx(),getmaxy()), complex(0,getmaxy()) };
       Mandelbrot1(PlanoComplejo,esq);
       break;
    case 2:
      // complex esq2[4]={ complex(getmaxx()/2,0), complex(getmaxx(),getmaxy()/2), complex(getmaxx()/2,getmaxy()), complex(0,getmaxy()/2) };
       //Mandelbrot2(PlanoComplejo,esq2);
	cuadricula rect={0,0,MAXX,MAXY};
	Mandelbrot3(PlanoComplejo,rect);
       break;
   }
    fin=clock();
   cout<<"\n\n"<<(fin-inicio)/CLK_TCK<<"\nIter: "<<iter;
  }
  tecla=zoom(PlanoComplejo);
  if(tecla=='M')salir=Menu();

  } while(salir && tecla!=27);

ModoGrafico(0);
}