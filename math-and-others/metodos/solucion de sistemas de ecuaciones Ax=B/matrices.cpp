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

  >> Version 2 - 02-IV-2024
	- Code is updated and improved
	- Comments are translated from Spanish to English
	- std::vector is used instead of arrays, and in this way the
	  limitation that did not allow solving systems of equations with
	  more than 10 unknown variables is eliminated.
	- Improvements in the coding of the Gauss Seidel and Cholesky
	  algorithms.
	- Finished replacing all arrays with std:vector
	- An alert message is added informing when the Cholesky method
	  cannot be applied
	- The code is modernized, converting it into the
	  CMatrixSolvingLinearEq class
	- Traces of old C functions, such as printf, cprintf, fabs, etc...
	  are removed and replaced with their modern equivalents
	- Some missing comments and the names of the CMatrixSolvingLinearEq
	  methods are translated into English.
	- Unnecessary files are removed
	- The option is added to generate the elements of matrices A and B	  
	  randomly, only defining the order of the matrix and indicating
	  whether it will be diagonally dominant. If you create a diagonally
	  dominant matrix, it can be successfully processed.
	- Modifications are added to the History version
	- The roots are shown in the Gauss-Seidel method as long as this
	  method converges.

  >> Version 1 - 30-XI-1999
	- First version for Borland C++ 3.1 and Turbo C 3.0

**********************************************************************/
#include <iostream> //cout cin
#include "conio.h" //clrscr() cgetch() gotoxy() textcolor()
#include <string>
#include <vector>
#ifdef max
#undef max
#endif
#include <algorithm>
#include <random>
#include <functional> // bind

using namespace std;


class CMatrixSolvingLinearEq {
public:
	CMatrixSolvingLinearEq();
	~CMatrixSolvingLinearEq();

	void LU_Gauss();	
	void LU_Pivot_Maximum();
	bool LU_Cholesky();
	bool Gauss_Seidel();

	void Calculate_LU_System_Solution();
	void Show_System_Solution();	
	void Show_Permutation_Matrix();	
	void Show_LU_Matrices();	
	bool SetNumberUnknownsVariables();
	void Enter_System();
	void Visualize_System();
	bool Initialize_Work_Matrix();
	void GenerateRandomMatrices(bool isDiagonallyDominant);


	int MENU(std::vector<std::string>& vec, int x, int y, int col);

	// Print a picture in console text mode
	void FRAME(int x1, int y1, int ancho, int largo, int col);

private:

	//x: contains the solution of the system Ax=B
	//W: Work matrix. Initially contains A|B at the end contains L\U
	//Wo: contains the initial values of W
	//n: number of unknowns (order of matrix A)
	//p: permutation vector
	int n;
	std::vector<double> x;
	std::vector<std::vector<double>> W, Wo;
	std::vector<int> p;

public:
	static std::string msgMatrixNotInvertible;
};

std::string CMatrixSolvingLinearEq::msgMatrixNotInvertible = "The matrix is not invertible";

CMatrixSolvingLinearEq::CMatrixSolvingLinearEq()
{
	// Init matrix dimension at empty matrix
	n = 0;
}

CMatrixSolvingLinearEq::~CMatrixSolvingLinearEq()
{
}

//////////////////////////////////////////////////////////////////////
// LU ALGORITHM BY GAUSSIAN DECOMPOSITION
//////////////////////////////////////////////////////////////////////
void CMatrixSolvingLinearEq::LU_Gauss()
{

	int i, j, k;

	// p is initialized
	for (i = 0; i < n; i++)
		p[i] = i;

	double m; //multiplier
	int tmp;

	// Calculation of the matrix W
	for (k = 0; k < n - 1; k++)
	{
		// find (the smallest) j>=k such that W[p[j]][k]!=0
		for (j = k; j < n; j++)
			if (W[p[j]][k] != 0)
			{// the contents of p[k] and p[j] are exchanged
				tmp = p[k];
				p[k] = p[j];
				p[j] = tmp;
				break; // the searched j was found
			}

		if (j == n)// the searched j was not found
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

	// there is a zero on the diagonal
	if (W[p[n - 1]][n - 1] == 0)
	{
		cout << msgMatrixNotInvertible;
		return;
	}

}

/////////////////////////////////////////////////////////////////////
// LU DECOMPOSITION ALGORITHM USING THE MAXIMUM PIVOT STRATEGY
//////////////////////////////////////////////////////////////////////
void CMatrixSolvingLinearEq::LU_Pivot_Maximum()
{

	int i, j, k;
	double m; // multiplier
	std::vector<double> d(n);	// d[i] = maximum( |Wij| ) 0<=j<n
								// d[i] = maximum absolute value of the elements of row i of W

	for (i = 0; i < n; i++)
	{
		p[i] = i;

		// The maximum absolute values of each row are found and stored in d[i]
		for (j = 0, d[i] = 0; j < n; j++)
		{
			m = std::abs(W[i][j]);
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
		// find (the smallest) j>=k such that
		//std::abs(W[p[j]][k])/d[p[j]] >= std::abs(W[p[i]][k])/d[p[i]]
		for (j = k; j < n; j++)
		{
			for (i = k; i < n; i++)
				if (std::abs(W[p[j]][k]) / d[p[j]] < std::abs(W[p[i]][k]) / d[p[i]]) break;

			if (i == n) // the searched j was found
			{ //the contents of p[k] and p[j] are exchanged
				i = p[k];
				p[k] = p[j];
				p[j] = i;
				break;
			}
		}

		for (i = k + 1; i < n; i++)
		{
			m = W[p[i]][k] = W[p[i]][k] / W[p[k]][k]; // the multiplier of the pivot row is assigned

			for (j = k + 1; j <= n; j++)
				W[p[i]][j] -= m * W[p[k]][j];

		}
	}

	// there is a zero on the diagonal
	if (W[p[n - 1]][n - 1] == 0)
	{
		cout << msgMatrixNotInvertible;
		return;
	}
}

//////////////////////////////////////////////////////////////////////
// LU DECOMPOSITION ALGORITHM USING THE CHOLESKY METHOD
//////////////////////////////////////////////////////////////////////
bool CMatrixSolvingLinearEq::LU_Cholesky()
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

	// assign matrix L to matrix W
	for (j = 0; j < n; j++)
		for (i = j; i < n; i++)
			if (j == i)
				W[i][i] = L[i][i];
			else
				W[i][j] = W[j][i] = L[i][j];

	// substitution forward and backward
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
// GAUSS-SEIDEL ITERATION ALGORITHM
//////////////////////////////////////////////////////////////////////
bool CMatrixSolvingLinearEq::Gauss_Seidel()
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
				x_ant[k] = x[k]; // the previous vector is saved Xm-1 = Xm

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
	else {
		cout << "\nThe solution DIVERGES with " << iterations << " iterations. Divergence value: " << divergenceMax;
		return  false;
	}

	return true;

}
/*/////////////////////////////////////////////////////////////////////////////
FUNCIONES PARA MOSTRAR LAS MATRICES:  x p L U
x: column matrix with the solutions of the system Ax=B
p: permutation vector of the system
L: lower triangular matrix
U: upper triangular matrix
Note: PLU=A
where P is calculated from p
////////////////////////////////////////////////////////////////////////////*/
void CMatrixSolvingLinearEq::Calculate_LU_System_Solution()
{
	int j, k;
	// we proceed to calculate the matrix x
	double Sum; // variable that will contain the sum
	for (k = n - 1; k >= 0; k--)
	{
		for (Sum = 0, j = k + 1; j < n; j++)
			Sum += W[p[k]][j] * x[j];
		x[k] = (W[p[k]][n] - Sum) / W[p[k]][k];
	}

}

void CMatrixSolvingLinearEq::Show_System_Solution()
{
	cout << "\nSolution to the Ax=B system: \n";
	textcolor(LIGHTCYAN);
	for (int i = 0; i < n; i++)
		cout << "x[" << i + 1 << "] = " << x[i] << endl;
}


void CMatrixSolvingLinearEq::Show_Permutation_Matrix()
{
	cout << "\n\n";
	textcolor(BROWN);
	cout << "Permutation matrix p:" << endl;
	cout<<"p = [ ";
	for (int i = 0; i < n; i++)
		cout<< p[i] + 1 << " ";
	cout<<"]";
}

void CMatrixSolvingLinearEq::Show_LU_Matrices()
{
	int i, j;
	cout << "\n\n";
	textcolor(LIGHTMAGENTA);
	cout << "Matrix L:" << endl;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (j == i)
				cout << "1\t";
			else
				if (j > i)
					cout << "0\t";
				else
					cout << W[p[i]][j] << "\t";
		}
		cout << "\n";
	}

	cout << "\n\n";
	textcolor(WHITE);
	cout << "Matrix U:" << endl;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (j < i) 
				cout << "0";
			else 
				cout << W[p[i]][j];
			gotoxy(wherex() + 9, wherey());
		}
		cout << "\n";
	}

}


bool CMatrixSolvingLinearEq::SetNumberUnknownsVariables()
{
	int _n;
	clrscr();
	cout << "\n\nEnter the system Ax=B :\n\n"
		<< "Enter the number of unknowns variables: ";
	cin >> _n; // order of the matrix of matrix A is entered

	// Resize all matrix
	if (_n > 1) {
		this->n = _n;
		x.resize(n, 0.0);
		p.resize(n, 0);
		W.resize(n, std::vector<double>(n + 1, 0.0));
		Wo.resize(n, std::vector<double>(n + 1, 0.0));
	}
	else {		
		cout << "Error: Enter a value greater than 1!!";
		cgetch();
		return false;
	}

	return true;
}

void CMatrixSolvingLinearEq::Enter_System()
{
	int i, j;

	cout << "\nEnter the elements of matrix A:\n";
	textcolor(YELLOW);
	for (i = 0; i < n; i++)	// enter the elements of matrix A
	{
		for (j = 0; j < n; j++)
		{
			cout << "A[" << i << "," << j << "] = ";
			cin >> Wo[i][j];
		}
		cout << "\n";
	}

	cout << "\nEnter the elements of matrix B:\n";
	textcolor(LIGHTGREEN);
	for (i = 0; i < n; i++)	// enter the elements of matrix B
	{
		cout << "B[" << i << "] = ";
		cin >> Wo[i][n];
	}
}
void CMatrixSolvingLinearEq::Visualize_System()
{
	//  textcolor(LIGHTGRAY);
	int i, j;
	clrscr();

	cout << "\n\nSystem Ax=B Entered: \n";

	textcolor(YELLOW);
	cout<<"Matrix A";

	gotoxy(9 * n, wherey());
	textcolor(LIGHTGREEN);
	cout << "Matrix B" << endl;

	for (i = 0; i < n; i++)	{

		// Show Matriz A
		textcolor(YELLOW);
		for (j = 0; j < n; j++)
			cout << W[i][j] << '\t';

		// Show Matriz B
		textcolor(LIGHTGREEN);
		cout << W[i][n] << endl;
	}
	cgetch();
}

bool CMatrixSolvingLinearEq::Initialize_Work_Matrix()
{	
	if (n > 1) {
		// Init matrix W from matrix Wo
		W = Wo;
		return true;
	}

	return false;
}

void CMatrixSolvingLinearEq::GenerateRandomMatrices( bool isDiagonallyDominant )
{
	// Random device
	std::random_device rd;

	// Distribution values between -1 and 1
	std::uniform_real_distribution<double> distribution(-1.0, 1.0);

	if (isDiagonallyDominant) {

		// A diagonally dominant matrix is created with random elements in the pre-specified
		// range. So that it can be successfully processed by the Cholesky and Gauss-Seidel algorithms

		double matrixDimension = double(n);
		
		// Distribution values between matrixDimension*1.2 and matrixDimension*1.5
		std::uniform_real_distribution<double> distributionDiagonal(matrixDimension*1.2, matrixDimension*1.5); 

		std::mt19937 engine(rd()); // Mersenne twister MT19937

		int i, j;
		for (i = 0; i < n; i++)
			for (j = 0; j <= n; j++)
				Wo[i][j] = i == j ? 
				distributionDiagonal(engine) :	// Random values between -1 and 1
				distribution(engine);			// Random values between matrixDimension*1.2 and matrixDimension*1.5
	} else {

		for (auto& element : Wo) {

			std::mt19937 engine(rd()); // Mersenne twister MT19937
			auto generator = std::bind(distribution, engine);

			std::generate_n(element.begin(), element.size(), generator);
		}
	}

}

int main()
{
	CMatrixSolvingLinearEq msle;

	std::vector<std::string> Metodo_Matricial = {
	"Enter matrix system",
	"Generate random matrices",
    "View the entered matrix system",
	"Gauss method - LU decomposition",
	"Gauss Method - Maximum Pivot",
	"Cholesky method",
	"Gauss-Seidel method",
	"Exit" }; //menu initialization

	// Init constans project
	char opc = 0; 
	clrscr();
	while (opc != -1)
	{	
		clrscr();
		msle.FRAME(12, 6, 57, 16, 9);
		gotoxy(14, 8);
		textcolor(LIGHTRED);
		cout << "MATRIX METHODS FOR SOLVING SYSTEMS OF LINEAR EQUATIONS";
		textcolor(LIGHTGREEN);
		gotoxy(42, 23); 
		cout << "Developed by Yacsha Software";
		opc = msle.MENU(Metodo_Matricial, 20, 11, 15); // create the options menu
		gotoxy(1, 1);
		
		
		// Init matrix W from Wo
		if( msle.Initialize_Work_Matrix()==false )						
			if (opc != 0 && opc != 1 && opc != 7)
				continue;	// Does not execute numeric methods
			

		switch (opc)
		{
		case 0:
			
			if (msle.SetNumberUnknownsVariables()) 			
				msle.Enter_System();				

			break;
		case 1:
			if (msle.SetNumberUnknownsVariables()) {

				textcolor(LIGHTGRAY);
				cout << "\nIf you create a diagonally dominant matrix, it can be successfully processed" << endl;
				cout << "by the Cholesky and Gauss-Seidel algorithms." << endl << endl;

				textcolor(WHITE);
				cout << "Generate diagonally dominant matrix (Y/N)? ";
				char subOption = toupper(cgetch());
				
				msle.GenerateRandomMatrices(subOption == 'Y');
			}

			break;
		case 2:	

			msle.Visualize_System();

			break;
		case  3:
			
			clrscr();
			cout << Metodo_Matricial[opc];
			msle.LU_Gauss();
			msle.Calculate_LU_System_Solution();
			msle.Show_System_Solution();
			msle.Show_Permutation_Matrix();
			msle.Show_LU_Matrices();
			cgetch();
			
			break;
		case  4:
			
			clrscr();
			cout << Metodo_Matricial[opc];
			msle.LU_Pivot_Maximum();
			msle.Calculate_LU_System_Solution();
			msle.Show_System_Solution();
			msle.Show_Permutation_Matrix();
			msle.Show_LU_Matrices();
			cgetch();
			
			break;
		case  5:
			
			clrscr();
			cout << Metodo_Matricial[opc];
			if(msle.LU_Cholesky() )
				msle.Show_LU_Matrices();
			cgetch();

			break;
		case  6:

			clrscr();
			cout << Metodo_Matricial[opc];
			if( msle.Gauss_Seidel() )
				msle.Show_System_Solution();
			cgetch();

			break;
		case -1:
		case  7:

			clrscr();
			gotoxy(25, 12);
			cout << "Are you sure you want to leave Y/N?: ";
			opc = toupper(cgetch());
			if (opc == 'Y')
				opc = -1;
			
			break;
		}
	}
	
	return 1;
}



int CMatrixSolvingLinearEq::MENU(std::vector<std::string>& vec, int x, int y, int col)
{
	textcolor(col);
	int k, con, dim = vec.size();
	for (k = 0; k < dim; k++) {
		gotoxy(x, y + k);
		cout << k + 1 << ") " << vec[k];
	}
	gotoxy(x, y + k + 1);
	cout << "Enter a option: ";
	cin >> con;

	return con - 1;
}


// Print a picture in console text mode
void CMatrixSolvingLinearEq::FRAME(int x1, int y1, int ancho, int largo, int col)
{

	if (x1 >= 0 && y1 >= 0 && (x1 + ancho) <= 70 && (y1 + largo) <= 25)
	{
		textcolor(col);
		for (int i = x1 + 1; i <= x1 + ancho - 1; i++)
		{
			gotoxy(i, y1); cout << "Í";
			gotoxy(i, y1 + largo); cout << "Í";
		}
		for (int k = y1 + 1; k <= y1 + largo - 1; k++)
		{
			gotoxy(x1, k); cout << "º";
			gotoxy(x1 + ancho, k); cout << "º";
		}
		gotoxy(x1, y1); cout << "É";
		gotoxy(x1, y1 + largo); cout << "È";
		gotoxy(x1 + ancho, y1 + largo); cout << "¼";
		gotoxy(x1 + ancho, y1); cout << "»";
	}
	else
	{
		gotoxy(x1, y1); cout << "Box off screen";
		cgetch();
	}
}