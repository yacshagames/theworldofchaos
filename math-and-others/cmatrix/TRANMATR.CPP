/***********************************************************************
 ::: DATA MATRICIAL :::
  >> Versión 1.0 09-IV-2000

 CALCULA LA TRANSPUESTA DE UNA MATRIZ

 :::Programado por:::
 José Luis De La Cruz Lázaro
 YACSHA - Software & Desing 2002
  >> yacsha@elmundodelcaos.tk    
  >> www.elmundodelcaos.tk -> EL MUNDO DEL CAOS - Unlimited Programming
  >> www.foros3d.tk  -> Foros de discusión  Flash/ActionScript - C/C++

***********************************************************************/
#include <iostream.h>

void main()
{
 int A[10][10],n,i,j;

 //Ingreso de elementos de la matriz
 cout<<"Ingrese el orden de la matriz: ";
 cin>>n;

 for( i=0; i<n; i++)
  for( j=0; j<n; j++)
  {
   cout<<"Ingrese elemento A["<<i<<"]["<<j<<"] : ";
   cin>>A[i][j];
  }

 int tmp; //variable temporal para intercambio

 //se intercambia valores de los elementos simetricos de la matriz
 //(definicion de matriz transpuesta)
 for( i=0; i<n; i++)
  for( j=0; j<i; j++)
  {
   tmp = A[i][j];
   A[i][j] = A[j][i];
   A[j][i] = tmp;
  }

 //mostrar transpuesta
 cout<<"\nMatriz transpuesta:\n";
  for( i=0; i<n; i++)
  {
   for( j=0; j<n; j++)
    cout<<A[i][j]<<" ";

   cout<<"\n";
   }

}

