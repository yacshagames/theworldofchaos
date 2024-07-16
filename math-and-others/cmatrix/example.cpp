/***************************************************************************
 :: CMATRIX DEMO :: 
-- EXAMPLE OF USING CMATRIZ -- EJEMPLO DEL USO DE CMATRIZ --

 This example shows how to use the powerful CMatriz class to work
 with matrices. And show how this class can be easily included in
 your mathematical applications.

 Spanish:
 Este ejemplo muestra como usar la poderosa clase CMatriz, para trabajar
 con matrices. Y mostrar como esta clase se puede incluir facilmente en
 sus aplicaciones matematicas.

Developed by:

	JOSE LUIS DE LA CRUZ LAZARO
	contact@theworldofchaos.com

	YACSHA - Software & Desing, since 1999, Lima-Peru
	>> The World of Chaos - EL MUNDO DEL CAOS - Unlimited Programming
	www.theworldofchaos.com

LICENSE
	This file is released under the terms of the BSD 3-Clause License.
	Read LICENSE.txt file for more information.

HISTORY...

  >> Version 2 - 28-IV-2024
	- Update math-and-others\cmatrix - Porting to VC++ 2017
	- All the tests in the example are updated to work with the CMatrix
	  version 2 library.
	- AddOns (version2) is added
	- The conio.h and Menu.h libraries are added to make the user
	  interface of the example more friendly
	- Example.cpp is adapted to the new GUI incorporated by Menu.h.
	  All examples can now be accessed in an orderly manner from an
	  options menu
	- Added the following menu options:
		* Enter matrix values
		* Generate a random matrix
		* View the entered matrix values
		* SUM, DIFFERENCE AND MULTIPLICATION OF MATRICES
		* TRANSPOSED MATRIX
		* COFACTORS: DETERMINANT OF THE MATRIX
		* COFACTORS: INVERSE MATRIX
		* GAUSS JORDAN 1: INVERSE MATRIX
		* GAUSS JORDAN 2: INVERSE AND DETERMINING MATRIX
		* GAUSS JORDAN 3(RECURSIVE): INVERSE AND DETERMINANT MATRIX
		* SOLVING SYSTEMS OF LINEAR EQUATIONS: x = A^-1*b
		* Exit
	- Version history and credits are updated.
	- All messages from the GUI console and user menu interface are
	  translated from Spanish to English
	- It is adapted to work with the CMatrix library translated into
	  English
	- The use examples are updated to version 2 of CMatrix, which includes
	  an interface with an options menu, which makes it easier to test the
	  examples; and the previous examples interface is deleted.

  >> Version 1 - 17-VIII-2000
	- First version for Borland C++ 3.1 and Turbo C 3.0
	- This example shows how to use the powerful CMatriz class to work
	  with matrices. And show how this class can be easily included in
	  your mathematical applications.
	- To process an array of 5000 elements, it takes 240, 455 and 450
	  seconds for the methods InvGaussJordan1, InvGaussJordan2 and
	  InvGaussJordan3, respectively, and each function occupies
	  approximately 600MB of RAM during the execution of the algorithm.

	  Spanish:
  >> Version 1 - 17-VIII-2000
	- Este ejemplo muestra como usar la poderosa clase CMatriz, para
	  trabajar con matrices. Y mostrar como esta clase se puede incluir
	  facilmente en sus aplicaciones matematicas.
	- Para procesar una matriz de 5000 elementos se demora 240, 455 y
	  450 segundos para los métodos  InvGaussJordan1, InvGaussJordan2 e
	  InvGaussJordan3, respectivamente y cada función ocupa aproximadamente
	  600MB de memoria RAM, durante la ejecución del algoritmo.


***************************************************************************/

#include <iostream>
#include <string>
#include <random>
#include <functional> // bind
#include "cmatrix.h" //Cabecera con funciones específicas para el ALGEBRA DE MATRICES
#include "conio.h"
#include "Menu.h"
#include "AddOns.h"

using std::cout;
using std::cin;
using std::endl;

//////////////////////////////////////////////////////////////////////
//SE INGRESAN LOS ELEMENTOS DE LA MATRIZ, DESDE EL TECLADO, UNO POR UNO
void EnterElements( CMatrix& A, string MatrixName, const unsigned int& Cols=0 )
{

	cout << "Enter array elements " << MatrixName << std::endl;

	int i, j, _Rows = A.Rows(), _Cols = Cols == 0 ? A.Cols() : Cols;

	for (i = 0; i < _Rows; i++)
		for (j = 0; j < _Cols; j++)
		{
			cout << "Element ( Rows=" << i << ", Cols=" << j << " ) = ";
			// se ingresan los elementos al arreglo Elemento, el cual es miembro de la matriz A
			cin >> A.Element[i][j];
		}
}
//////////////////////////////////////////////////////////////////////
//ESCRIBE LA MATRIZ EN LA PANTALLA
void ShowMatrix(const CMatrix& A)
{
	cout << endl << endl;

	int i, j, _Rows = A.Rows(), _Cols = A.Cols();

	for (i = 0; i < _Rows; i++){

		for (j = 0; j < _Cols; j++)
			cout << A.Element[i][j] << '\t';

		cout << endl;
	}
}

void GenerateRandomMatrices(CMatrix& A, bool isDiagonallyDominant)
{
	// Random device
	std::random_device rd;

	// Distribution values between -1 and 1
	std::uniform_int_distribution<int> distribution(-10, 10);

	if (isDiagonallyDominant) {

		if (A.Order() > 0) {

			// A diagonally dominant matrix is created with random elements in the pre-specified
			// range. So that it can be successfully processed by the Cholesky and Gauss-Seidel algorithms

			const int& n = A.Order();
			//double matrixDimension = double(n);

			// Distribution values between matrixDimension*1.2 and matrixDimension*1.5
			std::uniform_int_distribution<int> distributionDiagonal(n * 12, n * 15);

			std::mt19937 engine(rd()); // Mersenne twister MT19937

			int i, j;
			for (i = 0; i < n; i++)
				for (j = 0; j < n; j++)
					A.Element[i][j] = i == j ?
					distributionDiagonal(engine) :	// Random values between -1 and 1
					distribution(engine);			// Random values between matrixDimension*1.2 and matrixDimension*1.5
		}
	}
	else {

		for (auto& element : A.Element) {

			std::mt19937 engine(rd()); // Mersenne twister MT19937
			auto generator = std::bind(distribution, engine);

			std::generate_n(element.begin(), element.size(), generator);
		}
	}

}

int main() {

	CMatrix A;

	Menu menu;

	std::vector<std::string> Metodo_Matricial = {
	"Enter matrix values",
	"Generate a random matrix",
	"View the entered matrix values",
	"SUM, DIFFERENCE AND MULTIPLICATION OF MATRICES",
	"TRANSPOSED MATRIX",
	"COFACTORS: DETERMINANT OF THE MATRIX",
	"COFACTORS: INVERSE MATRIX",
	"GAUSS JORDAN 1: INVERSE MATRIX",
	"GAUSS JORDAN 2: INVERSE AND DETERMINING MATRIX",
	"GAUSS JORDAN 3(RECURSIVE): INVERSE AND DETERMINANT MATRIX",
	"SOLVING SYSTEMS OF LINEAR EQUATIONS: x = A^-1*b",
	"Exit" }; //menu initialization

	// Init constans project
	char opc = 0;
	clrscr();
	while (opc != -1)
	{
		clrscr();
		menu.DrawBox(12, 6, 71, 19, LIGHTGREEN);
		gotoxy(14, 8);
		textcolor(LIGHTRED);
		cout << ":: CMATRIX DEMO :: ";
		gotoxy(14, 9);
		cout << "-- ALGEBRA OF MATRIXES -- ALGEBRA DE MATRICES --";

		textcolor(LIGHTGREEN);
		gotoxy(56, 26);
		cout << "Developed by Yacsha Software";
		opc = menu.DrawOptions(Metodo_Matricial, 20, 11, 15); // create the options menu
		gotoxy(1, 1);


		// Se verifica que la matriz A esté inicializada
		if ( A.Order() <= 0 )
			if (opc != 0 && opc != 1 && opc != 11) {

				clrscr();
				gotoxy(15, 12);
				cout << "Matrix A is not initialized. You must use options (1) or (2), to initialize it";
				gotoxy(15, 13);
				cout << "Press any key to continue... ";
				cgetch();

				continue;	// Does not execute numeric methods		
			}

		switch (opc)
		{
		case 0:

			clrscr();

			cout << "\n\nEnter the order of the matrix: ";
			int orden;
			cin >> orden;
			A = CMatrix(orden); //se declara una matriz del orden especificado

			EnterElements(A, "A");

			break;
		case 1:
		{
			clrscr();
			cout << "\n\nEnter the order of the matrix: ";
			int orden;
			cin >> orden;
			A = CMatrix(orden); //se declara una matriz del orden especificado
						
			cout << endl << endl;

			textcolor(WHITE);
			cout << "Generate diagonally dominant matrix (Y/N)? ";
			char subOption = toupper(cgetch());

			GenerateRandomMatrices(A, subOption == 'Y');
		}

		break;
		case 2:
			
			clrscr();

			cout << "\n\nYou entered the following Matrix A:";

			ShowMatrix(A); //display the matrix on the screen

			cout << std::endl << "Press any key to continue...";

			cgetch();

			break;
		case  3:
		{
			clrscr();
			textcolor(LIGHTCYAN);
			cout << Metodo_Matricial[opc] << endl;

			textcolor(LIGHTGRAY);
			cout << "\n\nChecking operations between matrices (Addition, Subtraction, multiplication)";
			cout << "\n\nYou will then be asked to enter the data in a matrix B, which is";
			cout << "\noperate with A. Then you already know that the order of said array must be";
			cout << "\nsame as the order of A, but if you want to test the ease with which CMatrix,";
			cout << "\ndetect errors in the dimensions between A and B when doing operations, please enter";
			cout << "\nan order for B different from that of A";

			cout << "\n\nEnter data from matrix B (Square matrix)";
			cout << "\n\nEnter the order of the array: ";

			cin >> orden;

			//se declara una matriz del orden especificado
			CMatrix B(orden);


			textcolor(WHITE);
			cout << "Do you want to enter matrix B manually (Y/N)?";
			char subOption = toupper(cgetch());

			textcolor(LIGHTGRAY);

			cout << endl << endl;

			if (subOption == 'Y')
				EnterElements(B, "B", 1);
			else {

				// Se genera una matriz con elementos aleatorios
				GenerateRandomMatrices(B, false);

				cout << "An array 'B' with random elements was generated." << endl << endl;
			}

			if (AddOns::pauseYesOrNot("Do you want to display matrices A and B (Y/N)?")) {

				cout << "\nYou entered the following Matrix A";

				ShowMatrix(A); //display the matrix on the screen

				cout << "\nYou entered the following Matrix B";

				ShowMatrix(B); //display the matrix on the screen
			}

			textcolor(LIGHTGRAY);

			cout << "\n\nPress a key to see the operations between A and B...";

			cgetch();

			CMatrix C(orden); //an array C is declared to contain the operation between A and B

			//---------------------------------------

			cout << "\nSum of A and B:" << endl;

			AddOns::chronoStart(); //Init chronometer

			C = A + B; //Addition of matrices

			AddOns::chronoEnd(); // End chronometer and show elapsed time

			cout << endl;

			if (AddOns::pauseYesOrNot("Do you want to display the matrix C=A+B (Y/N)?")) {
			
				ShowMatrix(C); //se escribe la matriz C en pantalla				
			}

			cout << endl;

			AddOns::pause(); //se hace una pausa
			
			//------------------------------------------
			
			cout << "\nDifference of A and B:" << endl;

			AddOns::chronoStart(); //Init chronometer

			C = A - B; //Addition of matrices

			AddOns::chronoEnd(); // End chronometer and show elapsed time

			cout << endl;

			if (AddOns::pauseYesOrNot("Do you want to display the matrix C=A-B (Y/N)?")) {

				ShowMatrix(C); //the matrix C is written on the screen

			}
			cout << endl;

			AddOns::pause(); //pause

			//------------------------------------------

			cout << "\nMultiplication of A and B:" << endl;;

			AddOns::chronoStart(); //Init chronometer

			C = A * B; //Addition of matrices

			AddOns::chronoEnd(); // End chronometer and show elapsed time

			cout << endl;

			if (AddOns::pauseYesOrNot("Do you want to display the matrix C=A*B (Y/N)?")) {

				ShowMatrix(C); //the matrix C is written on the screen
			}

			cout << endl;

			AddOns::pause(); //pause
		}
			break;
		case  4:
		{
			clrscr();
			textcolor(LIGHTCYAN);
			cout << Metodo_Matricial[opc] << endl;
			textcolor(WHITE);

			AddOns::chronoStart(); // Init chronometer			

			cout << "\n\nThe transpose of matrix A is:";

			CMatrix T = A.Transposed();

			AddOns::chronoEnd(); // End chronometer and show elapsed time

			if (AddOns::pauseAndExit())
				break;

			ShowMatrix(T);

			cout << std::endl << "Pres any key to continue ... ";

			cgetch();
		}
			break;
		case  5:
		{
			clrscr();
			textcolor(LIGHTCYAN);
			cout << Metodo_Matricial[opc] << endl;
			textcolor(WHITE);

			double Determinant;

			AddOns::chronoStart(); // Init chronometer			

			Determinant = A.DetCofact();

			AddOns::chronoEnd(); // End chronometer and show elapsed time

			if (AddOns::pauseAndExit())
				break;

			cout << "\n\nThe determinant of matrix A is: " << Determinant;

			cout << std::endl << std::endl << "Pres any key to continue ... ";

			cgetch();
		}

			break;
		case  6:
		{

			clrscr();
			textcolor(LIGHTCYAN);
			cout << Metodo_Matricial[opc] << endl;
			textcolor(WHITE);

			CMatrix I;			

			AddOns::chronoStart(); // Init chronometer						

			bool ret = A.InvCofact(I);				

			AddOns::chronoEnd(); // End chronometer and show elapsed time

			if (AddOns::pauseAndExit())
				break;

			cout << "\n\nThe inverse of matrix A by the Transpose Method\nthe cofactor matrix is:\n";

			if (ret)
				//Write the inverse of A on the screen, by the transpose method of the cofactor matrix
				ShowMatrix(I);
			else
				cout << "\n\nThe matrix is not invertible, its determinant is 0.\n";

			cout << std::endl << "Pres any key to continue ... ";

			cgetch();
		}
			break;

		case  7:
		{

			clrscr();
			textcolor(LIGHTCYAN);
			cout << Metodo_Matricial[opc] << endl;
			textcolor(WHITE);

			CMatrix I;			

			AddOns::chronoStart(); // Init chronometer						

			bool ret = A.InvGaussJordan1(I);

			AddOns::chronoEnd(); // End chronometer and show elapsed time
			
			if (AddOns::pauseAndExit())
				break;

			cout << "\n\nThe inverse of matrix A is:\n";

			if (ret)
				//Write the inverse of A on the screen, by the transpose method of the cofactor matrix
				ShowMatrix(I);
			else
				cout << "\n\nThe matrix is not invertible, its determinant is 0.\n";

			cout << std::endl << "Pres any key to continue ... ";

			cgetch();
		}

			break;
		case  8:
		{

			clrscr();
			textcolor(LIGHTCYAN);
			cout << Metodo_Matricial[opc] << endl;
			textcolor(WHITE);

			CMatrix I;
			double Determinant;

			AddOns::chronoStart(); // Init chronometer						

			bool ret = A.InvGaussJordan2(I, Determinant);

			AddOns::chronoEnd(); // End chronometer and show elapsed time

			if (AddOns::pauseAndExit())
				break;

			cout << "\n\nThe determinant of matrix A is: " << Determinant;

			cout << "\n\nThe inverse of matrix A is:\n";

			if (ret)
				//Write the inverse of A on the screen, by the transpose method of the cofactor matrix
				ShowMatrix(I);
			else
				cout << "\n\nThe matrix is not invertible, its determinant is 0.\n";

			cout << std::endl << "Pres any key to continue ... ";

			cgetch();
		}

		break;
		case  9:
		{

			clrscr();
			textcolor(LIGHTCYAN);
			cout << Metodo_Matricial[opc] << endl;
			textcolor(WHITE);

			CMatrix I;
			double Determinant;

			AddOns::chronoStart(); // Init chronometer						

			bool ret = A.InvGaussJordan3(I, Determinant);

			AddOns::chronoEnd(); // End chronometer and show elapsed time

			if (AddOns::pauseAndExit())
				break;

			cout << "\n\nThe determinant of matrix A is: " << Determinant;

			cout << "\n\nThe inverse of matrix A is:\n";

			if (ret)
				//Write the inverse of A on the screen, by the transpose method of the cofactor matrix
				ShowMatrix(I);
			else
				cout << "\n\nThe matrix is not invertible, its determinant is 0.\n";

			cout << std::endl << "Pres any key to continue ... ";

			cgetch();
		}

		break;
		case  10:
		{
			
			clrscr();
			textcolor(LIGHTCYAN);
			cout << Metodo_Matricial[opc] << endl;
			textcolor(WHITE);

			CMatrix I;

			//matriz de terminos independientes
			CMatrix B(A.Order(),1);

			textcolor(LIGHTGRAY);
			cout << "\nIf we consider the system AX=b" << endl;
			cout << "The calculation of X = A^-1 b will be carried out" << endl;
			cout << "Where the inverse matrix A^-1 will be calculated with the Gauss Jordan 1 method" << endl << endl;

			textcolor(WHITE);
			cout << "Do you want to enter matrix b manually (Y/N)?";
			char subOption = toupper(cgetch());

			textcolor(LIGHTGRAY);

			cout << endl << endl;

			if (subOption == 'Y')				
				EnterElements(B, "b", 1);
			else {	

				// An array is generated with random elements
				GenerateRandomMatrices(B, false);

				cout << "An array 'b' with random elements was generated." << endl << endl;
			}

			//solution matrix
			//declare a matrix with n rows and one column
			CMatrix X(A.Order(), 1);

			AddOns::chronoStart(); //Init chronometer

			bool ret = A.InvGaussJordan1(I);

			//through Matrix Algebra we know that the solution of A*X = B
			//is X = Inverse(A)*B

			if (ret) {
				//assign X the solution of the system
				X = I * B;

			}

			AddOns::chronoEnd(); // End chronometer and show elapsed time

			if (AddOns::pauseAndExit())
				break;

			if (ret) {

				int i, j, n = A.Order();

				cout << "\n\nSystem Ax=B Entered: \n";

				textcolor(YELLOW);
				cout << "Matrix A";
				
				gotoxy(9 * A.Order(), wherey());
				textcolor(LIGHTGREEN);
				cout << "Matrix B" << endl;

				for (i = 0; i < n; i++) {

					// Show Matriz A
					textcolor(YELLOW);
					for (j = 0; j < n; j++)
						cout << A.Element[i][j] << '\t';

					// Show Matriz B
					textcolor(LIGHTGREEN);
					cout << B.Element[i][0] << endl;
				}
				
				textcolor(LIGHTGRAY);

				cout << endl << endl << "The system solution is:";

				//mostramos la solucion del sistema				
				for (i = 0; i < X.Rows(); i++)
					cout << "\nX" << i + 1 << " = " << X.Element[i][0];
			}
			else {
				cout << "\n\nThe system is indeterminate. A solution could not be found.\n";
			}

			cgetch();
			
		}

		break;
		case -1:
		case  11:

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