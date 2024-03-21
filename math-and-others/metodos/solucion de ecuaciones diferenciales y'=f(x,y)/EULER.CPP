

	//METODO DE EULER

	#include "conio.h"
	#include "fstream.h"
	#include "math.h"
	float Df(float x,float y)
	{
	   return y/x+2*x*y;
	   // Ecuacion Diferencial y'=y/x+2*x*y
	}
	   void main()
	{
	   float fa,a,b,x,y,h,df;
	   clrscr();
	   cout<<"\n\tMETODO DE EULER\n";
	   cout<<"\n\tIngrese a = ";cin>>a;
	   cout<<"\tIngrese b = ";cin>>b;
	   cout<<"\tIngrese f(a) = ";cin>>fa;
	   cout<<"\tIngrese h = ";cin>>h;
	   x=a;y=fa;
	   do{
		y=y+h*Df(x,y);
		cout<<"\n\tx = "<<x;
		cout<<"\t\t\ty = "<<y;
		x=x+h;
	   }
	   while (x<=b+h);
	   getch();
	}


