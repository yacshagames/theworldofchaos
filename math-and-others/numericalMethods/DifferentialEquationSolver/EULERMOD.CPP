


	//METODO DE EULER MODIFICADO

	#include "conio.h"
	#include "fstream.h"
	#include "math.h"
	double oper(double x,double y,double h)
	{
	   return y*(1+0.5*h*(1/x+2*x) )/(1-(1/(x+h)+2*(x+h))*0.5*h);
	}
	   void main()
	{
	   double fa,a,b,x,y,h,df;
	   clrscr();
	   cout<<"\n\tMETODO DE EULER MODIFICADO\n";
	   cout<<"\n\tIngrese a = "; cin>>a;
	   cout<<"\tIngrese b = ";   cin>>b;
	   cout<<"\tIngrese f(a) = "; cin>>fa;
	   cout<<"\tIngrese h = "; cin>>h;
	   x=a; y=fa;
	   do{
		y=oper(x,y,h);
		x=x+h;
		cout<<"\n\tx = "<<x;
		cout<<"\t\ty = "<<y;
	     } while (x<b);
	   getch();
	}


