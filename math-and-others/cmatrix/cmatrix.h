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

//////////////////////////////////////////////////////////////////////
//CONSTRUYE LA MATRIZ CON VALORES POR DEFECTO: FIL=COL=10;
CMatriz::CMatriz(void)
{
	FIL = COL = ORDEN = _MAX;//La matriz es cuadrada
	Inicializar(0);
}
//////////////////////////////////////////////////////////////////////
//CONSTRUYE UNA MATRIZ CUADRADA DE ORDEN "orden"
CMatriz::CMatriz(int orden)
{
	FIL = COL = ORDEN = orden;//La matriz es cuadrada
	Inicializar(0);
}
//////////////////////////////////////////////////////////////////////
//CONSTRUYE UNA MATRIZ ESPECIFICANDO EL NUMERO DE FILAS Y COLUMNAS
CMatriz::CMatriz(int filas, int columnas)
{
	FIL = filas;
	COL = columnas;

	if (FIL == COL)ORDEN = FIL;//La matriz es cuadrada
	else ORDEN = -1; //para detectar cuando una matriz no es cuadrada: Orden =-1

	Inicializar(0);
}
//////////////////////////////////////////////////////////////////////
//INICIALIZAR LOS ELEMENTOS DE LA MATRIZ
void CMatriz::Inicializar(double elemento)
{

	for (int i = 0; i < FIL; i++)
		for (int j = 0; j < COL; j++)
			Elemento[i][j] = elemento;

}

//////////////////////////////////////////////////////////////////////
//SE INGRESAN LOS ELEMENTOS DE LA MATRIZ, DESDE EL TECLADO, UNO POR UNO
void CMatriz::IngresarElementos()
{
	int i, j;
	float elemento;

	for (i = 0; i < FIL; i++)
		for (j = 0; j < COL; j++)
		{
			printf("Elemento ( Fil=%i, Col=%i ) = ", i, j);
			scanf("%f", &elemento); // se ingresan los elementos al arreglo Elemento, el cual es miembro de la matriz A
			Elemento[i][j] = elemento;
		}
}
//////////////////////////////////////////////////////////////////////
//ESCRIBE LA MATRIZ EN LA PANTALLA
void CMatriz::Escribir()
{
	printf("\n\n");
	for (int i = 0; i < FIL; i++)
	{
		for (int j = 0; j < COL; j++)
			printf("%f\t", Elemento[i][j]);
		printf("\n");
	}
}

//////////////////////////////////////////////////////////////////////
//OPERADORES BINARIOS
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//NEGATIVO DE UNA MATRIZ (-A)
CMatriz operator-(CMatriz &A)
{
	CMatriz *M = new CMatriz;

	*M = A;

	for (int i = 0; i < A.Fil(); i++)
		for (int j = 0; j < A.Col(); j++)
			M->Elemento[i][j] *= -1;

	return *M;
}
//////////////////////////////////////////////////////////////////////
//SUMA DE MATRICES (A+B)
CMatriz operator+(CMatriz &A, CMatriz &B)
{

	//Consistencia:
	if (A.Fil() != B.Fil() || A.Col() != B.Col()) {
		printf("Las matrices no tienen la misma dimensi¢n");
		return A;
	}

	CMatriz *M = new CMatriz(A.Fil(), A.Col());
	for (int i = 0; i < A.Fil(); i++)
		for (int j = 0; j < A.Col(); j++)
			M->Elemento[i][j] = A.Elemento[i][j] + B.Elemento[i][j];
	return *M;
}
//////////////////////////////////////////////////////////////////////
//DIFERENCIA DE MATRICES (A-B)
CMatriz operator-(CMatriz &A, CMatriz &B)
{
	return (A + (-B));
}
//////////////////////////////////////////////////////////////////////
//CONSTANTE POR MATRIZ (k*A)
CMatriz operator*(double k, CMatriz &A)
{
	CMatriz *M = new CMatriz(A.Fil(), A.Col());

	for (int i = 0; i < A.Fil(); i++)
		for (int j = 0; j < A.Col(); j++)
			M->Elemento[i][j] = k * A.Elemento[i][j];
	return *M;
}
//////////////////////////////////////////////////////////////////////
//MULTIPLICACION DE MATRICES (A*B)
CMatriz operator*(CMatriz &A, CMatriz &B)
{
	//Consistencia:  A.Col()==B.Fil()
	if (A.Col() != B.Fil())
	{
		printf("\nNo se puede multiplicar las matrices");
		return A;
	}
	else
	{
		int i, j, k, n = A.Col();

		CMatriz *M = new CMatriz(A.Fil(), B.Col());
		for (i = 0; i < M->Fil(); i++)
			for (j = 0; j < M->Col(); j++)
			{
				double S = 0.0;
				for (k = 0; k < n; k++)
					S += A.Elemento[i][k] * B.Elemento[k][j];
				M->Elemento[i][j] = S;
			}

		return *M;
	}

}


//********************************************************************
//CALCULO DE LA DETERMINANTE DE UNA MATRIZ
//********************************************************************

//////////////////////////////////////////////////////////////////////
//RECURSIVA PARA CALCULAR LA DETERMINANTE DE LA MATRIZ A
//POR EL METODO DE COFACTORES
//!!!Nesecita que se le ingrese el orden de la matriz
//////////////////////////////////////////////////////////////////////
double DetCofact(CMatriz &A, int orden)
{

	double D = 0;
	CMatriz B;
	int x, i, j;

	if (orden >= 2)
	{

		for (x = 0; x < orden; x++)
		{

			for (i = 0; i < orden - 1; i++)
				for (j = 1; j < orden; j++)
				{
					if (i < x) B.Elemento[i][j - 1] = A.Elemento[i][j];
					else  B.Elemento[i][j - 1] = A.Elemento[i + 1][j];
				}

			D += pow(-1, x) * A.Elemento[x][0] * DetCofact(B, orden - 1);
		}

		return D;

	}
	else return A.Elemento[0][0];

}

//////////////////////////////////////////////////////////////////////
//CALCULA LA DETERMINANTE DE A INVOCANDO A LA FUNCION DetCofact
//!!!No nesecita que se le ingrese el orden de la matriz
//////////////////////////////////////////////////////////////////////
double Det(CMatriz &A)
{
	//Consistencia:
	if (A.Orden() == -1) {
		printf("La matriz no es cuadrada");
		return 0;
	}

	return DetCofact(A, A.Orden());

}

//********************************************************************
//CALCULO DE LA INVERSA DE UNA MATRIZ
//********************************************************************


//////////////////////////////////////////////////////////////////////
//CALCULA LA INVERSA DE LA MATRIZ POR EL METODO DE LA TRANSPUESTA DE
//DE LA MATRIZ DE COFACTORES:
//METODO: A^-1 = (1/|A|) * (C)^t
//donde C = matiz cofactor de A
//////////////////////////////////////////////////////////////////////
CMatriz InvCofact(CMatriz M)
{

	//Consistencia:
	if (M.Orden() == -1) {
		printf("La matriz no es cuadrada");
		return M;
	}
	//Consistencia: Determinante!=0 para que Exista Inversa
	double DET = Det(M);
	if (DET == 0) {
		printf("La Matriz no es inversible, su determinante es 0");
		return M;
	}

	int i, j, x, y;

	CMatriz Ct(M.Orden());
	CMatriz B(M.Orden() - 1);
	//se crea la submatriz B de orden n-1
	//pivoteando en x,y

	for (x = 0; x < M.Orden(); x++)
		for (y = 0; y < M.Orden(); y++)
		{
			for (i = 0; i < M.Orden() - 1; i++)
				for (j = 0; j < M.Orden() - 1; j++)
				{
					if (i < x && j < y) B.Elemento[i][j] = M.Elemento[i][j];
					else if (i < x && j >= y) B.Elemento[i][j] = M.Elemento[i][j + 1];
					else if (i >= x && j < y) B.Elemento[i][j] = M.Elemento[i + 1][j];
					else if (i >= x && j >= y) B.Elemento[i][j] = M.Elemento[i + 1][j + 1];
				}

			//Se halla la transpuesta de la matriz de cofactores
			Ct.Elemento[y][x] = pow(-1, x + y) * Det(B);

		}

	return pow(DET, -1)*Ct;
}


//////////////////////////////////////////////////////////////////////
//CALCULA LA INVERSA DE LA MATRIZ POR EL METODO DE REDUCCION GAUSSIANA
// A^-1 = { A^-1 ; tal que  G = [ A | I ] = [ I | A^-1 ]  }
//////////////////////////////////////////////////////////////////////
CMatriz InvGauss(CMatriz M)
{

	int m = M.Orden();

	//Consistencia:
	if (m == -1) {
		printf("La matriz no es cuadrada");
		return M;
	}

	double G[_MAX][2 * _MAX];//Arreglo Gaussiano

	int i, j, k, s, t;
	double T, tmp, DET = 1;

	//Se Asigna el contenido de la Matriz M al arreglo Gaussiano G
	for (i = 0; i < m; i++)
		for (j = 0; j < m; j++)
			G[i][j] = M.Elemento[i][j];

	//Se anexa a esta matriz una matriz identidad de orden m para aplicar
	//Reduccion Gaussiana
	for (i = 0; i <= m - 1; i++)
		for (j = m; j <= 2 * m - 1; j++) {
			if (i + m == j)G[i][j] = 1; else G[i][j] = 0;
		}

	//Se reduce la matriz por operaciones elementales comenzando por G[0][0]
	//a una matriz triangular superior
	for (k = 0; k < m; k++)
		for (i = k; i < m; i++) {
			T = G[i][k];
			for (s = i; s < m - 1 && T == 0; s++)
				for (t = 0; t < 2 * m; t++) {
					tmp = G[s][t];
					G[s][t] = G[s + 1][t];
					G[s + 1][t] = tmp;
				}

			DET *= T;
			if (T == 0)continue;

			for (j = 2 * m - 1; j >= 0; j--) {	//Se disminuye el valor de j para que el valor de G[i][0] solo sea alterado al final
				if (i == k)G[i][j] /= T; //se divide a la primera fila por el primer termino de la fila
				else G[i][j] = G[i][j] / T - G[k][j]; //(A partir de la segunda fila) se divide la fila i por el primer termino de la fila i
			}
		}

	//Consistencia
	if (DET == 0)
	{
		printf("La Matriz no es inversible, su determinante es 0");
		return M;
	}

	//Se reduce la matriz triangular superior de la izquierda de G
	//a una matriz identidad
	for (k = 0; k < m; k++)
		for (t = k + 1; t < m; t++) {
			T = G[k][t];
			for (j = 0; j < 2 * m; j++)
				G[k][j] -= T * G[t][j];
		}

	//Por lo tanto en la parte derecha de G queda la matriz Inversa
	//que es asignada de vuelta a M para ser retornada
	for (i = 0; i < m; i++)
		for (j = 0; j < m; j++)
			M.Elemento[i][j] = G[i][j + m];

	return M;

}
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