/***************************************************************************
INVRECU (Inversa Recursiva) 28-Febrero-1999

Calcula la inversa de una matriz con funciones recursivas. No nesecita mucha
memoria.

programado por:
 JOSE LUIS DE LA CRUZ LAZARO
correos:
 jcruz@ec-red.com
 ramondc@hotmail.com
Pagina Web ( EL MUNDO DEL CAOS ):
 http://www.geocities.com/joseluisdl
***************************************************************************/
#include"fstream.h"
#include"conio.h"
#include"math.h"
int orden;

double A[30][30],D=1;

void escalonada(int osm){
//osm: Orden de la SubMatriz
int i,j,k,m,s,t;
double tmp,T;
m=orden;
k=orden-osm;
//SE HALLA LA INVERSA DE R por Gauss J.
//Se reduce la matriz por operaciones elementales comenzando por A[0][0]
		for(i=k;i<m;i++){
			T=A[i][k];
			for(s=i;s<m-1&&T==0;s++)   // si T=0 se intercambia la fila i con la fila i+1,i+2... hasta que T!=0
				for(t=0;t<2*m;t++){
					tmp=A[i][t];
					A[i][t]=A[s+1][t];
					A[s+1][t]=tmp;
				T=A[i][k];
				}

			T=A[i][k];
			if(T==0)continue;

		for(j=2*m-1;j>=0;j--){	//Se disminuye el valor de j para que el valor de A[i][0] solo sea alterado al final
			if(i==k)A[i][j]/=T; //se divide a la primera fila por el primer termino de la fila
			else A[i][j]=A[i][j]/T-A[k][j]; //(A partir de la segunda fila) se divide la fila i por el primer termino de la fila i
			}

		D*=T;
		}
if(osm!=0)escalonada(osm-1);


}//fin de la funcion escalonada


void inversa(int osm){
//osm:orden de la submatriz
int j,k,m,t;
double T;
m=orden;
k=orden-osm;

	for(t=k+1;t<m;t++){
		T=A[k][t];
		for(j=0;j<2*m;j++)
			A[k][j]-=T*A[t][j];
		}
if(osm!=0)inversa(osm-1);

}//fin de la funcion inversa

void main()
{

 clrscr();
 int i,j,m;

 cout<<"Ingrese orden de la matriz : ";
 cin>>orden;//se ingresa orden de la matriz
 m=orden;

 for(i=0;i<=m-1;i++)	//se ingresa los elementos de la matriz A
  for(j=0;j<=m-1;j++)
  {
   cout<<"Ingrese A["<<i<<","<<j<<"] : ";
   cin>>A[i][j];
  }

  for(i=0;i<=m-1;i++)         //Se anexa a esta matriz una matriz identidad de orden m para aplicar Gauss - Jordan
   for(j=m;j<=2*m-1;j++)
    if(i+m==j)
     A[i][j]=1;
    else
     A[i][j]=0;

 escalonada(orden);//Recursiva para la matriz escalonada

 double PD;//PD:Producto de la Diagonal

 for(i=0;i<m;i++) //se calcula producto de los elementos de la diagonal de la matriz escalonada
  PD*=A[i][i];

 clrscr();

 if(PD==0)
 {
  cout<<"\n\n\LA MATRIZ NO ES INVERSIBLE!!!";
  getch();
 }
 else
 {
  inversa(orden);//Recursiva para la matriz inversa

  //Muestra la inversa en pantalla
  D*=pow(-1,orden);//D es el determinante

  cout<<"LA MATRIZ INVERSA ES :";
  gotoxy(1,int(orden/2)+(pow(-1,orden+1)+1)/2+2);
  cout<<"I = ";
  cout<<abs(D)/D<<"/"<<abs(D)<<" * ";

  for(i=0;i<m;i++)
  {
   gotoxy(13,3+i);
   cout<<"³";

   for(j=m;j<2*m;j++)
    cout<<D*A[i][j]<<" ";

   cout<<"³\n";
  }

  cout<<"\nDeterminante = "<<D;
  getch();
 }
}