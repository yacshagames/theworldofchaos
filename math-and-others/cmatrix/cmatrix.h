/***************************************************************************
 CLASE:  CMATRIZ
 ALGEBRA LINEAL (OPERACIONES ELEMENTALES ENTRE MATRICES)

programado por:
 JOSE LUIS DE LA CRUZ LAZARO
correos:
 jcruz@ec-red.com
 ramondc@hotmail.com
Pagina Web ( EL MUNDO DEL CAOS ):
 http://www.geocities.com/joseluisdl

 Versi¢n 1.4  17-Agosto-2000
 -Ya hace mas de un a¤o que no actualizaba CMatriz, antes que todo pido
  disculpas a todos los usuarios que usaron CMatriz 1.3 y no pudieron
  correr el programa en su PC debido a varios errores de compilaci¢n.
  Esta nueva versi¢n supera varios de los errores que ocurr¡a en CMatriz 1.3.
  Pero si vuelve a ocurrir alg£n error, por favor avisarme lo mas r pido
  posible.
 -Se agreg¢ una nueva funci¢n miembro: IngresarElementos() ;  que ingresa
  los elementos de la matriz desde el teclado.
 -Se reemplaz¢ todas las entradas y salidas cout<< y cin>> (de iostream.h)
  por printf y scanf ( de stdio.h ), para que no ocurran errores de
  compilaci¢n en algunos compiladores antiguos.
 -Se agregaron comentarios a las lineas de c¢digo m s importantes.

 Versi¢n 1.3   6-Junio-1999
 -Clase para matrices que trabaja con las matrices como
  si fueran simples variables.

***************************************************************************/

#ifndef __STDIO_H
#include <stdio.h>
#endif

#ifndef __MATH_H
#include <math.h>
#endif

//IMPORTANTE: Si al correr el programa, este compila sin errores pero
//al momento de ejecutarlo se cuelga el programa mostrando un error
//esto puede deberse a que no hay memoria suficiente para crear las matrices
//sugiero que cambie el valor de _MAX a un valor menor al que contiene
//actualmente
const _MAX = 6; //Maximo numero de elementos con los que se va a trabajar

class CMatriz
{
	//    protected:
private:
	//VARIABLES MIEMBRO
	int FIL;
	int COL;
	int ORDEN;

public:
	double Elemento[_MAX][_MAX]; //Contiene los elementos de la matriz
	//CONSTRUCTORES
	CMatriz(); //constuye una matriz cuadrada de orden _MAX
	CMatriz(int filas, int columnas); //constructor para matrices no cuadradas
	CMatriz(int orden); //constructor para matrices cuadradas
	~CMatriz() { }; //destructor

	//FUNCIONES
	void Inicializar(double elemento); //Copia a todos los elementos
					   //de la matriz el valor
					   //de la variable elemento

	void IngresarElementos();//Se ingresan los elementos de la matriz
				 //desde el teclado
	void Escribir(); //Escribe la matriz en pantalla

	int Fil() { return FIL; }  //retorna el numero de filas de la matriz
	int Col() { return COL; }  //retorna el numero de columnas de la matriz
	int Orden() { return ORDEN; }//retorna el orden de la matriz en caso
					//de ser una matriz cuadrada y en caso
					//contrario retorna -1

	//DEFINE LAS OPERACIONES ENTRE MATRICES
	friend CMatriz operator-(CMatriz &A); 		 //operacion -A  NEGATIVO DE UNA MATRIZ
	friend CMatriz operator+(CMatriz &A, CMatriz &B); //operaci¢n A+B SUMA DE MATRICES
	friend CMatriz operator-(CMatriz &A, CMatriz &B); //operaci¢n A-B RESTA DE MATRICES
	friend CMatriz operator*(double k, CMatriz &A);  //operaci¢n k*B (k es una constante)
	friend CMatriz operator*(CMatriz &A, CMatriz &B);//operaci¢n A*B (Producto matricial)
};

/*
//UN EJEMPLO
void main()
{

 double B[3][3]={-1,-2,3,4,5,6,7,8,9},
	C[3][3]={2,5,7,1,4,2,4,5,9};

 CMatriz M(3),N(3),P(3);//se declaran 3 matrices cuadradas de orden 3

 CMatriz I;//para crear memoria virtual

 //Se asigna los arreglos B y C a las matrices M y N respectivamente
 for(int i=0;i<M.Fil();i++)
  for(int j=0;j<M.Col();j++)
  {
   M.Elemento[i][j]=B[i][j];
   N.Elemento[i][j]=C[i][j];
  }

 clrscr();

 P=( InvGauss( (Det(M)*N+Det(N)*M) ) )*(120*N);
 I=( InvCofact( (Det(M)*N+Det(N)*M) ) )*(120*N);

 //I=Inv1( M+N );

 I.Escribir(); //Escribe la matriz en pantalla

 M.Escribir(); //Escribe la matriz en pantalla

 P.Escribir(); //Escribe la matriz en pantalla

 getch();
}
  */