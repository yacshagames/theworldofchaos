/*********************************************************************
CONICAS - 15 de Mayo del 2000
Programa que grafica cónicas en su forma general

programado por:
 JOSE LUIS DE LA CRUZ LAZARO

  UNIVERSIDAD NACIONAL DE INGENIERIA
  Facultad de Ingenier¡a El‚ctrica y Electr¢nica
  Lima-Per£

correos:
 jcruz@ec-red.com
 ramondc@hotmail.com 
Pagina Web ( EL MUNDO DEL CAOS ):
 http://www.geocities.com/joseluisdl
*********************************************************************/
#include "iostream.h"
#include "math.h"
#include "conio.h"
#include "grafxy.h"

void main()
{

 //conica general de la forma AX^2+BXY+CY^2+DX+EY+F=0

 double A,B,C,D,E,F;

  cout<<"\tConica General de la forma AX^2+BXY+CY^2+DX+EY+F=0";
  cout<<"\n\nIngrese los coeficientes de la c¢nica:";
  cout<<"\nA: ";
  cin>>A;
  cout<<"B: ";
  cin>>B;
  cout<<"C: ";
  cin>>C;
  cout<<"D: ";
  cin>>D;
  cout<<"E: ";
  cin>>E;
  cout<<"F: ";
  cin>>F;

//ruta de la carpeta bgi de tu compilador (controladores graficos)
//si se deja vacio ("") busca el controlador bgi en la misma carpeta
//del ejecutable de este programa
 autoini(""); 

 CRegionXY R(-10, //xminino
	     10,  //xmaximo
	     -10, //yminimo
	     10); //ymaximo

 R.Ejes(); //dibuja los ejes


 //para graficar la conica despejamos y en funcion de x
 //y obtemenemos CY^2+(BX+E)Y+AX^2+DX+F=0
 //luego obtenemos Y como:
 //Y = (-b +- sqrt( b^2-4ac ) )/(2a)
 //donde a,b,c se definen a=C, b=BX+E, c=AX^2+DX+F;
 double a=C,b,c,Discriminante;

 double x,y;
 for( x=R.xmin();x<R.xmax();x+=0.01)
 {
  b=B*x+E;
  c=A*x*x+D*x+F;
  Discriminante=b*b-4*a*c;

  if( Discriminante>=0 )
  {
   y=(-b+sqrt(Discriminante))/(2*a);
   R.punto(x,y,GREEN);
   y=-y-b/a;
   R.punto(x,y,GREEN);
  }
 }

 getch();
 closegraph();
}