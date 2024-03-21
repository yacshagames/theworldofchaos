	//METODO DE PREDICTOR CORRECTOR

	#include "conio.h"
	#include "fstream.h"
	#include "math.h"
	double f(double x,double y)
	{
	   return y/x+2*x*y;
	   // Ecuacion Diferencial y'=y/x+2*x*y
	}
	   void main()
	{
	   double fa,a,b,x,y,y1,h,df,yo,error=1e-6;
	   int n=1;
	   clrscr();
	   cout<<"\n\tMETODO DE PREDICTOR CORRECTOR\n";
	   cout<<"\n\tIngrese a = ";cin>>a;
	   cout<<"\tIngrese b = ";cin>>b;
	   cout<<"\tIngrese f(a) = ";cin>>fa;
	   cout<<"\tIngrese h = ";cin>>h;
	   x=a;y=fa;
	   do{
		//PREDICTOR: EULER
		yo=y;
		y=y+h*f(x,y);
		//CORRECTOR: EULER MODIFICADO
		do{
		y1=y;
		y=yo+0.5*h*( f(x,yo)+f(x+h,y) );
		}while( fabs(y-y1)<error);

		cout<<"\n\tx = "<<x;
		cout<<"\t\t\ty = "<<yo;
//		n=n+1;
		x=x+h;
	     }
	   while (x<=b+h);
	   getch();
	}


