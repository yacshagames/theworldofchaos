/*********************************************************************
CONICS
Program that plots conics in their general form
AX^2+BXY+CY^2+DX+EY+F=0

Programmed by:
 JOSE LUIS DE LA CRUZ LAZARO

  UNIVERSIDAD NACIONAL DE INGENIERIA
  Faculty of Electrical and Electronic Engineering
  Lima-Peru

correos:
 ramondc@hotmail.com 
Pagina Web ( EL MUNDO DEL CAOS )

 HISTORY...

 >> Version 2 - 26-III-2024
	- Update graphics/conicas - Porting to VC++ 2017 using winbgi

>> Version 1 - 15-V-1999
	- First version for Borland C++ 3.1 and Turbo C 3.0

*********************************************************************/

#include "graphics.h"
#include <iostream>
//#include "math.h"
//#include "conio.h"
#include "grafxy.h"
using namespace std;

void main()
{

 //conica general de la forma AX^2+BXY+CY^2+DX+EY+F=0

 double A,B,C,D,E,F;

  cout<<"\tGeneral Conic Shape PLOTTER: AX^2+BXY+CY^2+DX+EY+F=0";
  cout<<"\n\nEnter the coefficients of the conic:";
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

 // Init WinBGI window
 initwindow(1024, 768, "The world of chaos in C++ - Unlimited Programming");

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