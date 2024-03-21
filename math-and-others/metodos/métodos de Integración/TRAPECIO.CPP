


	//METODO DE EL TRAPECIO

	#include "conio.h"
	#include "fstream.h"
	#include "math.h"
	float f(float x)
	{
	   return exp(-x*x)/sqrt(2*3.141592);
	}
	   void main()
	{
	   float fa,fb,a,b,h,x,I,n;
	   clrscr();
	   cout<<"\tMETODO DEL TRAPECIO\n";
	   cout<<"\n\tIngrese a = "; cin>>a;
	   cout<<"\tIngrese b = "; cin>>b;
	   cout<<"\tIngrese n = "; cin>>n;
	   h=(b-a)/n;
	   x=a+h;I=0;
	   do{
		I=I+f(x);
		x=x+h;
	     }
	   while (x<b);
	   fa=f(a);fb=f(b);
	   I=h*(fa+2*I+fb)/2;
	   cout<<"\n\tIntegral I = "<<I;
	   getch();
	}


