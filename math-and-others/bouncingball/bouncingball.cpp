/***********************************************************************
 ::: BOUNCING BALLS - PELOTAS REBOTANDO:::

 A simple example of OOP (Object Oriented Programming), in which
 like some balls bouncing on the limits of our screen in
 text mode.

 Un ejemplo simple de POO (Programación Orientada a objetos), en el
 cual unas pelotas rebotan en los límites de nuestra pantalla en
 modo texto.

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

 >> Version 2 - 24-IV-2024
	- Update math-and-others\bouncingball - Porting to VC++ 2017
	- Change project name from Pelota to boincingball
	- The code is updated to the new C++ 17 standard
	- Add conio.h library compatible with VC++17 (WinBGI)
	- The new standard std::random_device library is now used using a
	  mt19937_64 generator and an integer uniform random distribution.
	  This replaces the old, non-standard turbo C random function.
	- A small GUI is added to enter the number of balls that will
	  bounce simultaneously, for which std::vector is used to
	  dynamically define the number of Ball objects created
	- The program is translated from Spanish to English.
	- The credits and version history are updated

 >> Version 1.0 - 28-XI-2000
	- First version for Borland C++ 3.1 and Turbo C 3.0

***********************************************************************/

#include <iostream>
#include "conio.h" // gotoxy
#include <conio.h> // _kbhit
#include <vector>
#include <random>

using std::cout;
using std::cin;

class Ball
{
public:

	int X, Y;
	int dx, dy;

	Ball();
	Ball(int x, int y);

	void Move();

};

Ball::Ball()
{
	X = 40;
	Y = 12;
	dx = 1;
	dy = 1;
}

Ball::Ball(int x, int y)
{
	X = x;
	Y = y;
	dx = 1;
	dy = 1;
}

void Ball::Move()
{
	if (X == 80) 
		dx = -1;

	if (X == 1)
		dx = 1;

	if (Y == 25)
		dy = -1;

	if (Y == 1)
		dy = 1;

	// clear old ball position
	// With this line it is not necessary to call clrscr() after moving all the balls
	gotoxy(X, Y);
	cout << ' ';

	X += dx;
	Y += dy;

	// draw new ball position
	gotoxy(X, Y);
	cout << 'O';

}

int main()
{
	unsigned int i, num_balls;

	cout << "::: BOUNCING BALLS - PELOTAS REBOTANDO:::" << std::endl << std::endl;

	cout << "Enter number balls: ";

	cin >> num_balls;

	// Initialize the random device and the standard generator mt19937_64
	std::random_device rd;
	std::mt19937_64 gen(rd());

	// Creates uniform random distributions for a range of integers
	std::uniform_int_distribution<int> random1(1, 80), random2(1,25), random3(0,1);

	std::vector<Ball> ball(num_balls);

	for (i = 0; i < num_balls; i++)
	{
		ball[i].X = random1(gen);	// random range from 1 to 80
		ball[i].Y = random2(gen);	// random range from 1 to 25
		ball[i].dx = random3(gen)==0 ? -1 : 1;	// random -1 or 1
		ball[i].dy = random3(gen)==0 ? -1 : 1;	// random -1 or 1
	}

	// Clean screen before show balls
	clrscr();

	while (_kbhit()==false)
	{		
		// Pause 100 miliseconds
		//delay(100);
		Sleep(100);

		// Clear screen before moves
		//clrscr();

		for (i = 0; i < num_balls; i++)
			ball[i].Move();
	}

	return 1;

}
