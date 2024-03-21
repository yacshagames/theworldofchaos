/***************************************************************************
SDETERM (Super Determinante) 21-Enero-1999

Este programa calcula con facilidad la determinante de matrices de orden alto.
Se utiliza el m‚todo los cofactores de la matriz (pivoteando).
Se utiliza recursividad, por lo que el progrma necesita bastante memoria.

programado por:
 JOSE LUIS DE LA CRUZ LAZARO
correos:
 jcruz@ec-red.com
 ramondc@hotmail.com
Pagina Web ( EL MUNDO DEL CAOS ):
 http://www.geocities.com/joseluisdl
***************************************************************************/
#include"iostream.h"
#include"conio.h"
#include"math.h"

//Funcion Recursiva que retorna el determinante de la matriz A
double Determinante(double **A,int n)
{

double **C,P[30][30],B[30][30],D=0;

int x,y,i,j;

for(i=0;i<n;i++)
 for(j=0;j<n;j++)
 P[i][j]=A[i][j];


if(n>=2){

for(x=0;x<n;x++){

for(i=0;i<n-1;i++)
 for(j=1;j<n;j++)
  {
   if(i<x)B[i][j-1]=P[i][j];else B[i][j-1]=P[i+1][j];
  }

for(y=0;y<n-1;y++)*(C+y)=B[y];

D+=pow(-1,x)*P[x][0]*Determinante(C,n-1);

}

return D;

}else return P[0][0];

}

void main()
{

 double **A, //puntero doble que apunta a matrices
	B[10][10]; //matriz est tica que contendr  los datos
 int i,j,n;
 clrscr();

 cout<<"Ingrese orden de la matriz : ";
 cin>>n;//se ingresa orden de la matriz

 for(i=0;i<n;i++)	//se ingresa los elementos de la matriz A
  for(j=0;j<n;j++)
  {
   cout<<"Ingrese A["<<i<<","<<j<<"] : ";
   cin>>B[i][j];
  }

 //A apunta a B
 for(i=0;i<n;i++)
  *(A+i)=B[i];

 //Se retorna el determinante de B
 cout<<"\nDeterminante = "<<Determinante(A,n);

 getch();

}