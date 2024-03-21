/****************************************************************
GRAFXY 1.1

GRAFICADOR DE FUNCIONES EN 2D

JOSE LUIS DE LA CRUZ LAZARO UNI-FIEE - 26/06/99
ramondc@hotmail.com
****************************************************************/

#include <conio.h>
#include <graphics.h>
#include <math.h>
#include "ifuncade.h" 	//para que compile este programa copie ifunacade.h
			//en su directorio de includes

void main()
{
int gd=DETECT,gm;
initgraph(&gd,&gm,""); //aqui cambie la ruta de su carpeta bgi

double x,y;

char Funcion[80];

setcolor(2);
outtextxy(20,90,"Graficador de funciones para DOS Versi¢n 1.1");
setcolor(6);
outtextxy(20,120,"Jos‚ Luis De la Cruz L zaro - UNI-FIEE -1999-");
outtextxy(20,140,"Consultas y sugerencias a: ramondc@hotmail.com");
setcolor(3);
outtextxy(20,170,"Ingrese la funci¢n a graficar:");
gotoxy(10,15);cout<<"\n\t f(x) = ";

cin>>Formula;

cleardevice();

//Se establece las particiones de la pantalla (RANGO DE VISION DE LA FUNCION)
double minX=-5,maxX=5;
double minY=-5,maxY=5;

int m,n;

//Se halla las coordenadas del origen deacuerdo con la particion dada (m,n)
m=(-minX)*640/(maxX-minX)+1; 	//eje X
n=480-(-minY)*480/(maxY-minY)+1;//eje Y

//Se grafican los ejes cartesianos
setcolor(14);
line(m,480,m,0);
line(0,n,640,n);

for(x=-5;x<5;x+=0.01){

//Funcion a graficar y=f(x)
y=f(x,Formula);

m=(x-minX)*640/(maxX-minX)+1; 	//Conversion de real a entero x-->m
n=480-(y-minY)*480/(maxY-minY)+1;//Conversion de real a entero y-->n

putpixel(m,n,3);  //grafica la funcion en pantalla

}
getch();
closegraph();
}