/*********************************************************************
GRAFXY.H

Plots points of a function on the screen, in the specified region
of the Cartesian plane.

The screen is taken as if it were the specified region of the
Cartesian plane.

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

>> Version 2 - 21-III-2024
	- Update graphics/gxydemo - Porting to VC++ 2017 using winbgi

Versión 1.8 -> 24-Agosto-2000
-Se arregla parcialmente el error de que cuando la función se salia de la ventana
 marco y despues volvia entrar, se unia con una linea el punto de salida
 y el punto de entrada.

Versión 1.7 -> 15/Mayo/2000
-Se dividio grafxy en:
 grafxy (grafxy basico) que contiene las funciones mas usadas.
 grafxya (grafxy avanzado) que contiene funciones que complementan a grafxy
-Se elimina el trabajo con vectores para darle mayor velocidad a la
 transformacion
-se eliminan funciones que nunca son usadas, y se agiliza el proceso de
 transformacion creando constantes ( ki, kj ).
-La funcion CFungraf pasa a formar parte de grafxya


Version 1.6 -> 11/08/1999
-Se modifica la clase CRegionXY, añadiendo las variables miembro
 (Imin,Jmin,Imax,Jmax) que representan las coordenadas de una
 pantalla virtual, donde se graficaran los puntos (estas coordenadas
 son en pixels).
-Se modifico todas las funciones, para que trabajen con las nuevas variables.
-Se modifica la funcion miembro Ejes(), ahora utiliza sprintf para convertir
 un numero float a cadena de texto

Version 1.5 -> 25/07/99

Se añade la funcion Conectar() para conectar los puntos de la grafica

Version 1.4 -> 23/05/99

Se acoplo la cabecera ifuncade a grafxy, para graficar funciones instantaneamente
Se añade la funcion Ejes() para graficar los ejes

Version 1.3 -> 10/04/99

Se adapto todas las funciones a la clase CRegionXY

Version 1.2 -> 7/12/98

Funcion:
	converl() //Converitdor de longitudes

Version 1.1 -> 27/11/98

Funcion:
	autoini()

Version 1.0 -> 26/11/98

**********************************************************************/

/*#ifndef __GRAPHICS_H
#include <graphics.h>
#endif*/
#include <stdio.h>

#define CONECTAR 1
#define NOCONECTAR 0

class CRegionXY
{

protected:

//coordenadas de la region XY, (VALOR EN COORDENAS REALES)
double Xmin;
double Xmax;
double Ymin;
double Ymax;

//VENTANA MARCO
//coordenadas de la ventana donde se mostrara el grafico (VALOR EN PIXELES)
int Imin;
int Imax;
int Jmin;
int Jmax;

double ki,kj; //constanstes utilizadas en la transformacion

public:
//constructor
	CRegionXY(double XMIN, double XMAX, double YMIN, double YMAX)
	{
	Xmin=XMIN;
	Xmax=XMAX;
	Ymin=YMIN;
	Ymax=YMAX;
	Imin=0;
	Imax=getmaxx();
	Jmin=0;
	Jmax=getmaxy();
	ki=(Imax-Imin)/(Xmax-Xmin);
	kj=(Jmax-Jmin)/(Ymax-Ymin);
	}

	CRegionXY(double XMIN, double XMAX, double YMIN, double YMAX,
		  int IMIN,int JMIN, int IMAX, int  JMAX)
	{
	Xmin=XMIN;
	Xmax=XMAX;
	Ymin=YMIN;
	Ymax=YMAX;
	Imin=IMIN;
	Jmin=JMIN;
	Imax=IMAX;
	Jmax=JMAX;
	ki=(Imax-Imin)/(Xmax-Xmin);
	kj=(Jmax-Jmin)/(Ymax-Ymin);
	}

	double xmin(){ return Xmin; };
	double xmax(){ return Xmax; };
	double ymin(){ return Ymin; };
	double ymax(){ return Ymax; };

	//Funciones Miembro
	void transfor( int &i, int &j, double x, double y);
	void punto(double x,double y,char color, char conectar);
	void Ejes();

};//fin de la clase CRegionXY

//Convierte un punto de coordenadas reales (x,y) , a un pixel de
//coordenadas enteras (i,j) respecto al origen grafico de la pantalla
//NOTA: el valor de i y j se sobreescribiran
void CRegionXY::transfor( int &i, int &j, double x, double y)
{
   i = Imin+(x-Xmin)*ki+1;//Transformación de real a entero x-->i
   j = Jmax-(y-Ymin)*kj+1;//Transformación de real a entero y-->j
}

//Grafica el PUNTO (x,y) en coordenadas reales sobre la region
//rectangular de la PANTALLA de coordenadas (Xmin,Ymax, Xmax,Ymin)
void CRegionXY::punto(double x, double y, char color, char conectar = CONECTAR)
{
 int i,j;
 transfor( i, j, x, y);

 if( Imin< i && i< Imax && Jmin< j && j< Jmax) //para que no se pinte fuera de la ventana marco
 {
  if( conectar )
   {
    if(getcolor()!=color)moveto(i,j);
    setcolor(color);
    lineto(i,j); //conecta los puntos con una linea
   }
  else
   putpixel( i, j, color);  //pinta el punto en pantalla

 }//else
//  moveto(i,j); //si el punto no se encuentra dentro de la ventana marco, solo se se mueve el cursor a esta posición

}

void CRegionXY::Ejes()
{
//Se grafican los ejes cartesianos
//vector M = transfor(vector(0,0));
setcolor(14);
int x, y;
transfor( x, y, 0, 0);

line(x, Jmin, x, Jmax); //eje y
line(Imin,y-1,Imax,y-1); // eje x

char str[18];

int i;
float num;

setcolor(15);

for(i=0;i<20;i++)
{
//Eje Y
num = Ymin + ( Ymax-Ymin )/20*i;
//gcvt(num, 6, str);
sprintf(str,"%g",num);

transfor( x, y, 0, num);

fillellipse( x, y, 2, 1);
outtextxy(x, y, str);

 if(i%2)
 {
 //Eje X
 num = Xmin + ( Xmax-Xmin )/20*i;
// gcvt(num, 6, str);
 sprintf(str,"%g",num);
 transfor( x, y, num, 0);

 fillellipse( x, y, 1, 3);
 outtextxy(x, y-10, str);
 }

}

}

/*void autoini(char *ruta)
{
int gd=DETECT,gm;
initgraph(&gd,&gm,ruta);
}*/


