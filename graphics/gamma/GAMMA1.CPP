/****************************************************************************
GAMMA Versi¢n 1.1

Grafica la funcion gamma(x) de Euler, tambien se puede utilizar la funcion
gamma(x) para calcular la gamma de cualquier numero.

JOSE LUIS DE LA CRUZ LAZARO UNI-FIEE - 26/06/99
ramondc@hotmail.com
****************************************************************************/

#include "iostream.h"
#include "conio.h"
#include "grafxy.h"

long double n;

//integrando de la funcion gamma
long double f(long double &x)
{
return exp(-x)*pow(x,n-1);
}

int i;
//Cambiar los valores b y h para variar la aproximacion del resultado
//b tiende a infinito, h tiende a cero
long double a=0,b=15,h=0.1,xi,Sum;

double gamma(long double r)
{

 if(r>1)return (r-1)*gamma(r-1);  // r>1
 else
 {
   if(r<=0) 			  //r<=0
   {
   if( r==floor(r) ) return 0;    //si r es entero negativo incluyendo el cero
   else return gamma(r+1)/r;      //si r es real negativo no entero
   }
   else                           //0<r<=1
   {
    if(r==1)return 1;  //solo para darle mayor agilidad al programa
    else
    {
    //Aproximacion de la integral gamma por el
    //Metodo del Trapecio
    n=r+1;
    xi=a;
    Sum=( f(a)+f(b) )/2;
    for( xi+=h; xi<b; xi+=h) Sum+=f(xi);
    return h*Sum/r;

    }
  }
 }

}

void main()
{
//Busca los archivos graficos en la ruta especificada (Ruta de la carpeta bgi)
autoini("c:\\bc31\\bgi");

//Coordenadas de las esquinas del plano cartesiano de la pantalla
// R( xmin, xmax, ymin, ymax)
CRegionXY R(-5,5,-40,40);

//Grafica los ejes
R.Ejes();

double x;

//Grafica la funcion gamma
for(x=R.xmin();x<=R.xmax();x+=0.01)
R.punto(x,gamma(x),11);

getch();
closegraph();
}