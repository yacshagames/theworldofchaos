//
// solu0016.cpp program. // Tested in TC and BC.
//
// Solution to challenge 16, created by Antonio Gonzalez for C World.
//
// Author: Fabian Silva Pavez (CHILE), especially for the challenge.
//
//
// Operation: Select the order and see the magic square in
// C:\CUADRADO.TXT, I did it like this because the screen limits up to 80x50.
//
//

#include <iostream>
#include <fstream>
#include <iomanip>
using std::cout;
using std::cin;
using std::endl;

class Cuadrado {
	int **Cuad;             // The magic square
	int	n,                  // Order of the square
		Cifras;             // Number of digits of the largest number in the square
public:
	Cuadrado(int N);       // Constructor, only allocates memory
	~Cuadrado();            // Destructor, frees the memory
	void Procesar();        // Generate the magic square
	void Listar();          // List the square in the file
};

Cuadrado::Cuadrado(int N) {
	n = N;
	Cuad = new int*[n];
	for (int i = 0; i < n; i++)
		Cuad[i] = new int[n];
};

Cuadrado::~Cuadrado() {
	for (int i = 0; i < n; i++)
		delete Cuad[i];
	delete Cuad;
};

void Cuadrado::Procesar() {
	int i = 0, j, X, Y;
	X = n * n;                  // n^2 is the largest number, it is used for
	while (X) {					// know how many spaces are skipped
		X /= 10;				// between each number in the square to the file
		i++;
	};
	Cifras = i;					// Number of digits
	for (i = 0; i < n; i++)     // Move forward by row
	{
		X = (n / 2 + i) % n;	// See algorithm at the end of this file.
		Y = (X + 1) % n;
		for (j = 0; j < n; j++)
			Cuad[(X - j + n) % n][(Y + j) % n] = i * n + j + 1;
	};
};
void Cuadrado::Listar() {
	int i, j;

	std::ofstream f("square.txt", std::ofstream::out);	

	f << "Magic Square side" << n << ", Sum = " << n * (n*n + 1) / 2 << endl;
	f << "------------------------" << endl;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++)
			f << std::setfill(' ') << std::setw(Cifras + 1) << Cuad[i][j];
		f << endl;
	};
	f.close();
};

int main ()
{
	unsigned int orden;
	Cuadrado *c;

	cout << "Enter a positive number n (n > 2, and n is odd): ";
	cin >> orden;

	if (orden > 2 && orden % 2)
	{
		c = new Cuadrado(orden);
		c->Procesar();
		c->Listar();
		cout << "The magic square of order " << orden;
		cout << " is located in square.txt.";
	}
	else
		cout << "The number " << orden << " is not > 2 or is not odd.";
	//asm{ mov ah, 7; int 21h; }; // pause-diddly
	return 0;
};

/* ALGORITHM:

For n == 5

1. Empty Magnitude Square

				███████████████████████████
				██   ██   ██   ██   ██   ██
				███████████████████████████
				██   ██   ██   ██   ██   ██
				███████████████████████████
				██   ██   ██   ██   ██   ██
				███████████████████████████
				██   ██   ██   ██   ██   ██
				███████████████████████████
				██   ██   ██   ██   ██   ██
				███████████████████████████


2. Generate the following square extensions.
3. Write the numbers in stepwise form, as shown.

						  ▒▒▒▒▒▒▒
						  ▒▒ 5 ▒▒
					 ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
					 ▒▒ 4 ▒▒   ▒▒ 10▒▒
				███████████████████████████
				██ 3 ██   ██ 9 ██   ██ 16██
		   ▒▒▒▒▒███████████████████████████▒▒▒▒▒
		   ▒▒ 2 ██   ██ 8 ██   ██ 15██   ██ 21▒▒
	  ▒▒▒▒▒▒▒▒▒▒███████████████████████████▒▒▒▒▒▒▒▒▒▒
	  ▒▒ 1 ▒▒   ██ 7 ██   ██ 13██   ██ 20██   ▒▒ 25▒▒
	  ▒▒▒▒▒▒▒▒▒▒███████████████████████████▒▒▒▒▒▒▒▒▒▒
		   ▒▒ 6 ██   ██ 12██   ██ 19██   ██ 24▒▒
		   ▒▒▒▒▒███████████████████████████▒▒▒▒▒
				██ 11██   ██ 18██   ██ 23██
				███████████████████████████
					 ▒▒ 17▒▒   ▒▒ 22▒▒
					 ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
						  ▒▒ 21▒▒
						  ▒▒▒▒▒▒▒
						  
4. Move the extensions to their opposite side,
   for example the left extension

						  ▒▒▒▒▒▒▒
						  ▒▒ 5 ▒▒
					 ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
					 ▒▒ 4 ▒▒   ▒▒ 10▒▒
				███████████████████████████
				██ 3 ██   ██ 9 ██   ██ 16██
				████████████████████▓▓▓▓▓▓▓▒▒▒▒▒
				██   ██ 8 ██   ██ 15▓▓ 2 ▓▓ 21▒▒
				███████████████▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒
				██ 7 ██   ██ 13▓▓ 1 ▓▓ 20▓▓   ▒▒ 25▒▒
				███████████████▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒
				██   ██ 12██   ██ 19▓▓ 6 ▓▓ 24▒▒
				████████████████████▓▓▓▓▓▓▓▒▒▒▒▒
				██ 11██   ██ 18██   ██ 23██
				███████████████████████████
					 ▒▒ 17▒▒   ▒▒ 22▒▒
					 ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒
						  ▒▒ 21▒▒
						  ▒▒▒▒▒▒▒

5. And so on, until the square is complete.

To find the sequence I did:

N°| Position
------------
1 : (2,3)                          = (5/2, 5/2+1)
2 : (1,4) = ( (2-1+5)%5, (3+1)%5 )
3 : (0,0) = ( (2-2+5)%5, (3+2)%5 )
4 : (4,1) = ( (2-3+5)%5, (3+3)%5 )
5 : (3,2) = ( (2-4+5)%5, (3+4)%5 )
6 : (3,4) =                        = ( (2+1)%5, (3+1)%5 )
7 : (2,0) = ( (3-1+5)%5, (4+1)%5 )
8 : (1,1) = ( (3-2+5)%5, (4+2)%5 )
9 : (0,2) = ( (3-3+5)%5, (4+3)%5 )
10: (4,3) = ( (3-4+5)%5, (4+4)%5 )
11: (4,0)                          = ( (2+2)%5, (3+2)%5 )
12: (3,1) = ( (4-1+5)%5, (0+1)%5 )
13: (2,2) = ( (4-2+5)%5, (0+2)%5 )
14: (1,3) = ( (4-3+5)%5, (0+3)%5 )
15: (0,4) = ( (4-4+5)%5, (0+4)%5 )
16: (0,1)                          = ( (2+3)%5, (3+3)%5 )
17: (4,2) = ( (0-1+5)%5, (1+1)%5 )
18: (3,3) = ( (0-2+5)%5, (1+2)%5 )
19: (2,4) = ( (0-3+5)%5, (1+3)%5 )
20: (1,0) = ( (0-4+5)%5, (1+4)%5 )
21: (1,2)                          = ( (2+4)%5, (3+4)%5 )
22: (0,3) = ( (1-1+5)%5, (2+1)%5 )
23: (4,4) = ( (1-2+5)%5, (2+2)%5 )
24: (3,0) = ( (1-3+5)%5, (2+3)%5 )
25: (2,1) = ( (1-4+5)%5, (2+4)%5 )

*/