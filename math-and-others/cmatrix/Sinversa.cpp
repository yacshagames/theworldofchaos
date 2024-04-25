/***************************************************************************
SINVERSA (Super Inversa) 28-Febrero-1999

CALCULA LA INVERSA DE LA MATRIZ POR EL METODO DE LA TRANSPUESTA DE
DE LA MATRIZ DE COFACTORES:
METODO: A^-1 = (1/|A|) * (C)^t
donde C = matiz cofactor de A

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

double Determinante(double **A,int n)
{

double **C,M[30][30],B[30][30],D=0;

int x,y,i,j;

for(i=0;i<n;i++)
 for(j=0;j<n;j++)
 M[i][j]=A[i][j];


if(n>=2){

for(x=0;x<n;x++){

for(i=0;i<n-1;i++)
 for(j=1;j<n;j++)
  {
   if(i<x)B[i][j-1]=M[i][j];else B[i][j-1]=M[i+1][j];
  }

for(y=0;y<n-1;y++)*(C+y)=B[y];

D+=pow(-1,x)*M[x][0]*Determinante(C,n-1);

}

return D;

}else return M[0][0];

}

double **Inversa(double **A,int n)
{
int i,j,k,x,y;

double M[30][30],B[30][30],Ct[30][30],**P;

for(i=0;i<n;i++)
 for(j=0;j<n;j++)
 M[i][j]=A[i][j];

 //se crea la submatriz B de orden n-1
 //pivoteando en x,y

 for(x=0;x<n;x++)
  for(y=0;y<n;y++)
   {
    for(i=0;i<n-1;i++)
     for(j=0;j<n-1;j++)
      {
       if( i<x && j<y  )B[i][j]=M[i][j];
	else if( i<x && j>=y )B[i][j]=M[i][j+1];
	 else if( i>=x && j<y )B[i][j]=M[i+1][j];
	  else if( i>=x && j>=y)B[i][j]=M[i+1][j+1];
      }

    for(k=0;k<n-1;k++)*(P+k)=B[k];

    //Se halla la transpuesta de la matriz de cofactores
    Ct[y][x]=pow(-1,x+y)*Determinante(P,n-1);

   }

for(k=0;k<n;k++)*(P+k)=Ct[k];

return P;
}

void main()
{

double **A,**InvA,B[30][30];
int i,j,n;
clrscr();

cout<<"Ingrese orden de la matriz : ";cin>>n;//se ingresa orden de la matriz

for(i=0;i<n;i++)	//se ingresa los elementos de la matriz A
	for(j=0;j<n;j++){
		cout<<"Ingrese A["<<i<<","<<j<<"] : ";cin>>B[i][j];}


for(i=0;i<n;i++)*(A+i)=B[i];

InvA=Inversa(A,n);

for(i=0;i<n;i++)
 for(j=0;j<n;j++)
 B[i][j]=InvA[i][j];

clrscr();

double D=Determinante(A,n);

cout<<"LA MATRIZ INVERSA ES :";
	gotoxy(1,int(n/2)+(pow(-1,n+1)+1)/2+2);cout<<"I = ";
	cout<<abs(D)/D<<"/"<<abs(D)<<" * ";

	for(i=0;i<n;i++){
		gotoxy(13,3+i);cout<<"³";
		for(j=0;j<n;j++)
			cout<<D*B[i][j]<<" ";
		cout<<"³\n";}

cout<<"\n\nDeterminante= "<<Determinante(A,n);
getch();

}