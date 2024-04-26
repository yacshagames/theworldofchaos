/***************************************************************************
EJEMPLO DEL USO DE CMATRIZ versi¢n 1.4

Este ejemplo muestra como usar la poderosa clase CMatriz, para trabajar
con matrices. Y mostrar como esta clase se puede incluir f cilmente en
sus aplicaciones matem ticas.

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
#include "cmatrix.h" //Cabecera con funciones espec¡ficas para
//el ALGEBRA DE MATRICES

using std::cout;
using std::cin;
using std::endl;

void ImprimirTitulo()
{
	//clrscr();
	cout << ":: CMATRIX DEMO :: " << endl;
	cout << "-- ALGEBRA OF MATRIXES -- ALGEBRA DE MATRICES --" << endl;
}

void pausa()
{
	int n;
	cout <<"\n\nIngrese un numero para continuar: ";
	cin >> n;
}


//////////////////////////////////////////////////////////////////////
//SE INGRESAN LOS ELEMENTOS DE LA MATRIZ, DESDE EL TECLADO, UNO POR UNO
void IngresarElementos(CMatrix& A)
{
	int i, j, FIL = A.Fil(), COL=A.Col();

	for (i = 0; i < FIL; i++)
		for (j = 0; j < COL; j++)
		{
			//printf("Elemento ( Fil=%i, Col=%i ) = ", i, j);
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
	if (A.InvGauss(I))
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

	//LA DIFERENCIA ENTRE InvGauss e InvCofact es que la primera necesita
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
	if (A.InvGauss(I)){
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
}