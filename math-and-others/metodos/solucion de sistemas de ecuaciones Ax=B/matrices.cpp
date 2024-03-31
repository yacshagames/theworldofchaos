/*********************************************************************
METODOS NUMERICOS PARA SOLUCIONAR SISTEMAS DE ECUACIONES ( MATRICES )

programado por:
JOSE LUIS DE LA CRUZ LAZARO 	UNI-FIEE 30 Nov 1999
ramondc@hotmail.com
Pagina Web: http://www.geocities.com/joseluisdl/jldl.htm
**********************************************************************/
#include <iostream> //cout cin
#include "graphics.h"
#include "conio.h" //clrscr() getch() gotoxy() getchar() cprintf() textcolor()
/*#include <math.h> //fabs() pow() sqrt()
#include <ctype.h>// toupper()

//"menu.h"
//RUTINA PARA CREAR UN MENU VIRTUAL EN EL MODO TEXTO
#ifndef __STDLIB_H
#include <stdlib.h>
#endif

#ifndef __CONIO_H
#include <conio.h>
#endif

#ifndef __STDIO_H
#include <stdio.h>
#endif

#ifndef __BIOS_H
#include <bios.h>
#endif
*/
/*
// The standard Borland 16 colors
#define MAXCOLORS       15
enum colors {
	BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY, DARKGRAY,
	LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE
};
*/
using namespace std;

int MENU (const char *vec[],int x,int y,int dim,int puntero,int col);
///
void CUADRO(int x1,int y1,int ancho,int largo,int col);

void Imprimir_Raiz( int iteracion, double raiz)
{
 cout<<"\nIteraci¢n "<<iteracion<<"\tRaiz = "<<raiz;
}

void textcolor(int color) {

}
/*
void gotoxy(short int x, short int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}*/

int wherex()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.X;
}

int wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.Y;
}


//////////////////////////////////////////////////////////////////////
//ALGORITMO LU POR DESCOMPOSICION GAUSSIANA
//////////////////////////////////////////////////////////////////////
void LU_Gauss(int n, double W[10][10] ,int p[10] )
{

  int i,j,k;

 // se inicializa p
 for(i=0;i<n;i++)
  p[i]=i;

 double m; //multiplicador

 //Calculo de la matriz W
 for(k=0;k<n-1;k++)
 {
   //se halla (el menor) j>=k tal que W[p[j]][k]!=0
   for(j=k;j<n;j++)
    if( W[p[j]][k]!=0 )
    {//se intercambia los contenidos de p[k] y p[j]
     m=p[k];
     p[k]=p[j];
     p[j]=m;
     break; //se encontro el j buscado
    }

   if(j==n)//no se encontro el j buscado
   {
    cout<<"La matriz no es inversible";
    return;
   }

  for(i=k+1;i<n;i++)
  {
   m=W[p[i]][k]=W[p[i]][k]/W[p[k]][k];

   for(j=k+1;j<=n;j++)
    W[p[i]][j]-=m*W[p[k]][j];

  }
 }

 //existe un cero en la diagonal
 if(W[p[n-1]][n-1]==0)
 {
  cout<<"La matriz no es inversible";
  return;
 }

}

/////////////////////////////////////////////////////////////////////
//ALGORITMO DE DESCOMPOSICION LU UTILIZANDO LA ESTRATRATEGIA DEL
//PIVOTE MAXIMO
//////////////////////////////////////////////////////////////////////
void LU_Pivot_Maximo(int n, double W[10][10] ,int p[10] )
{

 int i,j,k;
 double m; //multiplicador
 double d[10];// d[i]= maximo( |Wij| ) 0<=j<n
      // d[i] = maximo valor absoluto de los elementos de la fila i de W

 for(i=0;i<n;i++)
 {
  p[i]=i;

 //Se halla los maximos valores absolutos de cada fila y se los guarda en d[i]
 for( j=0, d[i]=0 ; j<n; j++)
 {
  m=fabs(W[i][j]);
  if( m>d[i] ) d[i]=m;
 }

  if(d[i]==0)
  {
    cout<<"La matriz no es inversible";
    return;
  }

 }

  //Calculo de la matriz W
 for(k=0;k<n-1;k++)
 {
   //se halla (el menor) j>=k tal que
   //fabs(W[p[j]][k])/d[p[j]] >= fabs(W[p[i]][k])/d[p[i]]
   for(j=k;j<n;j++)
   {
    for(i=k;i<n;i++)
    if(  fabs(W[p[j]][k])/d[p[j]] < fabs(W[p[i]][k])/d[p[i]] ) break;

    if(i==n ) // se encontro el j buscado
    {//se intercambia los contenidos de p[k] y p[j]
     i=p[k];
     p[k]=p[j];
     p[j]=i;
     break;
    }
  }

  for(i=k+1;i<n;i++)
  {
   m=W[p[i]][k]=W[p[i]][k]/W[p[k]][k]; // se asigna el multiplicador de la fila pivote

   for(j=k+1;j<=n;j++)
      W[p[i]][j]-=m*W[p[k]][j];

  }
 }

 //existe un cero en la diagonal
 if(W[p[n-1]][n-1]==0)
 {
  cout<<"La matriz no es inversible";
  return;
 }
}

//////////////////////////////////////////////////////////////////////
//ALGORITMO DE DESCOMPOSICION LU UTILIZANDO EL METODO DE CHOLESKY
//////////////////////////////////////////////////////////////////////
void LU_Cholesky( int n, double W[10][10], double x[10] )
{
 double L[10][10],Sum;
 int i,j,k;

 for(j=0;j<n;j++)
 {

   for(Sum=0,k=0;k<j;k++) Sum+=pow(L[j][k],2);

    L[j][j]=sqrt(W[j][j]-Sum);

   for(i=j+1;i<n;i++)
   {
     for(Sum=0,k=0;k<j;k++) Sum+=L[i][k]*L[j][k];

      L[i][j]=(W[i][j]-Sum)/L[j][j];
   }
 }

//  se asigna la matriz L a la matriz W
   for(j=0;j<n;j++)
    for(i=j;i<n;i++)
     if( j==i ) W[i][i]=L[i][i];
     else W[i][j]=W[j][i]=L[i][j];

     //sustitucion hacia adelante y hacia atraz
     double b[10];
     for(k=0;k<n;k++)
     {
      Sum=0.0;
       for(j=0;j<k;j++) Sum+=W[k][j]*b[j];
      b[k]=W[k][n]-Sum;
     }

     for(k=n-1;k>=0;k--)
     {
      Sum=0.0;
       for(j=k+1;j<n;j++) Sum+=W[k][j]*x[j];
      x[k]=(b[k]-Sum)/W[k][k];
     }



}

//////////////////////////////////////////////////////////////////////
//ALGORITMO DE ITERACION DE GAUSS-SEIDEL
//////////////////////////////////////////////////////////////////////
void Gauss_Seidel(int n, double W[10][10], double x[10] )
{
 double B[10][10],C[10],x_ant[10];
 int i,j,k;

 for(i=0;i<n;i++)
 {
  for(j=0;j<n;j++)
   B[i][j]= i==j ? 0 : -W[i][j]/W[i][i];

   C[i]=W[i][n]/W[i][i];
   x[i]=0;
  }

 double Sum,m;

 for(m=0;m<10;m++)
  for(i=0;i<n;i++)
  {
   for(k=0;k<n;k++)
    x_ant[k]=x[k]; //guardo el vector anterior Xm-1=Xm

   Sum=0.0;

   for(j=0;j<i;j++)
    Sum+=B[i][j]*x[j];
   for(j=i+1;j<n;j++)
    Sum+=B[i][j]*x_ant[j];

   x[i]=Sum+C[i];
  }

}
/*/////////////////////////////////////////////////////////////////////////////
FUNCIONES PARA MOSTRAR LAS MATRICES:  x p L U
x: matriz columna con las solucion del sistema Ax=B
p: vector de permutacion del sistema
L: matriz triangular inferior
U: matriz triangular superior
Nota: PLU=A
donde P se calcula a partir de p
////////////////////////////////////////////////////////////////////////////*/
void Calcular_Solucion_del_Sistema_LU( int n, double W[10][10], double x[10], int p[10] )
{
 int i,j,k;
 //se procede a calcular la matriz x
 double Sum;  //variable que contendra la sumatoria
 for(k=n-1;k>=0;k--)
 {
  for(Sum=0,j=k+1;j<n;j++)
    Sum+=W[p[k]][j]*x[j];
  x[k]=(W[p[k]][n]-Sum)/W[p[k]][k];
 }

}

void Mostrar_Solucion_del_Sistema( int n, double x[10] )
{
   cout<<"\nSoluci¢n al sistema Ax=B: \n";
   textcolor(LIGHTCYAN);
   for(int i=0;i<n;i++)
    {
     printf("x[%i] = %g", i+1, x[i]);
     cout<<"\n";
    }
}


void Mostrar_Matriz_de_Permutacion(int n, int p[10] )
{
   cout<<"\n\n";
   textcolor(BROWN);
   printf("Matriz de permutaci¢n p:");
   cout<<"\n";
   printf("p = [ ");
   for(int i=0;i<n;i++)
     printf("%i ", p[i]+1);
   printf("]");
}

void Mostrar_Matrices_LU( int n, double W[10][10], int p[10] )
{
   int i,j;
   cout<<"\n\n";
   textcolor(LIGHTMAGENTA);
   printf("Matriz L:");
   cout<<"\n";

   for(i=0;i<n;i++)
   {
     for(j=0;j<n;j++)
     {
       if(j==i)cout<<"1\t";
       else
       if(j>i)cout<<"0\t";
       else
       cout<<W[p[i]][j]<<"\t";
     }
      cout<<"\n";
   }

   cout<<"\n\n";
   textcolor(WHITE);
   printf("Matriz U:");
   cout<<"\n";
   for(i=0;i<n;i++)
   {
     for(j=0;j<n;j++)
     {
      if(j<i) cout<<"0";
      else cout<<W[p[i]][j];
      gotoxy(wherex()+9,wherey());
     }
      cout<<"\n";
   }

}

void Ingresar_Sistema( int &n, double W[10][10] )
{
 int i,j;

 clrscr();
 cout<<"\n\nIngrese el sistema Ax=B :\n\n"
     <<"Ingrese el numero de inc¢gnitas: ";
 cin>>n;//se ingresa orden de la matriz de la matriz A

 cout<<"\nIngrese los elementos de la matriz A:\n";
 textcolor(YELLOW);
 for(i=0;i<n;i++)	//se ingresa los elementos de la matriz A
 {
   for(j=0;j<n;j++)
   {
    printf("A[%i,%i] = ",i,j);
    cin>>W[i][j];
   }
  cout<<"\n";
 }

 cout<<"\nIngrese los elementos de la matriz B:\n";
 textcolor(LIGHTGREEN);
 for(i=0;i<n;i++)	//se ingresa los elementos de la matriz B
 {
  printf("B[%i] = ",i);
  cin>>W[i][n];
 }
}
void Visualizar_Sistema( int &n, double W[10][10] )
{
//  textcolor(LIGHTGRAY);
 int i,j;
  clrscr();

   cout<<"\n\nSistema Ax=B Ingresado: \n";

   textcolor(YELLOW);
   printf("Matriz A");

   gotoxy(9*n,wherey());
   textcolor(LIGHTGREEN);
   printf("Matriz B");

   cout<<"\n";
   for(i=0;i<n;i++)
   {
     //Imprime Matriz A
     textcolor(YELLOW);
     for(j=0;j<n;j++)
     {
       printf("%g",W[i][j]);
       cout<<"\t";
     }

     //Imprime Matriz B
     textcolor(LIGHTGREEN);
     printf("%g",W[i][n]);

     cout<<"\n";
    }
  getch();
}

void Inicializar_Matriz_de_Trabajo( int &n, double W[10][10], double Wo[10][10] )
{
 int i,j;
 for(i=0;i<n;i++)
   for(j=0;j<=n;j++)
    W[i][j]=Wo[i][j];
}

void main()
{
	initwindow(0, 0);

 double x[10],W[10][10],Wo[10][10];
 int n=-1,p[10];
 //x: contiene la solucion del sistema Ax=B
 //W: Matriz de trabajo. Inicialmente contiene A|B al final contiene a L\U
 //Wo: contiene los valores iniciales de W
 //n: numero de incognitas (orden de la matriz A)
 //p: vector de permutacion

    const char *Metodo_Matricial[7]={
   "Ingresar sistema matricial",
   "Visualizar el sistema ingresado",
   "Metodo de Gauss - Descomposici¢n LU",
   "Metodo de Gauss del Pivot M ximo",
   "Metodo de Cholesky",
   "Metodo de Gauss-Seidel",
   "Salir"}; //inicializacion del menu

 char opc=0; //definicion de variables
 clrscr();
 while(opc!=-1)
 {
  clrscr();
  CUADRO(12,6,50,15,9);
  gotoxy( 14,8 );
  textcolor(LIGHTRED);
  printf("METODOS DE SOLUCIONES DE ECUACIONES MATRICIALES");
  textcolor(LIGHTGREEN);
  gotoxy( 1,23 );printf("Utilice las flechas ARRIBA y ABAJO para desplazar el cursor sobre las opciones");
  opc=MENU(Metodo_Matricial,20,11,7,-1,15);//se crea el menu de opciones
  gotoxy(1,1);

  if( n>1 ) Inicializar_Matriz_de_Trabajo( n, W ,Wo );

  switch(opc)
  {
   case 0:
    Ingresar_Sistema( n, Wo );
    break;
   case 1:
   if( n<2 ) break;
    Visualizar_Sistema( n, W );
    break;
   case  2:
    if( n<2 ) break;
    clrscr();
    printf(Metodo_Matricial[opc]);
    LU_Gauss(n,W,p);
    Calcular_Solucion_del_Sistema_LU( n, W, x, p );
    Mostrar_Solucion_del_Sistema( n, x );
    Mostrar_Matriz_de_Permutacion( n, p );
    Mostrar_Matrices_LU( n, W, p );
    getch();
    break;
   case  3:
    if( n<2 ) break;
    clrscr();
    printf(Metodo_Matricial[opc]);
    LU_Pivot_Maximo( n, W, p );
    Calcular_Solucion_del_Sistema_LU( n, W, x, p );
    Mostrar_Solucion_del_Sistema( n, x );
    Mostrar_Matriz_de_Permutacion( n, p );
    Mostrar_Matrices_LU( n, W, p );
    getch();
    break;
   case  4:
    if( n<2 ) break;
    clrscr();
    printf(Metodo_Matricial[opc]);
    LU_Cholesky( n, W, x );
    Mostrar_Matrices_LU( n, W, p );
    getch();
    break;

   case  5:
    if( n<2 ) break;
    clrscr();
    printf(Metodo_Matricial[opc]);
    Gauss_Seidel( n, W, x);
    Mostrar_Solucion_del_Sistema( n, x );
    getch();
    break;

   case -1:
   case  6:
    clrscr();
    gotoxy(25,12);
    printf("Esta seguro que desea salir S/N: ");
    opc=toupper(getch());
    if( opc=='S') opc=-1;
    break;

   }

 }
 closegraph();
}

int MENU (const char *vec[],int x,int y,int dim,int puntero,int col)
{
 /*Esta funcion resive unvector tipo caracter
   definido de la siguiente manera
   char *nomvec[dim]={"OPC1","OPC2","OPC3"..... ,"OPCn"};
   necesita las siguientes librerias:
   #include <conio.h>
   #include <stdio.h>
   #include <bios.h>
   ejemplo de como se envia
   opc=MENU(10,10,nomvec,dim);
   puntero= opcion por defecto donde aparecera el puntero
 */
 textcolor(col);
 int con=0,con_ant=0,sal=0;
 if (dim >=1 && x>=2 && y+(dim-1)<=24)
 {
  for(int k=0;k<dim;k++)
  {
   gotoxy(x,y+k);printf("%s",vec[k]);
  }
  if(puntero!=-1 && puntero<dim){con=puntero;}

  while (sal != 1)
  {
	  gotoxy(x - 1, y + con); printf(">");

	  textcolor(col);
	  gotoxy(x, y + con_ant); printf("%s", vec[con_ant]);
	  textcolor(LIGHTGREEN);
	  gotoxy(x, y + con); printf("%s", vec[con]);
	  con_ant = con;

	  /*
	  while (bioskey(1) == 0);
	  gotoxy(x - 1, y + con); printf(" ");
	  switch (bioskey(0))
	  {
	  case 0x11b:sal = 1; con = -1; break;//ESC
	  case 0x1c0d:sal = 1; break;//ENTER
	  case 0x4800:
		  con--;
		  if (con < 0)con = (dim - 1);

		  break;//Fle. Arriba
	  case 0x5000:con++; if (con > (dim - 1))con = 0; break;//Fle. Abajo
	  }
	  if (kbhit()) getch();*/


#ifdef _WIN32

	  // This routine is very fast at detecting pressed keys.But it only works on Windows

	  if (GetKeyState(VK_ESCAPE) & 0x8000/*Check if high-order bit is set (1 << 15)*/) {
		  // Key ESCAPE
		  sal = 1;
		  con = -1;
	  }
	  else if (GetKeyState(VK_RETURN) & 0x8000/*Check if high-order bit is set (1 << 15)*/) {
		  // Key RETURN
		  sal = 1;
	  }
	  else if (GetKeyState(VK_UP) & 0x8000) {
		  // Key Up
		  con--;
		  if (con < 0)
			  con = (dim - 1);
	  }
	  else if (GetKeyState(VK_DOWN) & 0x8000) {
		  // Key Down
		  con++;
		  if (con > (dim - 1))
			  con = 0;
	  }
#else	


#endif	
  }
  return(con);
 }
 else
 {
  printf("El menu no tiene la dimension correcta o se salio de la pantalla");
  getch();
  return(con=-1);
 }
}



///
void CUADRO(int x1,int y1,int ancho,int largo,int col)
{
 /*necesita
  #include <conio.h>
  #include <stdio.h>
 */
 if(x1 >= 0 && y1>=0 && (x1+ancho)<=70 && (y1+largo)<=25)
 {
  textcolor(col);
  for(int i=x1+1;i<=x1+ancho-1;i++)
  {
   gotoxy(i,y1);printf("Í");
   gotoxy(i,y1+largo);printf("Í");
  }
  for(int k=y1+1;k<=y1+largo-1;k++)
  {
   gotoxy(x1,k);printf("º");
   gotoxy(x1+ancho,k);printf("º");
  }
  gotoxy(x1,y1);printf("É");
  gotoxy(x1,y1+largo);printf("È");
  gotoxy(x1+ancho,y1+largo);printf("¼");
  gotoxy(x1+ancho,y1);printf("»");
 }
 else
 {
  gotoxy(x1,y1);printf("Cuadro fuera de pantalla");getch();
 }
}


