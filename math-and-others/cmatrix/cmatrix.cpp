#include "cmatrix.h"
#include <cstdlib>
#include <iostream>

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

	Elemento.resize(orden, ROW(orden, 0.0));
}

//////////////////////////////////////////////////////////////////////
//CONSTRUYE UNA MATRIZ ESPECIFICANDO EL NUMERO DE FILAS Y COLUMNAS
CMatrix::CMatrix(int filas, int columnas)
{
	FIL = filas;
	COL = columnas;

	if (FIL == COL)ORDEN = FIL;//La matriz es cuadrada
	else ORDEN = -1; //para detectar cuando una matriz no es cuadrada: Orden =-1

	Elemento.resize(filas, ROW(columnas, 0.0));
}

CMatrix::~CMatrix()
{
}

int CMatrix::Fil() const
{
	return FIL;
}
int CMatrix::Col() const
{
	return COL;
}
int CMatrix::Orden() const
{
	return ORDEN;
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
CMatrix operator -(const CMatrix &A)
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
CMatrix operator +(const CMatrix &A, const CMatrix &B)
{

	//Consistencia:
	if (A.Fil() != B.Fil() || A.Col() != B.Col()) {
		std::cout << "The arrays do not have the same dimension";
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
CMatrix operator -(const CMatrix &A, const CMatrix &B)
{
	return (A + (-B));
}
//////////////////////////////////////////////////////////////////////
//CONSTANTE POR MATRIZ (k*A)
CMatrix operator *(const double& k, const CMatrix &A)
{
	CMatrix *M = new CMatrix(A.Fil(), A.Col());

	for (int i = 0; i < A.Fil(); i++)
		for (int j = 0; j < A.Col(); j++)
			M->Elemento[i][j] = k * A.Elemento[i][j];
	return *M;
}
//////////////////////////////////////////////////////////////////////
//MULTIPLICACION DE MATRICES (A*B)
CMatrix operator *(const CMatrix &A, const CMatrix &B)
{
	//Consistencia:  A.Col()==B.Fil()
	if (A.Col() != B.Fil())
	{
		std::cout << "cannot multiply matrices";
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
double CMatrix::DetCofact(const CMatrix &A, const int& orden)const
{

	double D = 0;
	CMatrix B(orden);;
	int x, i, j;

	if (orden >= 2)
	{

		for (x = 0; x < orden; x++)
		{

			for (i = 0; i < orden - 1; i++)
				for (j = 1; j < orden; j++)
				{
					if (i < x) 
						B.Elemento[i][j - 1] = A.Elemento[i][j];
					else  
						B.Elemento[i][j - 1] = A.Elemento[i + 1][j];
				}

			D += pow(-1, x) * A.Elemento[x][0] * DetCofact(B, orden - 1);
		}

		return D;

	}
	else 
		return A.Elemento[0][0];

}


void CMatrix::escalonada(MATRIX& G, const unsigned int& orden, ELEMENT& Determinant, const int& osm) const {
	
	//osm: Orden de la SubMatriz
	const int& m = orden;
	int i, j, k, s, t, _2m =2*m;	
	
	double tmp, T;

	k = orden - osm; // k:columnas
	
	//SE HALLA LA INVERSA DE R por Gauss J.
	//Se reduce la matriz por operaciones elementales comenzando por G[0][0]
	for (i = k; i < m; i++) { // i:filas

		T = G[i][k];

		// Si T==0 se intercambia la fila i con la fila i+1,i+2... hasta que T!=0
		for (s = i; s < m - 1 && IsZero(T); s++)   // s: filas
			for (t = 0; t < _2m; t++) { // t: columnas
				tmp = G[i][t];
				G[i][t] = G[s + 1][t];
				G[s + 1][t] = tmp;
				T = G[i][k];
			}

		//T = G[i][k];
		// Consistencia
		if (IsZero(T)) // T==0
			// La Matriz no es inversible, su determinante es 0
			//return false;
			continue;

		Determinant *= T;

		for (j = _2m - 1; j >= 0; j--) {	//Se disminuye el valor de j para que el valor de A[i][0] solo sea alterado al final
			if (i == k)
				G[i][j] /= T; //se divide a la primera fila por el primer termino de la fila
			else 
				G[i][j] = G[i][j] / T - G[k][j]; //(A partir de la segunda fila) se divide la fila i por el primer termino de la fila i
		}

	}

	if (osm != 0)
		escalonada(G, orden, Determinant, osm - 1);


}//fin de la funcion escalonada


void CMatrix::inversa(MATRIX& G, const unsigned int& orden, const int& osm) const {
	//osm:orden de la submatriz
	
	const unsigned int& m = orden;
	unsigned int j, k, t, _2m = 2 * m;

	double T;

	k = orden - osm;

	for (t = k + 1; t < m; t++) {
		T = G[k][t];
		for (j = 0; j < _2m; j++)
			G[k][j] -= T * G[t][j];
	}

	if (osm != 0)
		return inversa(G, orden, osm - 1);

}//fin de la funcion inversa


bool CMatrix::IsZero(const ELEMENT &element)
{
	return std::abs(element) < 1e-10;
}

CMatrix CMatrix::Transposed() const
{
	int i, j, rows = this->Fil(), cols = this->Col();

	CMatrix T(cols, rows);
	//se intercambia valores de los elementos simetricos de la matriz
	//(definicion de matriz transpuesta)
	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++){
			T.Elemento[j][i] = this->Elemento[i][j];
		}

	return T;
}

//////////////////////////////////////////////////////////////////////
//CALCULA LA DETERMINANTE DE A INVOCANDO A LA FUNCION DetCofact
//!!!No nesecita que se le ingrese el orden de la matriz
//////////////////////////////////////////////////////////////////////
double CMatrix::DetCofact() const
{
	//Consistencia:
	if (ORDEN == -1) {
		//printf("La matriz no es cuadrada");
		return 0.0;
	}

	return DetCofact(*this, ORDEN);
}

//********************************************************************
//CALCULO DE LA INVERSA DE UNA MATRIZ
//********************************************************************

//////////////////////////////////////////////////////////////////////
//CALCULA LA INVERSA DE LA MATRIZ POR EL METODO DE LA TRANSPUESTA DE
//DE LA MATRIZ DE COFACTORES:
//METODO: A^-1 = (1/|A|) * (C)^t
//donde C = matriz cofactor de A
//////////////////////////////////////////////////////////////////////
bool CMatrix::InvCofact(CMatrix& Inverse) const
{
	//Consistencia:
	if (ORDEN == -1) {
		//printf("La matriz no es cuadrada");
		return false;
	}

	const CMatrix& M = *this;

	//Consistencia: Determinante!=0 para que Exista Inversa
	double DET = M.DetCofact();

	if (IsZero(DET)) { // DET==0
		//printf("La Matriz no es inversible, su determinante es 0");
		return false;
	}

	int i, j, x, y;

	CMatrix Ct(M.Orden());
	CMatrix B(M.Orden() - 1);
	//se crea la submatriz B de orden n-1
	//pivoteando en x,y

	for (x = 0; x < M.Orden(); x++)
		for (y = 0; y < M.Orden(); y++){

			for (i = 0; i < M.Orden() - 1; i++)
				for (j = 0; j < M.Orden() - 1; j++){

					if (i < x && j < y) 
						B.Elemento[i][j] = M.Elemento[i][j];
					else if (i < x && j >= y)
						B.Elemento[i][j] = M.Elemento[i][j + 1];
					else if (i >= x && j < y)
						B.Elemento[i][j] = M.Elemento[i + 1][j];
					else if (i >= x && j >= y)
						B.Elemento[i][j] = M.Elemento[i + 1][j + 1];
				}

			//Se halla la transpuesta de la matriz de cofactores
			Ct.Elemento[y][x] = pow(-1, x + y) * B.DetCofact();

		}

	Inverse = pow(DET, -1)*Ct;

	return true;
}


//CALCULA LA INVERSA DE LA MATRIZ POR EL METODO DE REDUCCION GAUSSIANA (Método 1)
// A^-1 = { A^-1 ; tal que  G = [ A | I ] = [ I | A^-1 ]  }
bool CMatrix::InvGaussJordan1(CMatrix& Inverse) const
{

	//Consistencia:
	if (ORDEN == -1) {
		//printf("La matriz no es cuadrada");
		return false;
	}

	const CMatrix& M = *this;

	// Arreglo Gaussiano
	MATRIX G(ORDEN, ROW(2 * ORDEN, 0.0));

	int n = M.Orden(), _2n = 2 * n, i, j, k, m;
	ELEMENT cte;

	//Se Asigna el contenido de la Matriz M al arreglo Gaussiano G
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			G[i][j] = M.Elemento[i][j];

	//Aumentando matriz identidad
	for (i = 0; i < n; i++)
	{
		for (j = n; j < _2n; j++)
		{
			if (i == j - n)
				G[i][j] = 1.0;
			else
				G[i][j] = 0.0;
		}
	}

	//Pivotear matriz aumentada
	for (j = 0; j < n; j++)
		for (i = 0; i < n; i++)
		{
			if (IsZero(G[j][j]) == false) { // G[j][j] != 0

				if (i != j) {

					cte = G[i][j] / G[j][j];
					for (k = 0; k < _2n; k++)
						G[i][k] = G[i][k] - cte * G[j][k];
				}

			}
			else {

				for (k = j + 1; k < n; k++) {

					for (m = 0; m < _2n; m++)
						G[j][m] = G[j][m] + G[k][m];

					if (IsZero(G[j][j]) == false) // G[j][j] != 0
						break;
				}

				if (IsZero(G[j][j])) // G[j][j] == 0
					// La Matriz no es inversible, su determinante es 0
					return false;

				if (i != j) {

					for (k = 0; k < _2n; k++)
						G[i][k] = G[i][k] - (G[i][j] / G[j][j])*G[j][k];
				}
			}
		}


	// El lado izquierdo de la matriz G es convertido en una matriz identidad
	for (i = 0; i < n; i++) {

		cte = G[i][i];

		for (j = 0; j < _2n; j++)
			G[i][j] = G[i][j] / cte;
	}


	//Por lo tanto en la parte derecha de G queda la matriz Inversa
	//que es asignada a R para ser retornada
	Inverse = CMatrix(n);

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			Inverse.Elemento[i][j] = G[i][j + n];

	return true;
}

//CALCULA LA INVERSA DE LA MATRIZ POR EL METODO DE REDUCCION GAUSSIANA (Método 2)
// (Este método también calcula la determinante)
// A^-1 = { A^-1 ; tal que  G = [ A | I ] = [ I | A^-1 ]  }
bool CMatrix::InvGaussJordan2(CMatrix& Inverse, ELEMENT& Determinant ) const
{
	//Consistencia:
	if (ORDEN == -1) {
		//printf("La matriz no es cuadrada");
		return false;
	}

	const CMatrix& M = *this;

	int m = M.Orden(), _2m = 2 * m;

	//Consistencia:
	if (m == -1) {
		//printf("La matriz no es cuadrada");
		return false;
	}

	//double G[_MAX][2 * _MAX];//Arreglo Gaussiano
	MATRIX G(ORDEN, ROW(2 * ORDEN, 0.0));

	int i, j, k, s, t;
	ELEMENT T, tmp;

	Determinant = 1;

	//Se Asigna el contenido de la Matriz M al arreglo Gaussiano G
	for (i = 0; i < m; i++)
		for (j = 0; j < m; j++)
			G[i][j] = M.Elemento[i][j];

	//Se anexa a esta matriz una matriz identidad de orden m para aplicar
	//Reduccion Gaussiana
	for (i = 0; i <= m - 1; i++)
		for (j = m; j <= _2m - 1; j++) {
			if (i + m == j)
				G[i][j] = 1;
			else
				G[i][j] = 0;
		}

	//Se reduce la matriz por operaciones elementales comenzando por G[0][0]
	//a una matriz triangular superior
	for (k = 0; k < m; k++) // k:columnas
		for (i = k; i < m; i++) { // i:filas

			T = G[i][k];

			// Si T==0 se intercambia la fila i con la fila i+1,i+2... hasta que T!=0
			for (s = i; s < m - 1 && IsZero(T); s++)  // s: filas
				for (t = 0; t < _2m; t++) { // t: columnas
					tmp = G[s][t];
					G[s][t] = G[s + 1][t];
					G[s + 1][t] = tmp;
					T = G[i][k];
				}
			
			// Consistencia
			if (IsZero(T)) // T==0
				// La Matriz no es inversible, su determinante es 0
				//return false;
				continue;

			Determinant *= T;

			for (j = _2m - 1; j >= 0; j--) {	//Se disminuye el valor de j para que el valor de G[i][0] solo sea alterado al final
				if (i == k)
					G[i][j] /= T; //se divide a la primera fila por el primer termino de la fila
				else
					G[i][j] = G[i][j] / T - G[k][j]; //(A partir de la segunda fila) se divide la fila i por el primer termino de la fila i
			}

			//if(IsZero(G[i][i])) // G[i][i]==0
			//	return false;
		}

	//Consistencia
	for (i = 0; i < m; i++) 
		if (IsZero(G[i][i])) {
			// Si alguno de los elementos de la diagonal es cero,
			// a Matriz no es inversible, su determinante es 0
			Determinant = 0.0;
			return false;
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
	//que es asignada a R para ser retornada
	Inverse = CMatrix(m);

	for (i = 0; i < m; i++)
		for (j = 0; j < m; j++)
			Inverse.Elemento[i][j] = G[i][j + m];

	return true;

}

//CALCULA LA INVERSA DE LA MATRIZ POR EL METODO DE REDUCCION GAUSSIANA (Método 2 recursivo)
// (Este método también calcula la determinante)
// A^-1 = { A^-1 ; tal que  G = [ A | I ] = [ I | A^-1 ]  }
bool CMatrix::InvGaussJordan3(CMatrix& Inverse, ELEMENT& Determinant) const
{
	//Consistencia:
	if (ORDEN == -1) {
		//printf("La matriz no es cuadrada");
		return false;
	}

	const CMatrix& M = *this;

	int m = M.Orden();

	//Consistencia:
	if (m == -1) {
		//printf("La matriz no es cuadrada");
		return false;
	}

	// Arreglo Gaussiano
	MATRIX G(ORDEN, ROW(2 * ORDEN, 0.0));

	int i, j;// , k, s, t;
	Determinant = 1;

	//Se Asigna el contenido de la Matriz M al arreglo Gaussiano G
	for (i = 0; i < m; i++)
		for (j = 0; j < m; j++)
			G[i][j] = M.Elemento[i][j];

	//Se anexa a esta matriz una matriz identidad de orden m para aplicar
	//Reduccion Gaussiana
	for (i = 0; i <= m - 1; i++)
		for (j = m; j <= 2 * m - 1; j++) {
			if (i + m == j)
				G[i][j] = 1;
			else
				G[i][j] = 0;
		}

	escalonada(G, m, Determinant, m);

	//Consistencia
	for (i = 0; i < m; i++)
		if (IsZero(G[i][i])) {
			// Si alguno de los elementos de la diagonal es cero,
			// a Matriz no es inversible, su determinante es 0
			Determinant = 0.0;
			return false;
		}

	inversa(G, m, m);

	//Por lo tanto en la parte derecha de G queda la matriz Inversa
	//que es asignada a R para ser retornada
	Inverse = CMatrix(m);

	for (i = 0; i < m; i++)
		for (j = 0; j < m; j++)
			Inverse.Elemento[i][j] = G[i][j + m];

	return true;

}
