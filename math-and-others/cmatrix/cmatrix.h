#pragma once
/***********************************************************************************
 :: CMATRIX :::
 -- ALGEBRA OF MATRIXES -- ALGEBRA DE MATRICES --
 
 Esta clase provee de operaciones elementales entre matrices, como la suma de
 matrices, diferencia de matrices, negativo de una matriz, multiplicaci�n de un
 escalar por una matriz y multiplicaci�n de matrices. Adem�s de que provee
 de m�todos para calcular el determinante, la matriz inversa, y la matriz transpuesta.

 Programmed by:

	JOSE LUIS DE LA CRUZ LAZARO
	ramondc@hotmail.com

	UNIVERSIDAD NACIONAL DE INGENIERIA
	Faculty of Electrical and Electronic Engineering
	Lima-Peru

	YACSHA - Software & Desing
	>> The World of chaos - EL MUNDO DEL CAOS - Unlimited Programming

 HISTORY...

 >> Version 2 - 26-IV-2024
	- Update math-and-others\cmatrix - Porting to VC++ 2017
	- Merge cmatriz4, matrices and matripak in cmatrix
	- Separate the CMatrix class into .h and .cpp files
	- Rename class CMatriz for CMatrix
	- Update to C++17, using std::vector instead of old arrays
	- In the CMatrix class, the DetCofact, InvCofact and InvGauss methods are added;
	  to calculate the determinant by the cofactor method; Inverse of a matrix by the
	  cofactor method and inverse of a matrix by the Gauss-Jordan method
	- The methods of overloaded algebraic operators are corrected, defining their
	  parameters as constants. Likewise, several methods are corrected, indicating
	  which are constants and which have constant parameters.
	- The Transposed method is added to calculate the matrix transposed to the
	  original.
	- The InvGauss and InvCofact methods now return a boolean indicating whether the
	  inversion was performed successfully, so that the user can take action in cases
	  where the matrix is not invertible.
	- The Initialize method is eliminated, since now the initialization is done with
	  the standard resize method of std::vector
	- The EnterElements and Write methods are removed from the CMatrix library, so as
	  not to mix the functions of the view (in this case the console) with the domain
	  (CMatrix library), so that the CMatrix library can be used in multiple views,
	  which will not necessarily be the console
	- The IngresarElementos and Escribir methods are declared as global functions in the
	  example.cpp file, to enter the data of the array
	- The InvGauss method of CMatriz 1.4 is renamed to InvGaussJordan2
	- The InvGaussJordan1 method is added, which was an independent program that
	  now integrates the CMatrix library
	- The InvGaussJordan3 method is added, which was an independent program that
	  now integrates the CMatrix library. This program is added in conjunction
	  with the private step and reverse methods, which are recursive functions
	  that are invoked by InvGaussJordan3.
	- Now the methods InvGaussJordan2 and InvGaussJordan3 allow you to simultaneously
	  calculate the inverse matrix and the determinant of the original matrix
	- Some bugs are corrected in InvGaussJordan2, InvGaussJordan3, which did not allow
	  the correct calculation of the inverse matrix and a consistency validation of
	  the diagonal of the pivoted matrix G (left G) is also added, in such a way that
	  no element of the diagonal of G left must be zero, otherwise the matrix is not
	  invertible. In this way, these functions return a boolean indicating whether the
	  calculation of the inverse matrix could be carried out.
	- The private IsZero method is added, using a small delta, to check if a variable
	  is zero, since previously the operator X==0 was used to check if a variable is
	  zero, which could give unexpected results.
	- Version history and credits are updated.
	- Translations from Spanish to English are added to the version history
	- Obsolete files are removed

	 Spanish:
	- Se actualiza math-and-others\cmatrix - Se hace el porting a VC++ 2017
	- Se fusionan los proyectos cmatriz4, matrices y mattripak en cmatrix
	- Se separa la clase CMatrix en archivos .h y .cpp
	- Se cambia el nombre de la clase CMatriz por CMatrix
	- Actualizaci�n a C++ 17, usando std::vector en lugar de matrices antiguas
	- En la clase CMatrix se agregan los m�todos DetCofact, InvCofact e InvGauss;
	  calcular el determinante mediante el m�todo del cofactor;
	  Inversa de una matriz por el m�todo del cofactor e inversa de una matriz por
	  el m�todo de Gauss-Jordan
	- Se corrigen los m�todos de operadores algebraicos sobrecargados, definiendo sus
	  par�metros como constantes. Asimismo, se corrigen varios m�todos, indicando cu�les
	  son constantes y cu�les tienen par�metros constantes.
	- Se agrega el m�todo Transpuesto para calcular la matriz transpuesta al original.
	- Los m�todos InvGauss e InvCofact ahora devuelven un booleano que indica si la
	  inversi�n se realiz� exitosamente, para que el usuario pueda tomar medidas en los
	  casos en que la matriz no sea invertible.
	- Se elimina el m�todo Inicializar, ya que ahora la inicializaci�n se hace con el
	  m�todo estandar resize de std::vector
	- Se remueve de la libreria CMatrix los m�todos IngresarElementos y Escribir, para
	  no mezclar las funciones de la vista (en este caso la consola), con el dominio
	  (librer�a CMatrix), de tal manera que la libreria CMatrix se pueda usar en m�ltiples
	  vistas, que no necesariamente ser� la consola
	- Los m�todos IngresarElementos y Escribir son declarados como funciones globales en
	  el archivo ejemplo.cpp, para ingresar los datos de la matriz
	- El m�todo InvGauss de CMatriz 1.4 se renombra a InvGaussJordan2
	- Se agrega el m�todo InvGaussJordan1, el cual era un programa independiente que
	  ahora pasa a integrar la libreria CMatrix
	- Se agrega el m�todo InvGaussJordan3, el cual era un programa independiente que ahora
	  pasa a integrar la libreria CMatrix. Este programa se agrega en conjunto con los
	  m�todos privados escalonada e inversa, los cuales son funciones recursivas que son
	  invocados por InvGaussJordan3.
	- Ahora los m�todos InvGaussJordan2 e InvGaussJordan3, permiten calcular
	  simultaneamente la matriz inversa y el determinante, de la matriz original
	- Se corrige algunos bugs en InvGaussJordan2, InvGaussJordan3, que no permitian el
	  correcto c�lculo de la matriz inversa y adem�s se agrega una validaci�n de
	  consistencia de la diagonal de la matriz G pivoteada (G izquierdo), de tal manera
	  que ning�n elemento de la diagonal de G izquierdo deba ser cero, caso contrario
	  la matriz no es inversible. De esta manera estas funciones retornan un booleano
	  indicando si se pudo realizar el c�lculo de la matriz inversa
	- Se agrega el m�todo privado IsZero, usando un delta peque�o, para verificar si
	  una variable es cero, ya que anteriormente se usaba el operador X==0 para verificar
	  si una variable es cero, lo cual podr�a dar resultados no esperados.
	- Se actualiza el historial de versiones y los cr�ditos
	- Se agregan traducciones del espa�ol al ingles en el historial de versiones
	- Se eliminan archivos obsoletos

 >> Version 1.4.1 - 31-X-2000
  	- InvGaussJordan1: Tercera versi�n de la implementaci�n del
	  algoritmo del c�lculo de la matriz inversa por el m�todo de Gauss-Jordan.
	  Se mejora la forma en la que se realiza el pivoteo de la matriz ampliada.
	- Este algoritmo se crea como un programa independiente llamado "Inversa"
	  y nunca lleg� a ser integrado CMatriz

 >> Version 1.4 - 17-VIII-2000
	- Ya hace mas de un a�o que no actualizaba CMatrix, antes que todo pido
	  disculpas a todos los usuarios que usaron CMatrix 1.3 y no pudieron
	  correr el programa en su PC debido a varios errores de compilaci�n.
	  Esta nueva versi�n supera varios de los errores que ocurr�a en
	  CMatrix 1.3.
	  Pero si vuelve a ocurrir alg�n error, por favor avisarme lo mas
	  r�pido posible.
	- Se agrego una nueva funci�n miembro: IngresarElementos() ;  que ingresa
	  los elementos de la matriz desde el teclado.
	- Se reemplazo todas las entradas y salidas cout<< y cin>> (de iostream.h)
	  por printf y scanf ( de stdio.h ), para que no ocurran errores de
	  compilaci�n en algunos compiladores antiguos.
	- Se agregaron comentarios a las l�neas de C�digo mas importantes.

  >> Version 1.3.1 - 06-VI-1999
	- Se trabajaron algunos programas independientes para:
		* OBTENER DATOS DE UNA MATRIZ
		Este programa suma las columnas y filas de una matriz, tambien
		calcula la suma de los elementos de la diagonal principal y
		la diagonal secundaria.
		* CALCULO DE LA TRANSPUESTA DE UNA MATRIZ
	- Estos programas nunca fueron integrados a la librer�a CMatriz

 >> Version 1.3 - 06-VI-1999
	- Se crea la clase CMatriz, como una clase para hacer algebra de matrices.
	  Trabaja con las matrices como si fueran simples variables.
	- Se implementaron los operadores b�sicos +, -, negativo de una matriz, 
	  * escalar y * matricial
	- Se agregaron InvGaussJordan2, InvCofact e DetCofact como funciones
	  globales, para que se pueda hacer operaciones adicionales entre matrices.

>> Version 0.4 - 28-II-1999
	- InvGaussJordan3: Inicialmente llamado INVRECU (Inversa Recursiva):
	  Segunda versi�n de la implementaci�n del algoritmo del c�lculo de la 
	  matriz inversa por el m�todo de Gauss-Jordan. Se toma como base 
	  InvGaussJordan2, pero se inserta funciones recursivas en reemplazo de 
	  algunos bucles. Esta funci�n calcula la inversa de una matriz con
	  funciones recursivas.

>> Version 0.3 - 28-II-1999
	- InvCofact: Inicialmente llamado SINVERSA (Super Inversa):
	  calcula la inversa de la matriz por el metodo de la transpuesta de
	  de la matriz de cofactores:
	  METODO: A^-1 = (1/|A|) * (C)^t
	  donde C = matiz cofactor de A

>> Version 0.2 - 21-I-1999
	- DetCofact: Inicialmente llamado SDETERM (Super Determinante): Esta rutina
	  calcula con facilidad la determinante de matrices de orden de 10x10.
	  Se utiliza el metodo los cofactores de la matriz (pivoteando).
	  Se utiliza recursividad, por lo que el progrma necesita bastante memoria.

>> Version 0.1 - 21-I-1999
	- InvGaussJordan2: Primera versi�n de la implementaci�n del
	  algoritmo del c�lculo de la matriz inversa por el m�todo de Gauss-Jordan

***********************************************************************************/

#include <vector>

class CMatrix
{
private:
	typedef double ELEMENT;
	typedef std::vector<ELEMENT> ROW;
	typedef std::vector<ROW> MATRIX;

public:
	
	//CONSTRUCTORES
	CMatrix(); //constuye una matriz cuadrada de orden _MAX
	CMatrix(int filas, int columnas); //constructor para matrices no cuadradas	
	CMatrix(int orden); //constructor para matrices cuadradas
	~CMatrix(); //destructor

	//FUNCIONES
/*private:
	void Inicializar(double elemento); //Copia a todos los elementos
					   //de la matriz el valor
					   //de la variable elemento

	void IngresarElementos();//Se ingresan los elementos de la matriz
				 //desde el teclado
	void Escribir(); //Escribe la matriz en pantalla
	*/
public:
	
	//retorna el numero de filas de la matriz
	int Fil() const;
	
	//retorna el numero de columnas de la matriz
	int Col() const;

	//retorna el orden de la matriz en caso de ser una
	// matriz cuadrada y en caso contrario retorna -1
	int Orden() const;

	//DEFINE LAS OPERACIONES ENTRE MATRICES
	friend CMatrix operator -(const CMatrix &A); 		 //operacion -A  NEGATIVO DE UNA MATRIZ
	friend CMatrix operator +(const CMatrix &A, const CMatrix &B); //operaci�n A+B SUMA DE MATRICES
	friend CMatrix operator -(const CMatrix &A, const CMatrix &B); //operaci�n A-B RESTA DE MATRICES
	friend CMatrix operator *(const double& k, const CMatrix &A);  //operaci�n k*B (k es una constante)
	friend CMatrix operator *(const CMatrix &A, const CMatrix &B);//operaci�n A*B (Producto matricial)


	// M�TODOS
private:
	double DetCofact(const CMatrix & A, const int & orden) const;
	
	//Se reduce la matriz por operaciones elementales comenzando por G[0][0]
	//a una matriz triangular superior
	void escalonada(MATRIX& A, const unsigned int& orden, ELEMENT& Determinant, const int & osm) const;

	//Se reduce la matriz triangular superior de la izquierda de G
	//a una matriz identidad
	void inversa(MATRIX & A, const unsigned int & orden, const int & osm) const;
	
	static bool IsZero(const ELEMENT& element);

public:
	CMatrix Transposed() const;
	double DetCofact() const;	
	bool InvCofact(CMatrix& Inverse) const;

	//CALCULA LA INVERSA DE LA MATRIZ POR EL METODO DE REDUCCION GAUSSIANA (M�todo 1)
	// (Este m�todo tambi�n calcula la determinante)
	// A^-1 = { A^-1 ; tal que  G = [ A | I ] = [ I | A^-1 ]  }
	bool InvGaussJordan1(CMatrix & Inverse) const;


	//CALCULA LA INVERSA DE LA MATRIZ POR EL METODO DE REDUCCION GAUSSIANA (M�todo 2)
	// (Este m�todo tambi�n calcula la determinante)
	// A^-1 = { A^-1 ; tal que  G = [ A | I ] = [ I | A^-1 ]  }
	bool InvGaussJordan2(CMatrix& Inverse, ELEMENT& Determinant) const;	


	//CALCULA LA INVERSA DE LA MATRIZ POR EL METODO DE REDUCCION GAUSSIANA (M�todo 2 recursivo)
	// A^-1 = { A^-1 ; tal que  G = [ A | I ] = [ I | A^-1 ]  }
	bool InvGaussJordan3(CMatrix & Inverse, ELEMENT& Determinant) const;

private:
	//VARIABLES MIEMBRO
	int FIL;
	int COL;
	int ORDEN;
public:
	MATRIX Elemento; //Contiene los elementos de la matriz
};

/*
//UN EJEMPLO
void main()
{

 double B[3][3]={-1,-2,3,4,5,6,7,8,9},
	C[3][3]={2,5,7,1,4,2,4,5,9};

 CMatrix M(3),N(3),P(3);//se declaran 3 matrices cuadradas de orden 3

 CMatrix I;//para crear memoria virtual

 //Se asigna los arreglos B y C a las matrices M y N respectivamente
 for(int i=0;i<M.Fil();i++)
  for(int j=0;j<M.Col();j++)
  {
   M.Elemento[i][j]=B[i][j];
   N.Elemento[i][j]=C[i][j];
  }

 clrscr();

 P=( InvGaussJordan1( (Det(M)*N+Det(N)*M) ) )*(120*N);
 I=( InvCofact( (Det(M)*N+Det(N)*M) ) )*(120*N);

 //I=Inv1( M+N );

 I.Escribir(); //Escribe la matriz en pantalla

 M.Escribir(); //Escribe la matriz en pantalla

 P.Escribir(); //Escribe la matriz en pantalla

 getch();
}
  */