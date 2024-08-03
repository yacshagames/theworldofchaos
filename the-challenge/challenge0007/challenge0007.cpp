/****************************************************************************
Challenge 007 - 22-IX-2000
created by: Jose Luis De la Cruz Lazaro
			contact@theworldofchaos.com
			www.theworldofchaos.com

This program is a recreation of a problem I had some time ago.

The objective is to add 2 matrices by means of a function Sum, where the matrices are two-dimensional arrays created dynamically and their order is entered from the keyboard.

But it turns out that the program does not show errors when compiling, maybe some warnings, but at the moment of executing the exe, some of the following cases happen:

- The program hangs from the start;
- It shows well the result, but at the end it hangs;
- It shows the result well, but at the end it shows the error message: Null pointer assignment.
-  The program displays the result well, but only for small order matrices;

Questions
1st. Find where the error is and explain why it crashes. You do not want to give the solution for a specific compiler, I say this, because your solution can run in DJGPP, but not in Borland C. What you want is that the solution is general.

2nd. Modify the program in such a way that you can add the 2 matrices more efficiently.

3rd. Up to what order (of the matrices), could the program work well, without crashing due to lack of memory? Explain why.

It must be fulfilled that the solution of question 1 must agree with what is said in question 3.

       o  o Jose Luis De la Cruz Lazaro o   220KV of Chaos
     o       o  Visit my homepage:          o      o
   o    o o    o THE WORLD OF CHAOS           o   o o
  o   o  o     o   https://www.theworldofchaos.com   o  o
  o    o     o                                   o    o  o
   o     o o     Chaos = Chaos & math ? C++ : ++C;        o
     o                                                     o
        o  o  o o o  FRACTALS UNLIMITED ooo o  o  o  o  o   o
                    o  o   o   o   o   o
     o               o   o   o   o   o
   o   o      o
 o      o   o  o  o  o  o o oooo      Yacsha Software & Desing
                                 O  O  o ooo Lima - Peru ooo o o O  O

****************************************************************************/

#include <iostream>
#include <time.h>
using std::cout;
using std::cin;

//Assigns memory to a double pointer A
void CreateMatrix(int **A, int Order);

//Destroys the square matrix created with CreateMatrix
void DestroyMatrix(int **A, int Order);

//Returns the sum matrix of A and B
int **Sum(int **A, int **B, int Order);

//Displays the matrix A
void ShowMatrix(int **A, int Orden);

int main()
{

	//2 double pointers, will be used to create 2 dynamic two-dimensional arrays
	int **a, **b;

	int i, j;

	int N;

	cout << "\n\nEnter the order of the arrays: ";
	cin >> N;

	CreateMatrix(a, N); //a MATRIX of order N is created dynamically
	CreateMatrix(b, N); //a MATRIX of order N is created dynamically

	srand(time(NULL)); //Initializes the random number generator, 
					   //dependent on the current time

	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
		{
			a[i][j] = rand() % 10; // a and b contain natural numbers less than 10
			b[i][j] = rand() % 10;
		}

	cout << "\nContents of array A:\n";
	ShowMatrix(a, N); //displays array A

	cout << "\n\nContents of array B:\n";
	ShowMatrix(b, N); //displays array B

	Sum(a, b, N);	//executes the sum function and assigns the result to the
					//array a

	cout << "\n\nThe matrix sum of A and B is:\n";
	ShowMatrix(a, N); //displays the sum A+B

	DestroyMatrix(a, N); //destroys A
	DestroyMatrix(b, N); //destroys B

	return 0;
}

void CreateMatrix(int **A, int Orden)
{
	for (int i = 0; i < Orden; i++)
		A[i] = new int[Orden];
}

void DestroyMatrix(int **A, int Orden)
{
	for (int i = 0; i < Orden; i++)
		delete A[i];
}

int **Sum(int **A, int **B, int Orden)
{
	int **C, i, j;

	CreateMatrix(C, Orden);

	for (i = 0; i < Orden; i++)
		for (j = 0; j < Orden; j++)
			C[i][j] = A[i][j] + B[i][j];

	return C;
}

void ShowMatrix(int **A, int Orden)
{
	int i, j;

	for (i = 0; i < Orden; i++)
	{
		cout << "\n";
		for (j = 0; j < Orden; j++)
			cout << A[i][j] << " ";
	}
}





