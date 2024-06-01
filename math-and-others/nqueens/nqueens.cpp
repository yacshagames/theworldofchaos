/****************************************************************************
:: NQUEENS :: NREINAS :: 

How can N queens be distributed on an N*N board without attacking each other?
This program shows all the possible solutions. A solution with the
backtraking algorithm and another algorithm using optimized brute force

¿Como N reinas se pueden distrubuir en un tablero de N*N sin atacarse?, 
este programa muestra todas las soluciones posibles. Una solución con el
algoritmo de backtraking y otro algoritmo usando fuerza bruta optimizada


 Developed by:

	JOSE LUIS DE LA CRUZ LAZARO
	ramondc@hotmail.com

	UNIVERSIDAD NACIONAL DE INGENIERIA
	Faculty of Electrical and Electronic Engineering
	Lima-Peru

	YACSHA - Software & Desing
	>> The World of chaos - EL MUNDO DEL CAOS - Unlimited Programming

HISTORY...

  >> Version 2 - 23-IV-2024
	- The code is updated to the new C++ 17 standard
	- Std::setfill and std::setw are used instead of the old gotoxy, to make
	  the code more portable. In such a way that conio.h is dispensed with
	- Pauses are no longer inserted after showing each solution
	- Function parameters are ordered to constants, to indicate that the
	  variables passed as reference parameters will not be modified
	- Now the solutions found are saved in a vector, to show them later. In	  
	  this way it will be possible to measure the time it takes for the
	  algorithm just to find the solutions.
	- Addons.h is included to measure the time it takes for the algorithm to
	  find the solutions, and then display this time on the screen.
	- A pause is placed before showing the solutions or the option to exit
	  the program is given
	- The credits and version history are updated
	- The credits and history are partially translated from Spanish to English
	- A more optimized solution is added using the backtraking algorithm, in
      order to compare the time vs the optimized brute force algorithm. The
	  times, number of solutions and solution report of each algorithm are
	  shown separately, so that they can be compared face to face.
	- RESULTS:
	  - For 8 queens the following results were obtained:
		- With the 1999 average performance CPU it took 52 seconds with the
		  "optimized brute force" algorithm.
		- With an average performance CPU of 2024 it takes 0.03 seconds and
		  0.0003 seconds, with the "backtraking" and "optimized brute force"
		  algorithms respectively.
	  - For 11 queens and with an average performance CPU of 2024:
	    it took 0.03 seconds and 79 seconds, with the  with the "backtraking"
		and "optimized brute force" algorithms respectively.
	  - For 15 queens and with an average performance CPU of 2024:
	    It took 45.52 seconds, with the "backtraking" algorithm.

  >> Version 1.9 - 26-VI-1999
	- First version for Borland C++ 3.1 and Turbo C 3.0
	- El nuevo algoritmo que utilizo consiste en utilizar permutaciones,
	  es decir se sabe que a cada reina le corresponde una fila del tablero de N*N,
	  por lo que para hallar todas las soluciones, bastara con permutar las
	  filas y en cada permutacion verificar si no existe ataque, si se cumple
	  lo anterior la posicion actual de las reinas es una solucion.
	- La funcion Nreinas se encarga de permutar las reinas, utilizando
	  recursividad y utilizando 2 "aceleradores", que seleccionan las permutaciones
	  con elementos no repetidos acelerando asi el proceso maravillosamente.
	  A diferencia de la version anterior que para 8 reinas se demoraba 15 minutos
	  ahora lo hace en 52 segundos (sin pausas)

*****************************************************************************/

#include <iostream>
#include <iomanip>
#include <vector>
#include "AddOns.h"

using std::cout;
using std::cin;

std::vector<int> pos;
std::vector<std::vector<int>> vSolutions;

//Halla una posicion donde ninguna reina se ataque
int pos_sin_ataque(const int &N)
{
	for (int i = 0; i < N - 1; i++)
		for (int r = i + 1; r < N; r++)
		{
			if (i == r || pos[i] == pos[r])
				return 0;

			if (std::abs(i - r) == std::abs(pos[i] - pos[r]))
				return 0;
		}
	return 1;
}

//Existe una solucion y se la muestra en pantalla
void Mostrar_Solucion(const unsigned int& solution, const std::vector<int>& pos_solution)
{
	unsigned int x, y, N = static_cast<unsigned int>(pos_solution.size());

	cout << std::endl << std::endl << "Solution " << solution << ":" << std::endl;

	for (x = 0; x < N; x++)
	{
		//se muestra la posicion de las reinas
		cout << "fil(" << x + 1 << "),col(" << pos_solution[x] + 1 << ") ";

		for (y = 0; y < N; y++) {
			//se muestra los casilleros del tablero
			// 0 si está vacío ó * si lleva una reina
			cout << std::setfill(' ') << std::setw(2) << (y == pos_solution[x] ? "*" : "0");
		}

		cout << std::endl;

	}
}

int norepet(const int &n)
{
	for (int r = 0; r < n - 1; r++)
		for (int s = r + 1; s < n; s++)
			if (pos[r] == pos[s])
				return 0;

	return 1;
}

//Calcula las permutaciones
void Nreinas(const unsigned int &N, const unsigned int& iter)
{
	unsigned int i;

	for (i = 0; i < N; i++)
	{
		pos[iter] = i;

		if (norepet(iter)) //acelerador #1 de la permutacion
		{
			if (iter < N - 1)
				Nreinas(N, iter + 1);
			else
			{
				if (norepet(N)) //acelerador #2 de la permutacion
					if (pos_sin_ataque(N)) {
						vSolutions.push_back(pos);
						//Mostrar_Solucion(N);
					}
			}
		}
	}
}

std::vector<std::vector<bool>> Board;
unsigned int back_solutions = 0;
std::vector<int> back_pos;
std::vector<std::vector<int>> vBackSolutions;

bool back_check(const int& r, const int& c, const int& N ) {

	int i;

	for (i = 0; i < r; i++) {
		
		if (Board[i][c] == true)
			return false;
		
		if (c - i - 1 >= 0 && Board[r - i - 1][c - i - 1] == true)
			return false;
		
		if( c + i + 1 < N && Board[r - i - 1][c + i + 1] == true )
			return false;
	}

	return true;
}


void back(const int& N, const int& r) {

	if (r == N) {

		// Se encontró solución
		back_solutions++;

		// Guarda solución
		int i, j;

		for (i = 0; i < N; i++) 
			for (j = 0; j < N; j++) {
				if (Board[i][j]) {
					back_pos[i] = j;
					break;
				}
			}

		vBackSolutions.push_back(back_pos);

		return;
	}

	int i;

	for (i = 0; i < N; i++) {

		if (back_check(r, i, N) == false)
			continue;

		Board[r][i] = true;
		back(N, r + 1);
		Board[r][i] = false;
	}
}

int main()
{
	unsigned int i, N, num_solutions;

	cout << ":: N-QUEENS :: NREINAS ::" << std::endl << std::endl;
	cout << "Enter the number of queens: ";
	cin >> N;

	cout << std::endl << std::endl;
	cout << N << "x" << N << " Chessboard" << std::endl << std::endl;;

	// Backtraking algorithm
	back_pos.resize(N);

	Board.resize(N, std::vector<bool>(N));

	cout << "Backtraking algorithm: ";

	AddOns::chronoStart(); // Init chronometer	

	back(N, 0);

	AddOns::chronoEnd(); // End chronometer and show elapsed time

	cout << back_solutions << " solutions found." << std::endl << std::endl;
		
	// Optimized brute force	
	pos.resize(N);

	cout << "Optimized brute force: ";

	AddOns::chronoStart(); // Init chronometer	
	
	Nreinas(N, 0);
	
	AddOns::chronoEnd(); // End chronometer and show elapsed time

	num_solutions = static_cast<unsigned int>(vSolutions.size());
	cout << num_solutions << " solutions found." << std::endl << std::endl;

	unsigned int p;
	cout << "Enter 1 to show solutions or 0 to exit: ";
	cin >> p;


	if (p == 0)
		return 1;

	// Show all solutions

	cout << std::endl << std::endl << "Backtraking solutions: " << std::endl;
	for (i = 0; i < back_solutions; i++)
		Mostrar_Solucion(i + 1, vBackSolutions[i]);

	cout << std::endl << std::endl << "Optimized brute force solutions: " << std::endl;
	
	for (i = 0; i < num_solutions; i++)
		Mostrar_Solucion(i + 1, vSolutions[i]);


	/*************************************************************************************************************************
	NUMBER OF SOLUTIONS UP TO N=15
	#N (Queens)  #Solutions time   time
	                        BruteF BackT
							  CPU 2024
		 4       2
		 5	     10
		 7 	     40
		 8	     92		    0.03s 0.0003s ****The most requested****
		 9 	     352
		 10		 724					  ****In 1999 with a average performance CPU I got tired of seeing so many brute forces ****
		 11     2680		  79s  0.03s
		 12	   14200			   0.17s
		 13    73712			   1.01s
		 14   365596			   6.60s
		 15  2279184			  45.52s
	*************************************************************************************************************************/

	return 1;
}