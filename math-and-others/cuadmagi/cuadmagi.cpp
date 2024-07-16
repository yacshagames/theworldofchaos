/***********************************************************************
 :::SUDOKU - CUADRADOS MAGICOS:::

 Solution to the classic mathematical problem of the magic square
 (odd order).
 For those who do not know what it is, you have to place the first n
 natural numbers (odd n) in an nxn matrix in such a way that the sum of
 any row, column or diagonal must always be the same.

 Example:

 Magic Square of order 3:

 8 1 6
 3 5 7
 4 9 2

 Sum = 15

 >> GENERAL ALGORITHM

 A way to easily construct magic squares of odd order.

1. Let's take any arithmetic series, for convenience the series of natural
   numbers, and place the number 1 in the central cell of the top row.
2. The figure consecutive to any one must be placed in the cell that
   follows it diagonally up and to the right.
3. If by doing this you leave the square at the upper limit of its contour,
   we will jump to the cell of the next column to the right and in its lower
   row, if you leave it to the right, you continue through the first cell,
   starting from the left, from the top row.
4. When the next cell is occupied, the consecutive number in the series is
   placed in the cell immediately below that of the preceding number, thus
   beginning a new path in the diagonal direction.
 
 Solución al clásico problema matemático del cuadrado mágico (orden impar).
 Para los que no saben de que trata, se tiene que ubicar los n primeros
 numeros naturales (n impar) en una matriz de nxn de tal forma que la
 suma de cualquier fila, columna o diagonal debe ser siempre la misma.

 Ejemplo:

 Cuadrado Mágico de orden 3 :

 8 1 6
 3 5 7
 4 9 2

 Suma = 15

  >> ALGORITMO GENERAL

 Un modo de construir fácilmente cuadrados mágicos de orden impar.

1. Tomemos una serie aritmética cualquiera, para mayor comodidad la
   serie de los números naturales, y coloquemos el número 1 en la
   celda central de la fila superior.
2. La cifra consecutiva a una cualquiera debe colocarse en la celda
   que le sigue diagonalmente hacia arriba y hacia la derecha.
3. Si al hacer esto se sale del cuadrado por el límite superior del
   contorno del mismo, saltaremos a la celda de la columna siguiente
   hacia la derecha y en su fila inferior, si se sale por la derecha,
   se sigue por la primera celda, a partir de la izquierda, de la fila
   superior.
4. Cuando la celda siguiente está ocupada, el número consecutivo de la
   serie se coloca en la celda inmediatamente inferior a la del número
   precedente, comenzando así un nuevo camino en la dirección de la
   diagonal.

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


  >> Version 3 - 21-IV-2024
	- Use setfill(' ') setw(4) in cout, to replace the old printf("%4d")
	  and display the matrices arranged symmetrically by rows and columns

 >> Version 2 - 19-IV-2024
	- Update math-and-others\cuadmagi - Porting to VC++ 2017

>> Version 1 - 17-IV-2001
	- First version for Borland C++ 3.1 and Turbo C 3.0

***********************************************************************/

//Códificación basada en el algoritmo anterior

#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::cin;

//limitar rango ( limita los valores de x al rango [0, N] )
#define lr( x, N ) ( (x)<0 ? N+(x)%N : ( (x)>=N ? (x)%N : (x) ) )

int main()
{
	int cuadrado[17][17], x, y, n, N;

	//restricción del orden a los impares entre 3 y 17, por motivos
	//de dar mayor facilidad para entender el código
	do {

		cout << "\nIngrese el orden ( impar entre 3 y 17 ): ";
		cin >> N;

	} while (!(N % 2));

	cout << endl << "SUDOKU - Cuadrado Magico de orden "<< N << " x " << N << " :" << endl << endl;

	//Se inicia los elementos del cuadrado mágico con ceros
	for (x = 0; x < N; x++)
		for (y = 0; y < N; y++)
			cuadrado[x][y] = 0;

	//Se aplica el algoritmo general para obtener cuadrados mágicos
	//de orden impar
	for (x = N / 2, y = 0, n = 1; n <= N * N; ) //se hace N*N iteraciones...
		if (!cuadrado[x][y])  //si el elemento seleccionado es cero
			cuadrado[x][y] = n++, //se inserta un número natural
			x = lr(x + 1, N),          //se incrementa x en 1
			y = lr(y - 1, N);          //se decrementa y en 1
		else x = lr(x - 1, N),      //se decrementa x en 1
			y = lr(y + 2, N);      //se incrementa y en 2

	  //se imprime el cuadrado mágico en pantalla
	for (y = 0; y < N; y++)
	{
		cout << endl;
		for (x = 0; x < N; x++)
			//printf("%4i", cuadrado[x][y]);
			cout << std::setfill(' ') << std::setw(4) << cuadrado[x][y];
	}

	cout << endl << endl << "Suma = " << (N*(N*N + 1)) / 2 << endl << endl;

	return 1;
}
