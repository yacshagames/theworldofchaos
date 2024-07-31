/****************************************************************************
SOLUTION 1 to Challenge 007
Solved on October 11, 2000
****************************************************************************
ORIGINAL STATEMENT:

Challenge 007
created by: Jose Luis De la Cruz Lazaro
			contact@theworldofchaos.com
			www.theworldofchaos.com
Date: September 22, 2000

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
said in question 3.

****************************************************************************/

#include <iostream>
#include <time.h>
using std::cout;
using std::cin;

const int MAX = 126; //Defines the maximum order of the matrices

//Assigns memory to a double pointer A
int CreateMatrix(int **A, int Order);

//Destroys the square matrix created with CreateMatrix
void DestroyMatrix(int **A, int Order);

//Returns the sum matrix of A and B
void Sum(int **A, int **B, int Order);

//Displays the matrix A
void ShowMatrix(int **A, int Orden);

int main()
{
	//2 double pointers, will be used to create 2 dynamic two-dimensional arrays
	int *a[MAX], *b[MAX];
	int i, j;
	int N;

	cout << "\n\nEnter the order of the arrays: ";
	cin >> N;

	if (!CreateMatrix(a, N)) return 1; //a MATRIX of order N is created dynamically
	if (!CreateMatrix(b, N)) return 1; //a MATRIX of order N is created dynamically

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

int CreateMatrix(int **A, int Orden)
{
	for (int i = 0; i < Orden; i++)
	{
		A[i] = new int[Orden];
		if (A[i] == NULL || Orden > MAX)
		{
			cout << "\no memory to create array...";
			return 0;
		}
	}

	return 1;

}

void DestroyMatrix(int **A, int Orden)
{
	for (int i = 0; i < Orden; i++)
		delete A[i];
}

void Sum(int **A, int **B, int Orden)
{
	int i, j;

	for (i = 0; i < Orden; i++)
		for (j = 0; j < Orden; j++)
			A[i][j] = A[i][j] + B[i][j];
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





