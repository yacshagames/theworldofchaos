/*********************************************************************
MATRIX NUMERICAL METHODS FOR SOLVING SYSTEMS OF LINEAR EQUATIONS

A system of equations is solved using the following algorithms in 
numerical methods:
	- Gauss method - LU decomposition
	- Gauss Method - Maximum Pivot
	- Cholesky method
	- Gauss-Seidel method

Developed by:

	JOSE LUIS DE LA CRUZ LAZARO
	ramondc@hotmail.com

	UNIVERSIDAD NACIONAL DE INGENIERIA
	Faculty of Electrical and Electronic Engineering
	Lima-Peru

	YACSHA - Software & Desing
	>> The World of chaos - EL MUNDO DEL CAOS - Unlimited Programming

HISTORY...

  >> Version 2 - 01-IV-2024
	- Code is updated and improved
	- Comments are translated from Spanish to English

  >> Version 1 - 30-XI-1999
	- First version for Borland C++ 3.1 and Turbo C 3.0

**********************************************************************/
#include <iostream> //cout cin
#include "conio.h" //clrscr() getch() gotoxy() getchar() cprintf() textcolor()
#include <string>
#include <vector>
#ifdef max
#undef max
#endif

#include <algorithm>


using namespace std;

std::string msgMatrixNotInvertible = "The matrix is not invertible";

int MENU(std::vector<std::string>& vec, int x, int y, int dim, int puntero, int col);

// Print a picture in console text mode
void CUADRO(int x1, int y1, int ancho, int largo, int col);

void Imprimir_Raiz(int iteracion, double raiz)
{
	cout << "\nIteration " << iteracion << "\tRoot = " << raiz;
}

//////////////////////////////////////////////////////////////////////
//ALGORITMO LU POR DESCOMPOSICION GAUSSIANA
//////////////////////////////////////////////////////////////////////
void LU_Gauss(int n, std::vector<std::vector<double>>& W, std::vector<int>& p)
{

	int i, j, k;

	// se inicializa p
	for (i = 0; i < n; i++)
		p[i] = i;

	double m; //multiplicador
	int tmp;

	//Calculo de la matriz W
	for (k = 0; k < n - 1; k++)
	{
		//se halla (el menor) j>=k tal que W[p[j]][k]!=0
		for (j = k; j < n; j++)
			if (W[p[j]][k] != 0)
			{//se intercambia los contenidos de p[k] y p[j]
				tmp = p[k];
				p[k] = p[j];
				p[j] = tmp;
				break; //se encontro el j buscado
			}

		if (j == n)//no se encontro el j buscado
		{
			cout << msgMatrixNotInvertible;
			return;
		}

		for (i = k + 1; i < n; i++)
		{
			m = W[p[i]][k] = W[p[i]][k] / W[p[k]][k];

			for (j = k + 1; j <= n; j++)
				W[p[i]][j] -= m * W[p[k]][j];

		}
	}

	//existe un cero en la diagonal
	if (W[p[n - 1]][n - 1] == 0)
	{
		cout << msgMatrixNotInvertible;
		return;
	}

}

/////////////////////////////////////////////////////////////////////
//ALGORITMO DE DESCOMPOSICION LU UTILIZANDO LA ESTRATRATEGIA DEL
//PIVOTE MAXIMO
//////////////////////////////////////////////////////////////////////
void LU_Pivot_Maximo(int n, std::vector<std::vector<double>>& W, std::vector<int>& p)
{

	int i, j, k;
	double m; //multiplicador
	std::vector<double> d(n);	// d[i]= maximo( |Wij| ) 0<=j<n
								// d[i] = maximo valor absoluto de los elementos de la fila i de W

	for (i = 0; i < n; i++)
	{
		p[i] = i;

		//Se halla los maximos valores absolutos de cada fila y se los guarda en d[i]
		for (j = 0, d[i] = 0; j < n; j++)
		{
			m = fabs(W[i][j]);
			if (m > d[i]) d[i] = m;
		}

		if (d[i] == 0)
		{
			cout << msgMatrixNotInvertible;
			return;
		}

	}

	//Calculo de la matriz W
	for (k = 0; k < n - 1; k++)
	{
		//se halla (el menor) j>=k tal que
		//fabs(W[p[j]][k])/d[p[j]] >= fabs(W[p[i]][k])/d[p[i]]
		for (j = k; j < n; j++)
		{
			for (i = k; i < n; i++)
				if (fabs(W[p[j]][k]) / d[p[j]] < fabs(W[p[i]][k]) / d[p[i]]) break;

			if (i == n) // se encontro el j buscado
			{//se intercambia los contenidos de p[k] y p[j]
				i = p[k];
				p[k] = p[j];
				p[j] = i;
				break;
			}
		}

		for (i = k + 1; i < n; i++)
		{
			m = W[p[i]][k] = W[p[i]][k] / W[p[k]][k]; // se asigna el multiplicador de la fila pivote

			for (j = k + 1; j <= n; j++)
				W[p[i]][j] -= m * W[p[k]][j];

		}
	}

	//existe un cero en la diagonal
	if (W[p[n - 1]][n - 1] == 0)
	{
		cout << msgMatrixNotInvertible;
		return;
	}
}

//////////////////////////////////////////////////////////////////////
//ALGORITMO DE DESCOMPOSICION LU UTILIZANDO EL METODO DE CHOLESKY
//////////////////////////////////////////////////////////////////////
bool LU_Cholesky(int n, std::vector<std::vector<double>>& W, std::vector<double>& x)
{
	std::vector<std::vector<double>> L(n, std::vector<double>(n));
	double Sum, diagonalElement;
	int i, j, k;

	for (j = 0; j < n; j++){

		for (Sum = 0.0, k = 0; k < j; k++)
			Sum += pow(L[j][k], 2);

		diagonalElement = W[j][j] - Sum;

		if (diagonalElement < 0) {
			cout << endl << "Cholesky factorization cannot be applied on the diagonal ["
				<< j << "," << j << "]." << endl
				<< "Possibly matrix A is not diagonally dominant.";			
			return false;
		}

		L[j][j] = sqrt(diagonalElement);

		for (i = j + 1; i < n; i++){

			for (Sum = 0.0, k = 0; k < j; k++)
				Sum += L[i][k] * L[j][k];

			L[i][j] = (W[i][j] - Sum) / L[j][j];
		}
	}

	//  se asigna la matriz L a la matriz W
	for (j = 0; j < n; j++)
		for (i = j; i < n; i++)
			if (j == i)
				W[i][i] = L[i][i];
			else
				W[i][j] = W[j][i] = L[i][j];

	//sustitucion hacia adelante y hacia atras
	std::vector<double> b(n);
	for (k = 0; k < n; k++)
	{
		Sum = 0.0;

		for (j = 0; j < k; j++)
			Sum += W[k][j] * b[j];

		b[k] = W[k][n] - Sum;
	}

	for (k = n - 1; k >= 0; k--)
	{
		Sum = 0.0;

		for (j = k + 1; j < n; j++)
			Sum += W[k][j] * x[j];

		x[k] = (b[k] - Sum) / W[k][k];
	}

	return true;

}

//////////////////////////////////////////////////////////////////////
//ALGORITMO DE ITERACION DE GAUSS-SEIDEL
//////////////////////////////////////////////////////////////////////
void Gauss_Seidel(int n, std::vector<std::vector<double>>& W, std::vector<double>& x)
{
	std::vector<std::vector<double>> B(n, std::vector<double>(n));
	std::vector<double> C(n), x_ant(n);

	int i, j, k;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			B[i][j] = i == j ? 0 : -W[i][j] / W[i][i];

		C[i] = W[i][n] / W[i][i];
		x[i] = 0;
	}

	double Sum, error = 1e-6, deltaMax, divergenceMax = 1e10;
	unsigned int iterations = 0;
	do {
		for (i = 0; i < n; i++)
		{
			for (k = 0; k < n; k++)
				x_ant[k] = x[k]; //guardo el vector anterior Xm-1=Xm

			Sum = 0.0;

			for (j = 0; j < i; j++)
				Sum += B[i][j] * x[j];
			for (j = i + 1; j < n; j++)
				Sum += B[i][j] * x_ant[j];

			x[i] = Sum + C[i];

			deltaMax = 0.0;

			for (k = 0; k < n; k++)
				deltaMax = std::max(std::abs(x_ant[k] - x[k]), deltaMax);

		}

		iterations++;
	} while (deltaMax > error && deltaMax < divergenceMax);

	if( (deltaMax > error)==false )
		cout << "\nThe solution CONVERGES with " << iterations << " iterations";
	else
		cout << "\nThe solution DIVERGES with " << iterations << " iterations. Divergence value: " << divergenceMax;

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
void Calcular_Solucion_del_Sistema_LU(int n, std::vector<std::vector<double>>& W, std::vector<double>& x, std::vector<int>& p)
{
	int j, k;
	//se procede a calcular la matriz x
	double Sum;  //variable que contendra la sumatoria
	for (k = n - 1; k >= 0; k--)
	{
		for (Sum = 0, j = k + 1; j < n; j++)
			Sum += W[p[k]][j] * x[j];
		x[k] = (W[p[k]][n] - Sum) / W[p[k]][k];
	}

}

void Mostrar_Solucion_del_Sistema(int n, std::vector<double>& x)
{
	cout << "\nSolution to the Ax=B system: \n";
	textcolor(LIGHTCYAN);
	for (int i = 0; i < n; i++)
	{
		printf("x[%i] = %g", i + 1, x[i]);
		cout << "\n";
	}
}


void Mostrar_Matriz_de_Permutacion(int n, std::vector<int>& p)
{
	cout << "\n\n";
	textcolor(BROWN);
	printf("Permutation matrix p:");
	cout << "\n";
	printf("p = [ ");
	for (int i = 0; i < n; i++)
		printf("%i ", p[i] + 1);
	printf("]");
}

void Mostrar_Matrices_LU(int n, std::vector<std::vector<double>>& W, std::vector<int>& p)
{
	int i, j;
	cout << "\n\n";
	textcolor(LIGHTMAGENTA);
	printf("Matrix L:");
	cout << "\n";

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (j == i)cout << "1\t";
			else
				if (j > i)cout << "0\t";
				else
					cout << W[p[i]][j] << "\t";
		}
		cout << "\n";
	}

	cout << "\n\n";
	textcolor(WHITE);
	printf("Matrix U:");
	cout << "\n";
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (j < i) cout << "0";
			else cout << W[p[i]][j];
			gotoxy(wherex() + 9, wherey());
		}
		cout << "\n";
	}

}


void SetNumberUnknownsVariables(int &n)
{
	clrscr();
	cout << "\n\nEnter the system Ax=B :\n\n"
		<< "Enter the number of unknowns variables: ";
	cin >> n;//se ingresa orden de la matriz de la matriz A	
}

void Ingresar_Sistema(int &n, std::vector<std::vector<double>>& W)
{
	int i, j;

	cout << "\nEnter the elements of matrix A:\n";
	textcolor(YELLOW);
	for (i = 0; i < n; i++)	//se ingresa los elementos de la matriz A
	{
		for (j = 0; j < n; j++)
		{
			printf("A[%i,%i] = ", i, j);
			cin >> W[i][j];
		}
		cout << "\n";
	}

	cout << "\nEnter the elements of matrix B:\n";
	textcolor(LIGHTGREEN);
	for (i = 0; i < n; i++)	//se ingresa los elementos de la matriz B
	{
		printf("B[%i] = ", i);
		cin >> W[i][n];
	}
}
void Visualizar_Sistema(int &n, std::vector<std::vector<double>>& W)
{
	//  textcolor(LIGHTGRAY);
	int i, j;
	clrscr();

	cout << "\n\nSystem Ax=B Entered: \n";

	textcolor(YELLOW);
	printf("Matrix A");

	gotoxy(9 * n, wherey());
	textcolor(LIGHTGREEN);
	printf("Matrix B");

	cout << "\n";
	for (i = 0; i < n; i++)
	{
		//Imprime Matriz A
		textcolor(YELLOW);
		for (j = 0; j < n; j++)
		{
			printf("%g", W[i][j]);
			cout << "\t";
		}

		//Imprime Matriz B
		textcolor(LIGHTGREEN);
		printf("%g", W[i][n]);

		cout << "\n";
	}
	cgetch();
}

void Inicializar_Matriz_de_Trabajo(int &n, std::vector<std::vector<double>>& W, std::vector<std::vector<double>>& Wo)
{
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j <= n; j++)
			W[i][j] = Wo[i][j];
}

int main()
{
	// Init console window with WinBGI active in console mode
	//initwindow(0, 0);
	//SetForegroundWindow(GetConsoleWindow());

	std::vector<double> x;
	std::vector<std::vector<double>> W, Wo;
	std::vector<int> p;
	int n = -1;
	//x: contiene la solucion del sistema Ax=B
	//W: Matriz de trabajo. Inicialmente contiene A|B al final contiene a L\U
	//Wo: contiene los valores iniciales de W
	//n: numero de incognitas (orden de la matriz A)
	//p: vector de permutacion

	std::vector<std::string> Metodo_Matricial = {
	"Enter matrix system",
    "View the entered matrix system",
	"Gauss method - LU decomposition",
	"Gauss Method - Maximum Pivot",
	"Cholesky method",
	"Gauss-Seidel method",
	"Exit" }; //menu initialization

	char opc = 0; //definicion de variables
	clrscr();
	while (opc != -1)
	{	
		clrscr();
		CUADRO(12, 6, 57, 15, 9);
		gotoxy(14, 8);
		textcolor(LIGHTRED);
		printf("MATRIX METHODS FOR SOLVING SYSTEMS OF LINEAR EQUATIONS");
		textcolor(LIGHTGREEN);
		gotoxy(42, 23); 
		printf("Developed by Yacsha Software");
		opc = MENU(Metodo_Matricial, 20, 11, 7, -1, 15);//se crea el menu de opciones
		gotoxy(1, 1);

		if (n > 1) Inicializar_Matriz_de_Trabajo(n, W, Wo);

		switch (opc)
		{
		case 0:
			
			SetNumberUnknownsVariables(n);

			if (n > 0){
				x.resize(n, 0.0);
				p.resize(n, 0);
				W.resize(n, std::vector<double>(n+1, 0.0));
				Wo.resize(n, std::vector<double>(n+1, 0.0));

			}
			else {
				cout << "Error: Enter a value greater than zero!!";
				cgetch();
				break;
			}



			Ingresar_Sistema(n, Wo);
			break;
		case 1:
			if (n < 2) break;
			Visualizar_Sistema(n, W);
			break;
		case  2:
			if (n < 2) break;
			clrscr();
			cout << Metodo_Matricial[opc];
			LU_Gauss(n, W, p);
			Calcular_Solucion_del_Sistema_LU(n, W, x, p);
			Mostrar_Solucion_del_Sistema(n, x);
			Mostrar_Matriz_de_Permutacion(n, p);
			Mostrar_Matrices_LU(n, W, p);
			cgetch();
			break;
		case  3:
			if (n < 2) break;
			clrscr();
			cout << Metodo_Matricial[opc];
			LU_Pivot_Maximo(n, W, p);
			Calcular_Solucion_del_Sistema_LU(n, W, x, p);
			Mostrar_Solucion_del_Sistema(n, x);
			Mostrar_Matriz_de_Permutacion(n, p);
			Mostrar_Matrices_LU(n, W, p);
			cgetch();
			break;
		case  4:
			if (n < 2) break;
			clrscr();
			cout << Metodo_Matricial[opc];
			if( LU_Cholesky(n, W, x) )
				Mostrar_Matrices_LU(n, W, p);
			cgetch();
			break;

		case  5:
			if (n < 2) break;
			clrscr();
			cout << Metodo_Matricial[opc];
			Gauss_Seidel(n, W, x);
			Mostrar_Solucion_del_Sistema(n, x);
			cgetch();
			break;

		case -1:
		case  6:
			clrscr();
			gotoxy(25, 12);
			printf("Esta seguro que desea salir S/N: ");
			opc = toupper(cgetch());
			if (opc == 'S') opc = -1;
			break;

		}
	}
	//closegraph();
	return 1;
}

int MENU(std::vector<std::string>& vec, int x, int y, int dim, int puntero, int col)
{	
	textcolor(col);
	int k, con;
	for (k = 0; k < dim; k++) {
		gotoxy(x, y + k);
		printf("%d) %s", k + 1, vec[k].c_str());
	}
	gotoxy(x, y + k+1);
	cout << "Enter a option: ";
	cin >> con;

	return con-1;
}


// Print a picture in console text mode
void CUADRO(int x1, int y1, int ancho, int largo, int col)
{
	
	if (x1 >= 0 && y1 >= 0 && (x1 + ancho) <= 70 && (y1 + largo) <= 25)
	{
		textcolor(col);
		for (int i = x1 + 1; i <= x1 + ancho - 1; i++)
		{
			gotoxy(i, y1); printf("Í");
			gotoxy(i, y1 + largo); printf("Í");
		}
		for (int k = y1 + 1; k <= y1 + largo - 1; k++)
		{
			gotoxy(x1, k); printf("º");
			gotoxy(x1 + ancho, k); printf("º");
		}
		gotoxy(x1, y1); printf("É");
		gotoxy(x1, y1 + largo); printf("È");
		gotoxy(x1 + ancho, y1 + largo); printf("¼");
		gotoxy(x1 + ancho, y1); printf("»");
	}
	else
	{
		gotoxy(x1, y1); printf("Cuadro fuera de pantalla");
		cgetch();
	}
}


