/****************************************************************************
NREINAS Versi¢n 1.9

COMO N REINAS SE PUEDEN DISTRUBUIR EN UN TABLERO DE N*N SIN ATACARSE
CON TODAS LAS SOLUCIONES POSIBLES!!!!

JOSE LUIS DE LA CRUZ LAZARO UNI-FIEE - 26/06/99
ramondc@hotmail.com

NOVEDADES:

-El nuevo algoritmo que utilizo consiste en utilizar permutaciones,
 es decir se sabe que a cada reina le corresponde una fila del tablero de N*N,
 por lo que para hallar todas las soluciones, bastara con permutar las
 filas y en cada permutaci¢n verificar si no existe ataque, si se cumple
 lo anterior la posicion actual de las reinas es una soluci¢n.

-La funcion Nreinas se encarga de permutar las reinas, utilizando
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
int pos_sin_ataque(const unsigned int &N)
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
	unsigned int k, i;

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


int main()
{
	unsigned int i, N, num_solutions;

	cout << ":: N-ROOTS ::" << std::endl << std::endl;
	cout << "Enter the number of queens: ";
	cin >> N;

	cout << std::endl << std::endl;
	cout << N << "x" << N << " Chessboard" << std::endl;
	
	pos.resize(N);
	
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
	for (i = 0; i < num_solutions;i++) 
		Mostrar_Solucion(i + 1, vSolutions[i]);

	/*************************************************
	NUMERO DE SOLUCIONES HASTA N=9
	#N (Reinas)  #Soluciones
		 4       2
		 5	     10
		 7 	     40
		 8	     92		****La más solicitada****
		 9 	     352
		 10				****me cansé de ver tantas****
	**************************************************/

	return 1;
}