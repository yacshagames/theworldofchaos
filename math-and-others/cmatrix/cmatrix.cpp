#include "cmatrix.h"

//////////////////////////////////////////////////////////////////////
//CONSTRUYE LA MATRIZ CON VALORES POR DEFECTO: FIL=COL=10;
CMatrix::CMatrix(void)
{
	FIL = COL = ORDEN = 0;//La matriz es cuadrada
}
//////////////////////////////////////////////////////////////////////
//CONSTRUYE UNA MATRIZ CUADRADA DE ORDEN "orden"
CMatrix::CMatrix(int orden)
{
	FIL = COL = ORDEN = orden;//La matriz es cuadrada

	Elemento.resize(orden, FILE(orden, 0.0));
}
//////////////////////////////////////////////////////////////////////
//CONSTRUYE UNA MATRIZ ESPECIFICANDO EL NUMERO DE FILAS Y COLUMNAS
CMatrix::CMatrix(int filas, int columnas)
{
	FIL = filas;
	COL = columnas;

	if (FIL == COL)ORDEN = FIL;//La matriz es cuadrada
	else ORDEN = -1; //para detectar cuando una matriz no es cuadrada: Orden =-1

	Elemento.resize(filas, FILE(columnas, 0.0));
}
/*
//////////////////////////////////////////////////////////////////////
//INICIALIZAR LOS ELEMENTOS DE LA MATRIZ
void CMatrix::Inicializar(double elemento)
{

	for (int i = 0; i < FIL; i++)
		for (int j = 0; j < COL; j++)
			Elemento[i][j] = elemento;

}

//////////////////////////////////////////////////////////////////////
//SE INGRESAN LOS ELEMENTOS DE LA MATRIZ, DESDE EL TECLADO, UNO POR UNO
void CMatrix::IngresarElementos()
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
void CMatrix::Escribir()
{
	printf("\n\n");
	for (int i = 0; i < FIL; i++)
	{
		for (int j = 0; j < COL; j++)
			printf("%f\t", Elemento[i][j]);
		printf("\n");
	}
}
*/
//////////////////////////////////////////////////////////////////////
//OPERADORES BINARIOS
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//NEGATIVO DE UNA MATRIZ (-A)
CMatrix operator-(CMatrix &A)
{
	CMatrix *M = new CMatrix;

	*M = A;

	for (int i = 0; i < A.Fil(); i++)
		for (int j = 0; j < A.Col(); j++)
			M->Elemento[i][j] *= -1.0;

	return *M;
}
//////////////////////////////////////////////////////////////////////
//SUMA DE MATRICES (A+B)
CMatrix operator+(CMatrix &A, CMatrix &B)
{

	//Consistencia:
	if (A.Fil() != B.Fil() || A.Col() != B.Col()) {
		printf("Las matrices no tienen la misma dimensi¢n");
		return A;
	}

	CMatrix *M = new CMatrix(A.Fil(), A.Col());
	for (int i = 0; i < A.Fil(); i++)
		for (int j = 0; j < A.Col(); j++)
			M->Elemento[i][j] = A.Elemento[i][j] + B.Elemento[i][j];
	return *M;
}
//////////////////////////////////////////////////////////////////////
//DIFERENCIA DE MATRICES (A-B)
CMatrix operator-(CMatrix &A, CMatrix &B)
{
	return (A + (-B));
}
//////////////////////////////////////////////////////////////////////
//CONSTANTE POR MATRIZ (k*A)
CMatrix operator*(double k, CMatrix &A)
{
	CMatrix *M = new CMatrix(A.Fil(), A.Col());

	for (int i = 0; i < A.Fil(); i++)
		for (int j = 0; j < A.Col(); j++)
			M->Elemento[i][j] = k * A.Elemento[i][j];
	return *M;
}
//////////////////////////////////////////////////////////////////////
//MULTIPLICACION DE MATRICES (A*B)
CMatrix operator*(CMatrix &A, CMatrix &B)
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

		CMatrix *M = new CMatrix(A.Fil(), B.Col());
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
double DetCofact(CMatrix &A, int orden)
{

	double D = 0;
	CMatrix B;
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
double Det(CMatrix &A)
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
CMatrix InvCofact(CMatrix M)
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

	CMatrix Ct(M.Orden());
	CMatrix B(M.Orden() - 1);
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
CMatrix InvGauss(CMatrix M)
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