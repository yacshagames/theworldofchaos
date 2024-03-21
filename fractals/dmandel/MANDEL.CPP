//DIAGRAMADOR DEL CONJUNTO DE MANDELBROT
//POR JOSE LUIS DE LA CRUZ LAZARO 01/11/1999
//ramondc@hotmail.com
//Pagina web: www.geocities.com/SiliconValley/Screen/2767/jldl.htm");

#include"graphics.h"
#include"conio.h"
#include"complex.h"

int huge Detect ()
{
	return ( 2 );
}


void main()
{

double
  //////////////////////////
  //COORDENADAS DEL PLANO COMPLEJO
  REALMIN=-2,
  REALMAX=1,
  IMAGMIN=-1.2,
  IMAGMAX=1.2,
  //////////////////////////
  DIVERGE=4,   //valor de divergencia
  ITERMAX=155; //iteracion maxima

int  i,j,ITERACION;

complex Z,C;

int gd=DETECT,gm;

installuserdriver ( "svga256", Detect );
   initgraph (&gd, &gm, "");
   setgraphmode ( 2 );

cleardevice();

//PROCESO DE DIAGRAMADO
    for(j=0;j<480;j++)
      for(i=0;i<640;i++)
	{

	C=complex((REALMAX-REALMIN)/640.*i+REALMIN,
		   IMAGMAX-(IMAGMAX-IMAGMIN)/480.*j);
	ITERACION=0;

	Z=0;
	 do{

	   Z=Z*Z+C; //cambiar aqui la ecuacion

	  ITERACION++;
	  if( norm(Z) > DIVERGE)break;
	  }while( ITERACION<ITERMAX );

	if(ITERACION!=ITERMAX)putpixel(i,j,ITERACION+50);

	}


getch();
closegraph();
textcolor(GREEN);
cprintf("<< Mandel 1.0 >>");
cprintf("programado por Jos‚ Luis De la Cruz L zaro");

}