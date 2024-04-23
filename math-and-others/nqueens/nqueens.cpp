/****************************************************************************
NREINAS Versi�n 1.9

COMO N REINAS SE PUEDEN DISTRUBUIR EN UN TABLERO DE N*N SIN ATACARSE
CON TODAS LAS SOLUCIONES POSIBLES!!!!

JOSE LUIS DE LA CRUZ LAZARO UNI-FIEE - 26/06/99
ramondc@hotmail.com

NOVEDADES:

-El nuevo algoritmo que utilizo consiste en utilizar permutaciones,
 es decir se sabe que a cada reina le corresponde una fila del tablero de N*N,
 por lo que para hallar todas las soluciones, bastara con permutar las
 filas y en cada permutaci�n verificar si no existe ataque, si se cumple
 lo anterior la posicion actual de las reinas es una soluci�n.

-La funcion Nreinas se encarga de permutar las reinas, utilizando
 recursividad y utilizando 2 "aceleradores", que seleccionan las permutaciones
 con elementos no repetidos acelerando asi el proceso maravillosamente.
 A diferencia de la version anterior que para 8 reinas se demoraba 15 minutos
 ahora lo hace en 52 segundos (sin pausas)

*****************************************************************************/

#include <iostream>
#include <iomanip>

using std::cout;
using std::cin;

int pos[15], solucion = 1;

//Halla una posicion donde ninguna reina se ataque
int pos_sin_ataque(int &N)
{
	for (int i = 0; i < N - 1; i++)
		for (int r = i + 1; r < N; r++)
		{
			if (i == r || pos[i] == pos[r]) return 0;
			if (abs(i - r) == abs(pos[i] - pos[r])) return 0;
		}
	return 1;
}

//Existe una solucion y se la muestra en pantalla
void Mostrar_Solucion(int &N)
{
	int x, y;
	cout << std::endl << std::endl << "Solution " << solucion++ << ":" << std::endl;


	for (x = 0; x < N; x++)
	{
		//se muestra la posicion de las reinas
		cout << "fil(" << x + 1 << "),col(" << pos[x] + 1 << ") ";

		for (y = 0; y < N; y++) {
			//se muestra los casilleros del tablero
			// 0 si est� vac�o � * si lleva una reina
			cout << std::setfill(' ') << std::setw(2) << (y == pos[x] ? "*" : "0");
		}

		cout << std::endl;

	}
}

int norepet(int &n)
{
	for (int r = 0; r < n - 1; r++)
		for (int s = r + 1; s < n; s++)
			if (pos[r] == pos[s]) return 0;

	return 1;
}

//Calcula las permutaciones
void Nreinas(int &N, int iter)
{
	int k, i;

	for (i = 0; i < N; i++)
	{
		pos[iter] = i;

		if (norepet(iter)) //acelerador #1 de la permutacion
		{
			if (iter < N - 1) Nreinas(N, iter + 1);
			else
			{
				if (norepet(N)) //acelerador #2 de la permutacion
					if (pos_sin_ataque(N)) Mostrar_Solucion(N);
			}
		}
	}
}


void main()
{


	int N;
	cout << ":: N-ROOTS ::" << std::endl << std::endl;
	cout << "Enter the number of queens: ";
	cin >> N;

	cout << std::endl << std::endl;
	cout << N << "x" << N << " Chessboard" << std::endl;
	
	Nreinas(N, 0);

	/*************************************************
	NUMERO DE SOLUCIONES HASTA N=9
	#N (Reinas)  #Soluciones
		 4       2
		 5	     10
		 7 	     40
		 8	     92		****La m�s solicitada****
		 9 	     352
		 10				****me cans� de ver tantas****
	**************************************************/
}