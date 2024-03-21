/*GRAFXY.H fue creado por JLDL-SOFTWARE UNI-FIEE
Su uso se centra en la grafica de puntos y figuras en la pantalla,
principalmente de "graphics.h", pero tomando a la pantalla
como si fuera el plano cartesiano.
NOTA:	SI ALGUIEN QUIERE AGREGAR OTRA OPERACION MAS, HAGALO CON
	TODA CONFIANZA; PERO NO VAYA A BORRAR NADA DE LO QUE YA
	ESTA ECHO!!!!!!

Version 1.0 -> 26/11/98

Version 1.1 -> 27/11/98

Funcion:
	autoini()

Version 1.2 -> 7/12/98

Funcion:
	converl() //Converitdor de longitudes

Version 1.3 -> 10/04/99

Se adapto todas las funciones a la clase CRegionXY


Version 1.4 -> 23/05/99

Se acoplo la case ifuncade a grafxy, para graficar funciones instantaneamente
Se a¤ade la funcion Ejes() para graficar los ejes


*/
#include"iostream.h"
#include"conio.h"
#include"math.h"
#include"graphics.h"
#include"vector.h"
#include"stdlib.h"
//#include"ifuncade.h"

class CRegionXY
{

protected:

double Xmin;
double Xmax;
double Ymin;
double Ymax;

public:
//constructor
	CRegionXY(double XMIN, double XMAX, double YMIN, double YMAX)
	{
	Xmin=XMIN;
	Xmax=XMAX;
	Ymin=YMIN;
	Ymax=YMAX;
	}

	double xmin(){ return Xmin; };
	double xmax(){ return Xmax; };
	double ymin(){ return Ymin; };
	double ymax(){ return Ymax; };

	//Funciones Miembro
	vector conver(vector P);
	vector converl(vector R);
	void punto(vector P,int color);
	void punto(double x,double y,int color);
	void punto(double x,double y,int color,double minX,double maxX,double minY,double maxY);
	void Graficar( char Formula[], char color, double Particion);
	void Ejes();

};//fin de la clase CRegionXY

//Convierte un vector R de coordenadas reales a un vector M de
//coordenadas enteras, relativas al tama¤o de la pantalla
//II=(0,0) SD=(getmaxx,getmaxy)
//      |          |
//    entero      entero
//
//Donde la pantalla representara a una regi¢n rectangular R donde
//las esquinas son los vectores de coordenadas reales II y SD;
//II=InferiorIzquierda de la pantalla
//SD=SuperiorDerecha de la pantalla
//En resumen la Region R se transforma a una region rectangular W pero
//de coordenadas enteras que encaja en la pantalla

vector CRegionXY::conver(vector P)
{

return vector( (P.x-Xmin)*getmaxx()/(Xmax-Xmin)+1, 	//Conversion de real a entero x-->m
		getmaxy()-(P.y-Ymin)*getmaxy()/(Ymax-Ymin)+1 );//Conversion de real a entero y-->n
}

vector CRegionXY::converl(vector R)
{
vector M;
M=conver(R);
M=vector(M.x,getmaxy()-M.y);

return M;
}

//Grafica un punto que representa al punto P en la region rectangular
//especificada por II y SD y lo pinta del color especificado en color

void CRegionXY::punto(vector P,int color){

vector M=conver(P);

putpixel(M.x,M.y,color);  //grafica la funcion en pantalla

}

void CRegionXY::punto(double x, double y,int color)
{
punto( vector(x,y) , color );
}


//Igual que la funcion anterior pero sin vectores
//Grafica un punto en la pantalla pero tomando coordenadas reales (x,y)
//y un color especificado en color, donde su dominio es la region
//rectangular de esquinas:
//inferior izquierda (minX,minY) hasta superior derecha (maxX,maxY)

void CRegionXY::punto(double x,double y,int color,double minX,double maxX,double minY,double maxY){
//Se establece las particiones de la pantalla (RANGO DE VISION DE LA FUNCION)
//desde (minX,minY) hasta (maxX,maxY)
int m,n;

m=(x-minX)*getmaxx()/(maxX-minX)+1; 	//Conversion de real a entero x-->m
n=getmaxy()-(y-minY)*getmaxy()/(maxY-minY)+1;//Conversion de real a entero y-->n

putpixel(m,n,color);  //grafica la funcion en pantalla

}

void CRegionXY::Ejes()
{
//Se grafican los ejes cartesianos
vector M = conver(vector(0,0));
setcolor(14);
line(M.x,480,M.x,0);
line(0,M.y-1,640,M.y-1);

char *str;
int i;
double num;

setcolor(15);

for(i=0;i<20;i++)
{
//Eje Y
num = ymin() + ( ymax()-ymin() )/20*i;
gcvt(num, 6, str);
M=conver(vector(0,num));
fillellipse( M.x, M.y, 2, 1);
outtextxy(M.x, M.y, str);

 if(i%2)
 {
 //Eje X
 num = xmin() + ( xmax()-xmin() )/20*i;
 gcvt(num, 6, str);
 M=conver(vector(num,0));
 fillellipse( M.x, M.y, 1, 3);
 outtextxy(M.x, M.y-10, str);
 }

}

}

/*
void CRegionXY::Graficar( char Formula[], char color = 3, double Particion = 0.001)
{

double x,y;

for(x=xmin();x<xmax();x+=Particion)
{
//Funcion a graficar y=f(x)
y=f(x,Formula);
punto( vector(x,y), color);
}

}
*/

void autoini(char *ruta)
{
int gd=DETECT,gm;
initgraph(&gd,&gm,ruta);
}


