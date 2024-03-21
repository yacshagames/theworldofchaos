/***********************************************************************
 :::PROGRAMA PARA DIAGRAMAR EL CONJUNTO DE MANDELBROT:::
  >> Versión 1.5 23-II-2002
 Ejemplo simple de diagramación de fractales.
 Optimización de la versión 1.0, ahora se puede personalizar la paleta
 de 256 colores que utilizará nuestro fractal, mediante la función
 setrgbpallete de la BGI.

 :::Programado por:::
 José Luis De La Cruz Lázaro
 YACSHA - Software & Desing 2002
  >> yacsha@elmundodelcaos.tk    
  >> www.elmundodelcaos.tk -> EL MUNDO DEL CAOS - Unlimited Programming
  >> www.foros3d.tk  -> Foros de discusión  Flash/ActionScript - C/C++

***********************************************************************/

#include"graphics.h"
#include"math.h"
#include"conio.h"
#include"complex.h"

int huge Detect ()
{
	return ( 2 );
}

void CambiarColores( int red, int green, int blue){

 for(int i=0;i<256;i++)
    setrgbpalette (i , i*red, i*green, i*blue);
}


void main()
{

double
  REALMIN=-2,  //{PROCURAR QUE REALMAX-REALMIN SEA IGUAL A                   }
  REALMAX=2,   //{COMPLEJOMAX-COMPLEJOMIN, PARA EVITAR FIGURAS DISTORSIONADAS}
  COMPLEJOMIN=-2,    //{MODIFICAR LOS VALORES PARA HACER ZOOM}
  COMPLEJOMAX=2,
  DIVERGE=100,
  ITERMAX=200;

///coordenadas del Mandelbrot-Rayos

double x1 = -1.19172737578084;
double y1 = 0.307841264022174;
double x2 = -1.18215986353386;
double y2 = 0.298345102426701;

REALMIN=x1;  //{PROCURAR QUE REALMAX-REALMIN SEA IGUAL A                   }
REALMAX=x2;   //{COMPLEJOMAX-COMPLEJOMIN, PARA EVITAR FIGURAS DISTORSIONADAS}
COMPLEJOMIN=y1;    //{MODIFICAR LOS VALORES PARA HACER ZOOM}
COMPLEJOMAX=y2;

int  i,j,INDICE;

complex Z,C;

int gd=DETECT,gm;

 //INICIALIZANDO MODO GRAFICO EN 256 COLORES
   installuserdriver ( "svga256", Detect );
   initgraph (&gd, &gm, "");
   setgraphmode ( 2 ); //CAMBIA LA RESOLUCION DE LA PANTALLA

   //muestra una precarga mientras se carga los colores
   //en la paleta
    setrgbpalette (255,255,255,255); //color blanco
    setcolor(255);
    outtextxy(280,240, "CARGANDO...");

   //Cambia la paleta de 256 colores en funcion lineal a los tonos
   //red=10 , green=5, blue=1
   CambiarColores( 10, 5, 1);

   //borra la precarga
   setcolor(0);
   outtextxy(280,240, "CARGANDO...");

 //TITULOS Y CREDITOS
setcolor(115);
outtextxy(130,5,"THE MANDELBROT-RAYOS: Z^2+C");
setcolor(10);
settextstyle(7,1,1);
outtextxy(10,5,"<< MANDELX 1.5 >>");
setcolor(114);
settextstyle(7,0,1);
outtextxy(220,450,"por YACSHA - Software & Desing");
setcolor(12);
settextstyle(10,1,1);
outtextxy(10,230,"UNI-FIEE");
rectangle(120,20,550,450);

 //PROCESO PINTAR
    for(j=21;j<449;j++)
      for(i=121;i<549;i++)
	{

	C=complex((REALMAX-REALMIN)/430.*(i-120)+REALMIN,
		   COMPLEJOMAX-(COMPLEJOMAX-COMPLEJOMIN)/430.*(j-20));
	INDICE=0;
	  Z=C;
	 do{

	  Z=Z*Z+C;
	  INDICE++;
	  if( abs(Z) > DIVERGE)break;
	  }while( INDICE<ITERMAX );

	if(INDICE!=ITERMAX)
	  putpixel(i,j,INDICE);

	}

  //Fin PINTAR

getch();
closegraph();
}
