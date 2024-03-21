/***********************************************************************
 ::: DATA MATRICIAL :::
  >> Versión 1.0 09-IV-2000

 OBTENER DATOS DE UNA MATRIZ
 Este programa suma las columnas y filas de una matriz , tambien calcula
 la suma de los elementos de la diagonal principal y la
 diagonal secundaria.

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

 //Obtener Datos
		//Suma de los elementos de la:
 int Sc[10];    //columna j
 int Sf[10];    //fila i
 int Sdp=0;     //diagonal principal
 int Sds=0;     //diagonal secundaria

 //inicializacion de variables
 for( i=0; i<n; i++)
 {
  Sc[i]=0;
  Sf[i]=0;
 }

 //Obtener sumas
 for( i=0; i<n; i++)
 {

   Sdp = Sdp + A[i][i];
   Sds = Sds + A[i][n-i-1];
    for( j=0; j<n; j++)
    {
     Sc[i] = Sc[i] + A[j][i];
     Sf[i] = Sf[i] + A[i][j];
    }
 }


 //Mostrar Datos

 cout<<"\nSuma de los elementos en la:";
 cout<<"\ndiagonal principal: "<<Sdp;
 cout<<"\ndiagonal secundaria: "<<Sds;

 for( i=0; i<n; i++)
 {
  cout<<"\ncolumna "<<i<<" : "<<Sc[i];
  cout<<"\nfila "<<i<<" : "<<Sf[i];
 }

}

