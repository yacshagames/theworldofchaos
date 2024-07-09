/***********************************************************************
 ::: MOVING TRIANGLE :::

 Plots a triangle in a 3D system on the screen rotating
 around the axe Z. Its initial coordinates are read from a text file.
 
  >> Version 2 - 26-III-2024
	- Update graphics/triangul - Porting to VC++ 2017 using winbgi

  >> Versión 1.0 14-X-2000
 Grafica un triángulo en un sistema 3D en pantalla rotando
 alrededor del eje Z. Sus coordenadas iniciales son leidas
 desde un archivo de texto.

 :::Programado por:::
 Jose Luis De La Cruz Lazaro
 YACSHA - Software & Desing
  >> ramondc@hotmail.com    
  >> EL MUNDO DEL CAOS - Unlimited Programming  

***********************************************************************/

#include "graphics.h"
//#include <math.h>
//#include <dos.h>
//#include <conio.h>
//#include <stdio.h>

//Contiene la posici¢n de un punto en el plano XY
struct punto
{
  int x; //coordenada x en unidades de pixel
  int y; //coordenada x en unidades de pixel
};

void DibujarTriangulo( punto *P )
{
	int i;
	for (i = 1; i < 3; i++)
	{
		moveto(P[i].x, P[i].y);
		lineto(P[i + 1].x, P[i + 1].y);
	}
	moveto(P[i].x, P[i].y);
	lineto(P[1].x, P[1].y);
}

int LeerPuntos( punto *P )
{

 FILE *puntos;

 if( (puntos = fopen("puntos.dat","r") )==NULL )
  return 0; //si no encuentra el archivo retorna cero

  printf("Triangle coordinate data, obtained from the points.dat file:\n\n");

 int i;
 for( i=0; i<4; i++)
 {
  fscanf(puntos, "%i %i", &P[i].x, &P[i].y );

  if( i==0 )
   printf("Pivot Point: ( %i, %i)\n",P[i].x, P[i].y);
  else
   printf("Vertex %i   : ( %i, %i)\n", i, P[i].x, P[i].y);
 }

 fclose(puntos);

 printf("\nEnter 1 to continue : ");
 int opt;
 scanf("%i", &opt);

 return 1;

}


int main()
{

 punto P[4];
 //Donde P[0] es el pivote y P[1], P[2], P[3] son
 //las coordenadas de los vertices del triangulo


 if( !LeerPuntos( P ) )
 {
  printf("El archivo puntos.dat no existe!!!");
  return 0;
 }
 
 // Init WinBGI window
 initwindow(1024, 768, "The world of chaos in C++ - Unlimited Programming");

// punto P[4]={{320,240},{50,220},{130,330},{250,100}};

 int i;
 double angulo=0.1,X,Y;

 while(1)
 {
   for( i=1;i<4;i++)
   {
    X=P[i].x-P[0].x; // posicion X relativa al pivote
    Y=P[i].y-P[0].y; // posicion Y relativa al pivote

    //Rotacion de coordenadas alrededor del eje Z
    P[i].x= P[0].x+X*cos(angulo)+Y*sin(angulo);
    P[i].y= P[0].y-X*sin(angulo)+Y*cos(angulo);
   }

   DibujarTriangulo( P ); //dibuja el triangulo
   delay(150); //tiempo de retrazo para dibujar nuevamente el triangulo
   cleardevice(); //borra la pantalla
   if( kbhit() ) break; //si se presiona una tecla se sale del bucle
 }

 closegraph();

 return 1;

}

