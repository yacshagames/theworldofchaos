/***************************************************************************
EJEMPLO DEL USO DE CMATRIZ versi¢n 1.4

Este ejemplo muestra como usar la poderosa clase CMatriz, para trabajar
con matrices. Y mostrar como esta clase se puede incluir f cilmente en
sus aplicaciones matem ticas.


Para procesar una matriz de 5000 elementos se demora 240, 455 y 450 segundos
para los métodos  InvGaussJordan1, InvGaussJordan2 e InvGaussJordan3,
respectivamente y cada función ocupa aproximadamente 600MB de memoria RAM,
durante la ejecución del algoritmo.


programado por:
 JOSE LUIS DE LA CRUZ LAZARO
correos:
 jcruz@ec-red.com
 ramondc@hotmail.com
Pagina Web ( EL MUNDO DEL CAOS ):
 http://www.geocities.com/joseluisdl
***************************************************************************/

//#include <conio.h>
#include <iostream>
#include <string>
#include <random>
#include <functional> // bind
#include "cmatrix.h" //Cabecera con funciones espec¡ficas para el ALGEBRA DE MATRICES
#include "conio.h"
#include "Menu.h"
#include "AddOns.h"

using std::cout;
using std::cin;
using std::endl;

//////////////////////////////////////////////////////////////////////
//SE INGRESAN LOS ELEMENTOS DE LA MATRIZ, DESDE EL TECLADO, UNO POR UNO
void IngresarElementos( CMatrix& A, string MatrixName, const unsigned int& Cols=0 )
{

	cout << "Ingrese elementos de la matriz " << MatrixName << std::endl;

	int i, j, FIL = A.Fil(), COL = Cols==0 ? A.Col() : Cols;

	for (i = 0; i < FIL; i++)
		for (j = 0; j < COL; j++)
		{
			cout << "Elemento ( Fil="<< i <<  ", Col=" << j << " ) = ";
			// se ingresan los elementos al arreglo Elemento, el cual es miembro de la matriz A
			cin >> A.Elemento[i][j];
		}
}
//////////////////////////////////////////////////////////////////////
//ESCRIBE LA MATRIZ EN LA PANTALLA
void Escribir(const CMatrix& A)
{
	cout << endl << endl;

	int i, j, FIL = A.Fil(), COL = A.Col();

	for (i = 0; i < FIL; i++){

		for (j = 0; j < COL; j++)
			cout << A.Elemento[i][j] << '\t';

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

		if (A.Orden() > 0) {

			// A diagonally dominant matrix is created with random elements in the pre-specified
			// range. So that it can be successfully processed by the Cholesky and Gauss-Seidel algorithms

			const int& n = A.Orden();
			//double matrixDimension = double(n);

			// Distribution values between matrixDimension*1.2 and matrixDimension*1.5
			std::uniform_int_distribution<int> distributionDiagonal(n * 12, n * 15);

			std::mt19937 engine(rd()); // Mersenne twister MT19937

			int i, j;
			for (i = 0; i < n; i++)
				for (j = 0; j < n; j++)
					A.Elemento[i][j] = i == j ?
					distributionDiagonal(engine) :	// Random values between -1 and 1
					distribution(engine);			// Random values between matrixDimension*1.2 and matrixDimension*1.5
		}
	}
	else {

		for (auto& element : A.Elemento) {

			std::mt19937 engine(rd()); // Mersenne twister MT19937
			auto generator = std::bind(distribution, engine);

			std::generate_n(element.begin(), element.size(), generator);
		}
	}

}

/*
//UN EJEMPLO
//IMPORTANTE: Si al correr el programa, este compila sin errores pero
//al momento de ejecutarlo se cuelga el programa, mostrando un error
//esto puede deberse a que no hay memoria suficiente para crear las matrices
//sugiero que cambie el valor de _MAX (definido en CMATRIZ.H )
//a un valor menoral que contiene actualmente
int main()
{
	/////////////////////////////////////////////////////////////////////////
	//PRIMER EJEMPLO
	/////////////////////////////////////////////////////////////////////////
	ImprimirTitulo(); //T¡tulo de la Demo de CMatriz 1.4

	printf("\n\nIngresar datos de la matriz A (Matriz cuadrada)");
	printf("\n\nIngrese el orden de la matriz: ");

	int orden;
	cin >> orden;

	CMatrix A(orden); //se declara una matriz del orden especificado

	printf("\nIngrese los elementos de la matriz A:\n\n");

	IngresarElementos(A); // se ingresan los elementos de la matriz A desde el
				 // teclado

	//printf("\n\nPresione una tecla para ver la matriz ingresada...");
	//getch();
	pausa();

	//ImprimirTitulo(); //T¡tulo de la Demo de CMatriz 1.4

	cout << "\n\nUsted ingres¢ la siguiente Matriz A";

	Escribir(A); //muestra la matriz en pantalla

	//printf("\n\nPresione una tecla para ver su determinante y su inversa...");
	//getch();
	pausa();


	//ImprimirTitulo(); //T¡tulo de la Demo de CMatriz 1.4

	cout << "\n\nLa determinante de la matriz A es: " << A.DetCofact();

	pausa(); //se hace una pausa

	cout << "\n\nLa inversa de la matriz A por el M‚todo de Reducci¢n Gaussiana es:\n";

	CMatrix I;
	if (A.InvGaussJordan1(I))
		//Escribe la inversa de A en pantalla, por el m‚todo de reducci¢n Gaussiana
		Escribir(I); 
	else
		cout << "\n\nLa matriz no es inversible, su determinante es 0.\n";

	pausa(); //se hace una pausa

	printf("\n\nLa inversa de la matriz A por el M‚todo de la transpuesta\nde la matriz de cofactores es:\n");

	if (A.InvCofact(I))
		//Escribe la inversa de A en pantalla, por el m‚todo de la transpuesta de la matriz de cofactores
		Escribir(I);
	else
		cout << "\n\nLa matriz no es inversible, su determinante es 0.\n";

	pausa(); //se hace una pausa

	//LA DIFERENCIA ENTRE InvGaussJordan1 e InvCofact es que la primera necesita
	//de menos memoria que la segunda, pero la segunda hace menos operaciones
	//que la primera, por la tanto InvCofact es mas r pida

	/////////////////////////////////////////////////////////////////////////
	//SEGUNDO EJEMPLO
	/////////////////////////////////////////////////////////////////////////
	ImprimirTitulo(); //T¡tulo de la Demo de CMatriz 1.4

	cout << "\n\nComprobando las operaciones entre matrices (Suma, Resta, multiplicaci¢n)";
	cout << "\n\nA continuaci¢n se le pedir  que ingrese los datos una matriz B, la cual se";
	cout << "\noperar  con A. Entonces usted ya sabe que el orden de dicha matriz debe ser";
	cout << "\nigual al orden de A, pero si usted quiere probar la facilidad con que CMatrix,";
	cout << "\ndetecta errores en las dimensiones entre A y B al hacer operaciones, ingrese";
	cout << "\nun orden para B diferente al de A";

	cout << "\n\nIngresar datos de la matriz B (Matriz cuadrada)";
	cout << "\n\nIngrese el orden de la matriz: ";

	cin >> orden;

	//se declara una matriz del orden especificado
	CMatrix B(orden);

	cout << "\nIngrese los elementos de la matriz B:\n\n";

	// se ingresan los elementos de la matriz A desde el teclado
	IngresarElementos(B);

	//printf("\n\nPresione una tecla para ver la matriz ingresada...");
	pausa();
	
	//ImprimirTitulo(); //T¡tulo de la Demo de CMatriz 1.4

	cout << "\n\nUsted ingres¢ la siguiente Matriz B";

	Escribir(B); //muestra la matriz en pantalla

	cout << "\n\nPresione una tecla para ver las operaciones entre A y B...";

	//ImprimirTitulo(); //T¡tulo de la Demo de CMatriz 1.4

	CMatrix C(orden); //se declara una matriz C para contener la operaci¢n entre A y B

	cout << "\nSuma de A y B:";

	C = A + B; //Suma de matrices

	Escribir(C); //se escribe la matriz C en pantalla

	pausa(); //se hace una pausa

	cout << "\nDiferencia de A y B:";

	C = A - B; //Suma de matrices

	Escribir(C); //se escribe la matriz C en pantalla

	pausa(); //se hace una pausa

	cout << "\nMultiplicaci¢n de A y B:";

	C = A * B; //Suma de matrices

	Escribir(C); //se escribe la matriz C en pantalla

	pausa(); //se hace una pausa

	/////////////////////////////////////////////////////////////////////////
	//TERCER EJEMPLO
	/////////////////////////////////////////////////////////////////////////
	ImprimirTitulo(); //T¡tulo de la Demo de CMatriz 1.4

	cout << "\n\nComo £ltimo ejemplo vamos a resolver un sistema de 3 ecuaciones";
	cout << "\ncon 3 inc¢gnitas:";

	//matriz de coeficientes
	A = CMatrix(3);//se declara una matriz de orden 3

	//matriz de terminos independientes
	B = CMatrix(3, 1);//se declara una matriz con 3 filas y una columna

	//matriz de soluciones
	CMatrix X(3, 1);//se declara una matriz con 3 filas y una columna

	//Se crea el sistema matricial A*X = B
	//se obtienen los elementos de la matriz A y la matriz B
	int i, j;
	double elemento;

	cout << "\n\nIngrese los coeficientes de las 3 ecuaciones:";

	for (i = 0; i < 3; i++)
	{
		cout << "\n\nIngrese los coeficientes a" << i + 1 << ", b" << i + 1 << ", c" << i + 1 << " y d" << i + 1;
		cout << "\nde la ecuaci¢n a" << i + 1 << "x + b" << i + 1 << "y + c" << i + 1 << "z = d" << i + 1 << "\n\n";

		for (j = 0; j < 4; j++)
		{
			cout << std::string(1, 'a' + j) << i + 1 << ": ";
			cin >> elemento;
			if (j < 3)
				A.Elemento[i][j] = elemento;
			else
				B.Elemento[i][0] = elemento;
		}
	}
	//por el Algebra matricial sabemos que la soluci¢n de  A*X = B
	//es X = Inversa(A)*B
	
	// CMatrix I;
	if (A.InvGaussJordan1(I)){
		//asignamos a X la soluci¢n del sistema
		X = I * B;
		cout << "\nLa soluci¢n del sistema es:";

		//mostramos la soluci¢n del sistema
		for (i = 0; i < 3; i++)
			cout << "\nX" << i + 1 << " = " << X.Elemento[i][0];
	}
	else {
		cout << "\n\nEl sistema es indeterminado. No se pudo encontrar una solución.\n";
	}

	pausa(); //se hace una pausa

	ImprimirTitulo(); //T¡tulo de la Demo de CMatrix

	//gotoxy(1, 4);
	cout << "\nfue programado por:";
	cout << "\n JOSE LUIS DE LA CRUZ LAZARO";
	cout << "\n email: ramondc@hotmail.com";
	cout << "\nPagina Web ( EL MUNDO DEL CAOS ):";
	cout << "\n\nFIN DE LA DEMO... ;(";	
	
	return 1;
}*/

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
		if ( A.Orden() <= 0 )
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

			cout << "\n\nIngrese el orden de la matriz: ";
			int orden;
			cin >> orden;
			A = CMatrix(orden); //se declara una matriz del orden especificado

			IngresarElementos(A, "A");

			break;
		case 1:
		{
			clrscr();
			cout << "\n\nIngrese el orden de la matriz: ";
			int orden;
			cin >> orden;
			A = CMatrix(orden); //se declara una matriz del orden especificado

			//textcolor(LIGHTGRAY);
			//cout << "\nIf you create a diagonally dominant matrix, it can be successfully processed" << endl;
			//cout << "by the Cholesky and Gauss-Seidel algorithms." << endl << endl;

			cout << endl << endl;

			textcolor(WHITE);
			cout << "Generate diagonally dominant matrix (Y/N)? ";
			char subOption = toupper(cgetch());

			GenerateRandomMatrices(A, subOption == 'Y');
		}

		break;
		case 2:
			
			clrscr();

			cout << "\n\nUsted ingreso la siguiente Matriz A :";

			Escribir(A); //muestra la matriz en pantalla

			cout << std::endl << "Pres any key to continue ... ";

			cgetch();

			break;
		case  3:
		{
			clrscr();
			textcolor(LIGHTCYAN);
			cout << Metodo_Matricial[opc] << endl;

			textcolor(LIGHTGRAY);
			cout << "\n\nComprobando las operaciones entre matrices (Suma, Resta, multiplicaci¢n)";
			cout << "\n\nA continuaci¢n se le pedir  que ingrese los datos una matriz B, la cual se";
			cout << "\noperar  con A. Entonces usted ya sabe que el orden de dicha matriz debe ser";
			cout << "\nigual al orden de A, pero si usted quiere probar la facilidad con que CMatrix,";
			cout << "\ndetecta errores en las dimensiones entre A y B al hacer operaciones, ingrese";
			cout << "\nun orden para B diferente al de A";

			cout << "\n\nIngresar datos de la matriz B (Matriz cuadrada)";
			cout << "\n\nIngrese el orden de la matriz: ";

			cin >> orden;

			//se declara una matriz del orden especificado
			CMatrix B(orden);


			textcolor(WHITE);
			cout << "Desea ingresar la matriz B manualmente (Y/N)? ";
			char subOption = toupper(cgetch());

			textcolor(LIGHTGRAY);

			cout << endl << endl;

			if (subOption == 'Y')
				IngresarElementos(B, "B", 1);
			else {

				// Se genera una matriz con elementos aleatorios
				GenerateRandomMatrices(B, false);

				cout << "Se generó una matriz 'B' con elementos aleatorios." << endl << endl;
			}

			if (AddOns::pauseYesOrNot("Desea visualizar las matrices A y B (Y/N)?") ) {

				cout << "\nUsted ingreso la siguiente Matriz A";

				Escribir(A); //muestra la matriz en pantalla

				cout << "\nUsted ingreso la siguiente Matriz B";

				Escribir(B); //muestra la matriz en pantalla
			}

			textcolor(LIGHTGRAY);

			cout << "\n\nPresione una tecla para ver las operaciones entre A y B...";

			cgetch();

			CMatrix C(orden); //se declara una matriz C para contener la operaci¢n entre A y B

			//------------------------------------------
			
			cout << "\nSuma de A y B:" << endl;					   

			AddOns::chronoStart(); // Init chronometer	

			C = A + B; //Suma de matrices

			AddOns::chronoEnd(); // End chronometer and show elapsed time

			cout << endl;

			if (AddOns::pauseYesOrNot("Desea visualizar la matriz C=A+B (Y/N)?")) {
			
				Escribir(C); //se escribe la matriz C en pantalla				
			}

			cout << endl;

			AddOns::pause(); //se hace una pausa
			
			//------------------------------------------
			
			cout << "\nDiferencia de A y B:" << endl;

			AddOns::chronoStart(); // Init chronometer	
			
			C = A - B; //Suma de matrices

			AddOns::chronoEnd(); // End chronometer and show elapsed time

			cout << endl;

			if (AddOns::pauseYesOrNot("Desea visualizar la matriz C=A-B (Y/N)?")) {

				Escribir(C); //se escribe la matriz C en pantalla				

			}
			cout << endl;

			AddOns::pause(); //se hace una pausa

			//------------------------------------------

			cout << "\nMultiplicaci¢n de A y B:" << endl;;

			AddOns::chronoStart(); // Init chronometer	

			C = A * B; //Suma de matrices

			AddOns::chronoEnd(); // End chronometer and show elapsed time

			cout << endl;

			if (AddOns::pauseYesOrNot("Desea visualizar la matriz C=A*B (Y/N)?")) {

				Escribir(C); //se escribe la matriz C en pantalla				
			}

			cout << endl;

			AddOns::pause(); //se hace una pausa		
		}
			break;
		case  4:
		{
			clrscr();
			textcolor(LIGHTCYAN);
			cout << Metodo_Matricial[opc] << endl;
			textcolor(WHITE);

			AddOns::chronoStart(); // Init chronometer			

			cout << "\n\nLa transpuesta de la matriz A es:";

			CMatrix T = A.Transposed();

			AddOns::chronoEnd(); // End chronometer and show elapsed time

			if (AddOns::pauseAndExit())
				break;

			Escribir(T);

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

			cout << "\n\nEl determinante de la matriz A es: " << Determinant;

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

			cout << "\n\nLa inversa de la matriz A por el Metodo de la transpuesta\nde la matriz de cofactores es:\n";

			if (ret)
				//Escribe la inversa de A en pantalla, por el m‚todo de la transpuesta de la matriz de cofactores
				Escribir(I);
			else
				cout << "\n\nLa matriz no es inversible, su determinante es 0.\n";

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

			cout << "\n\nLa inversa de la matriz A es:\n";

			if (ret)
				//Escribe la inversa de A en pantalla, por el m‚todo de la transpuesta de la matriz de cofactores
				Escribir(I);
			else
				cout << "\n\nLa matriz no es inversible, su determinante es 0.\n";

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

			cout << "\n\nEl determinante de la matriz A es: " << Determinant;

			cout << "\n\nLa inversa de la matriz A es:\n";

			if (ret)
				//Escribe la inversa de A en pantalla, por el m‚todo de la transpuesta de la matriz de cofactores
				Escribir(I);
			else
				cout << "\n\nLa matriz no es inversible, su determinante es 0.\n";

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

			cout << "\n\nEl determinante de la matriz A es: " << Determinant;

			cout << "\n\nLa inversa de la matriz A es:\n";

			if (ret)
				//Escribe la inversa de A en pantalla, por el m‚todo de la transpuesta de la matriz de cofactores
				Escribir(I);
			else
				cout << "\n\nLa matriz no es inversible, su determinante es 0.\n";

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
			CMatrix B(A.Orden(),1);

			textcolor(LIGHTGRAY);
			cout << "\nSi consideramos el sistema AX=b" << endl;
			cout << "Se procederá al cálculo de X = A^-1 b" << endl;
			cout << "Donde la matriz inversa A^-1 se calculara con el método Gauss Jordan 1" << endl << endl;

			textcolor(WHITE);
			cout << "Desea ingresar la matriz b manualmente (Y/N)? ";
			char subOption = toupper(cgetch());

			textcolor(LIGHTGRAY);

			cout << endl << endl;

			if (subOption == 'Y')				
				IngresarElementos(B, "b", 1);
			else {	

				// Se genera una matriz con elementos aleatorios
				GenerateRandomMatrices(B, false);

				cout << "Se generó una matriz 'b' con elementos aleatorios." << endl << endl;
			}
			
			//matriz de soluciones
			//se declara una matriz con n filas y una columna
			CMatrix X(A.Orden(), 1);			

			AddOns::chronoStart(); // Init chronometer						

			bool ret = A.InvGaussJordan1(I);			

			//por el Algebra matricial sabemos que la soluci¢n de  A*X = B
			//es X = Inversa(A)*B

			if (ret) {
				//asignamos a X la soluci¢n del sistema
				X = I * B;
				
			}

			AddOns::chronoEnd(); // End chronometer and show elapsed time

			if (AddOns::pauseAndExit())
				break;

			if (ret) {

				int i, j, n = A.Orden();

				cout << "\n\nSystem Ax=B Entered: \n";

				textcolor(YELLOW);
				cout << "Matrix A";
				
				gotoxy(9 * A.Orden(), wherey());
				textcolor(LIGHTGREEN);
				cout << "Matrix B" << endl;

				for (i = 0; i < n; i++) {

					// Show Matriz A
					textcolor(YELLOW);
					for (j = 0; j < n; j++)
						cout << A.Elemento[i][j] << '\t';

					// Show Matriz B
					textcolor(LIGHTGREEN);
					cout << B.Elemento[i][0] << endl;
				}
				
				textcolor(LIGHTGRAY);

				cout << endl << endl << "La solucion del sistema es:";

				//mostramos la solucion del sistema				
				for (i = 0; i < X.Fil(); i++)
					cout << "\nX" << i + 1 << " = " << X.Elemento[i][0];
			}
			else {
				cout << "\n\nEl sistema es indeterminado. No se pudo encontrar una solución.\n";
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