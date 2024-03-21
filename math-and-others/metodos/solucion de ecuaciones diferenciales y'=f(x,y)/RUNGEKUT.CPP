


	//METODO DE RUNGE KUTTA DE ORDEN 2

	#include "conio.h"
	#include "fstream.h"
	#include "math.h"

	double f(double x,double y)
	{
	   return y/x+2*x*y;
	   // Ecuacion Diferencial y'=y/x+2*x*y
	}


	double K1(double h,double y,double x)
	{
	   return h*f(x,y); // Ecuacion Diferencial
				  // y'=-0.4y+0.2
	}
	   double K2(double h,double y,double x,double k1)
	{
	   return h*f(x+h,y+k1);
	}
	   void main()
	{
	   double fa,a,b,x,y,h,k1,k2;
	   clrscr();
	   cout<<"\n\tMETODO DE RUNGE KUTTA (ORDEN 2)\n";
	   cout<<"\n\tIngrese a = ";  cin>>a;
	   cout<<"\tIngrese b = ";    cin>>b;
	   cout<<"\tIngrese f(a) = "; cin>>fa;
	   cout<<"\tIngrese h = ";    cin>>h;
	   x=a; y=fa;
	   do{
		k1=K1(h,y,x);
		k2=K2(h,y,x,k1);
		x=x+h;
		y=y+(k1+k2)/2;
		cout<<"\n\tk1 = "<<k1;
		cout<<"\tk2 = "<<k2;
		cout<<"\tx = "<<x;
		cout<<"\ty = "<<y;
	     }
	   while (x<b);           	
	   getch();
	}


