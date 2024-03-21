


	//METODO DE NEWTON(2 VARIABLES)
	// Si se tiene 2 funciones: F(x,y)=0 y G(x,y)=0
	// se puede hallar los conjuntos de solución (x,y)
	//que verifiquen simultaneamente este par de ecuaciones
	//utilizando este método 

	#include "conio.h"
	#include "fstream.h"
	#include "math.h"
	float F(float x,float y)
	{
	   return x*y*y-y-2;          //  F(x) = xy^2-y-2 = 0
	}                            //  G(x) = x^3y-6x-9 = 0
	   float G(float x,float y)
	{
	   return x*x*x*y-6*x-9;
	}
	   float Fx(float x,float y)
	{
	   return y*y;
	}
	   float Fy(float x,float y)
	{
	   return 2*y*x-1;
	}
	   float Gx(float x,float y)
	{
	   return 3*x*x*y-6;
	}
	   float Gy(float x,float y)
	{
	   return x*x*x;
	}
	   void main()
	{
	   double x,y,e,f,g,fx,fy,gx,gy,x1,y1;
	   clrscr();
	   cout<<"\n\tMETODO DE NEWTON (2 VARIABLES)\n";
	   cout<<"\n\tIngrese Xo = "; cin>>x;
	   cout<<"\tIngrese Yo = "; cin>>y;
	   cout<<"\tIngrese Error = "; cin>>e;
	   do{
		x1=x;y1=y;
		f=F(x,y);g=G(x,y);
		fx=Fx(x,y);fy=Fy(x,y);
		gx=Gx(x,y);gy=Gy(x,y);
		x=x+(-f*gy+g*fy)/(fx*gy-gx*fy);
		y=y+(-g*fx+gx*f)/(fx*gy-gx*fy);
		cout<<"\n\tSoluci¢n X = "<<x;
		cout<<"\tSoluci¢n Y = "<<y;
	     }
	   while ( sqrt((x1-x)*(x1-x)+(y1-y)*(y1-y))>e );
	   getch();
	}
