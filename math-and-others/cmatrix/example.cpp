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

#include <conio.h>
#include "cmatriz.h" //Cabecera con funciones espec¡ficas para
//el ALGEBRA DE MATRICES

void ImprimirTitulo()
{
	clrscr();
	printf("\t\t\t****CMATRIZ 1.4 DEMO****");
	printf("\n\t\t\tALGEBRA DE MATRICES");
}

void pausa()
{
	printf("\n\nPresione una tecla para continuar...");
	getch();
}

//UN EJEMPLO
//IMPORTANTE: Si al correr el programa, este compila sin errores pero
//al momento de ejecutarlo se cuelga el programa, mostrando un error
//esto puede deberse a que no hay memoria suficiente para crear las matrices
//sugiero que cambie el valor de _MAX (definido en CMATRIZ.H )
//a un valor menoral que contiene actualmente
void main()
{
	/////////////////////////////////////////////////////////////////////////
	//PRIMER EJEMPLO
	/////////////////////////////////////////////////////////////////////////
	ImprimirTitulo(); //T¡tulo de la Demo de CMatriz 1.4

	printf("\n\nIngresar datos de la matriz A (Matriz cuadrada)");
	printf("\n\nIngrese el orden de la matriz: ");

	int orden;
	scanf("%i", &orden);

	CMatriz A(orden); //se declara una matriz del orden especificado

	printf("\nIngrese los elementos de la matriz A:\n\n");

	A.IngresarElementos(); // se ingresan los elementos de la matriz A desde el
				 // teclado

	printf("\n\nPresione una tecla para ver la matriz ingresada...");
	getch();

	ImprimirTitulo(); //T¡tulo de la Demo de CMatriz 1.4

	printf("\n\nUsted ingres¢ la siguiente Matriz A");

	A.Escribir(); //muestra la matriz en pantalla

	printf("\n\nPresione una tecla para ver su determinante y su inversa...");
	getch();

	ImprimirTitulo(); //T¡tulo de la Demo de CMatriz 1.4

	printf("\n\nLa determinante de la matriz A es: %f", Det(A));

	pausa(); //se hace una pausa

	printf("\n\nLa inversa de la matriz A por el M‚todo de Reducci¢n Gaussiana es:\n");

	InvGauss(A).Escribir(); //Escribe la inversa de A en pantalla, por el m‚todo de reducci¢n Gaussiana

	pausa(); //se hace una pausa

	printf("\n\nLa inversa de la matriz A por el M‚todo de la transpuesta\nde la matriz de cofactores es:\n");

	InvCofact(A).Escribir(); //Escribe la inversa de A en pantalla, por el m‚todo de la transpuesta de la matriz de cofactores

	pausa(); //se hace una pausa

	//LA DIFERENCIA ENTRE InvGauss e InvCofact es que la primera necesita
	//de menos memoria que la segunda, pero la segunda hace menos operaciones
	//que la primera, por la tanto InvCofact es mas r pida

	/////////////////////////////////////////////////////////////////////////
	//SEGUNDO EJEMPLO
	/////////////////////////////////////////////////////////////////////////
	ImprimirTitulo(); //T¡tulo de la Demo de CMatriz 1.4

	printf("\n\nComprobando las operaciones entre matrices (Suma, Resta, multiplicaci¢n)");
	printf("\n\nA continuaci¢n se le pedir  que ingrese los datos una matriz B, la cual se");
	printf("\noperar  con A. Entonces usted ya sabe que el orden de dicha matriz debe ser");
	printf("\nigual al orden de A, pero si usted quiere probar la facilidad con que CMatriz,");
	printf("\ndetecta errores en las dimensiones entre A y B al hacer operaciones, ingrese");
	printf("\nun orden para B diferente al de A");

	printf("\n\nIngresar datos de la matriz B (Matriz cuadrada)");
	printf("\n\nIngrese el orden de la matriz: ");

	scanf("%i", &orden);

	CMatriz B(orden); //se declara una matriz del orden especificado

	printf("\nIngrese los elementos de la matriz B:\n\n");

	B.IngresarElementos(); // se ingresan los elementos de la matriz A desde el
				 // teclado

	printf("\n\nPresione una tecla para ver la matriz ingresada...");
	getch();

	ImprimirTitulo(); //T¡tulo de la Demo de CMatriz 1.4

	printf("\n\nUsted ingres¢ la siguiente Matriz B");

	B.Escribir(); //muestra la matriz en pantalla

	printf("\n\nPresione una tecla para ver las operaciones entre A y B...");

	ImprimirTitulo(); //T¡tulo de la Demo de CMatriz 1.4

	CMatriz C(orden); //se declara una matriz C para contener la operaci¢n entre A y B

	printf("\nSuma de A y B:");

	C = A + B; //Suma de matrices

	C.Escribir(); //se escribe la matriz C en pantalla

	pausa(); //se hace una pausa

	printf("\nDiferencia de A y B:");

	C = A - B; //Suma de matrices

	C.Escribir(); //se escribe la matriz C en pantalla

	pausa(); //se hace una pausa

	printf("\nMultiplicaci¢n de A y B:");

	C = A * B; //Suma de matrices

	C.Escribir(); //se escribe la matriz C en pantalla

	pausa(); //se hace una pausa

	/////////////////////////////////////////////////////////////////////////
	//TERCER EJEMPLO
	/////////////////////////////////////////////////////////////////////////
	ImprimirTitulo(); //T¡tulo de la Demo de CMatriz 1.4

	printf("\n\nComo £ltimo ejemplo vamos a resolver un sistema de 3 ecuaciones");
	printf("\ncon 3 inc¢gnitas:");

	//matriz de coeficientes
	A = CMatriz(3);//se declara una matriz de orden 3

	//matriz de terminos independientes
	B = CMatriz(3, 1);//se declara una matriz con 3 filas y una columna

	//matriz de soluciones
	CMatriz X(3, 1);//se declara una matriz con 3 filas y una columna

	//Se crea el sistema matricial A*X = B
	//se obtienen los elementos de la matriz A y la matriz B
	int i, j;
	float elemento;

	printf("\n\nIngrese los coeficientes de las 3 ecuaciones:");

	for (i = 0; i < 3; i++)
	{
		printf("\n\nIngrese los coeficientes a%i, b%i, c%i y d%i", i + 1, i + 1, i + 1, i + 1);
		printf("\nde la ecuaci¢n a%ix + b%iy + c%iz = d%i\n\n",
			i + 1, i + 1, i + 1, i + 1);
		for (j = 0; j < 4; j++)
		{
			printf("%c%i = ", 'a' + j, i + 1);
			scanf("%f", &elemento);
			if (j < 3)
				A.Elemento[i][j] = elemento;
			else
				B.Elemento[i][0] = elemento;
		}
	}
	//por el Algebra matricial sabemos que la soluci¢n de  A*X = B
	//es X = Inversa(A)*B

	//asignamos a X la soluci¢n del sistema
	X = InvGauss(A)*B;

	printf("\nLa soluci¢n del sistema es:");

	//mostramos la soluci¢n del sistema
	for (i = 0; i < 3; i++)
		printf("\nX%i = %f", i + 1, X.Elemento[i][0]);

	pausa(); //se hace una pausa

	ImprimirTitulo(); //T¡tulo de la Demo de CMatriz 1.4

	gotoxy(1, 4);
	printf("\nfue programado por:");
	printf("\n JOSE LUIS DE LA CRUZ LAZARO");
	printf("\ncorreos:");
	printf("\n jcruz@ec-red.com");
	printf("\n ramondc@hotmail.com");
	printf("\nPagina Web ( EL MUNDO DEL CAOS ):");
	printf("\n http://www.geocities.com/joseluisdl");


	gotoxy(30, 15);
	printf("FIN DE LA DEMO... ;(");

	getch();

}