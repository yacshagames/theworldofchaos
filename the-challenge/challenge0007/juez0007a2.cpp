/****************************************************************************
SOLUTION 2 to Challenge 007 (OPTIMIZATION)
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

struct Matriz
{
	int *elemento; //pointer to array elements
};

//Assigns memory to a double pointer A
int CreateMatrix(Matriz &A, unsigned Order);

//Destroys the square matrix created with CreateMatrix
void DestroyMatrix(Matriz &A);

//Returns the sum matrix of A and B
void Sum(Matriz &A, Matriz &B, unsigned Order);

//Shows the array A
void ShowMatrix(Matriz &A, unsigned Order);

int main()
{
	//2 double pointers, will be used to create 2 two-dimensional arrays
	//dynamic
	Matriz a, b;

	int i, j;
	int N;

	cout << "\n\nEnter the order of the matrices: ";
	cin >> N;

	if (!CreateMatrix(a, N)) return 1; //dynamically creates a MATRIX of order N
	if (!CreateMatrix(b, N)) return 1; //dynamically creates a MATRIX of order N

	srand(time(NULL)); //Initializes the random number generator,
						//dependent on the current time

	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
		{
			a.elemento[j*N + i] = rand() % 10; // a and b contain natural numbers less than 10
			b.elemento[j*N + i] = rand() % 10;
		}

	cout << "\nContents of matrix A:\n";
	ShowMatrix(a, N); //show matrix A

	cout << "\n\nContents of matrix B:\n";
	ShowMatrix(b, N); //show matrix B

	Sum(a, b, N); //execute the sum function and assign the result to the
	//matrix a

	cout << "\n\nThe matrix sum of A and B is:\n";
	ShowMatrix(a, N); //show the sum A+B

	DestroyMatrix(a); //destroy A
	DestroyMatrix(b); //destroy B

	return 0;

}

int CreateMatrix(Matriz &A, unsigned Orden)
{

	if ((A.elemento = new int[Orden*Orden]) == NULL)
	{
		cout << "\no memory to create array...";
		return 0;
	}

	return 1;
}

void DestroyMatrix(Matriz &A)
{
	delete A.elemento;
}

void Sum(Matriz &A, Matriz &B, unsigned Orden)
{

	unsigned i, N = Orden * Orden;

	for (i = 0; i < N; i++)
		A.elemento[i] = A.elemento[i] + B.elemento[i];

}

void ShowMatrix(Matriz &A, unsigned Orden)
{
	unsigned i, N = Orden * Orden;

	for (i = 0; i < N; i++)
	{
		if (i%Orden == 0) cout << "\n";
		cout << A.elemento[i] << " ";
	}
}





