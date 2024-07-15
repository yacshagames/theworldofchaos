#pragma once
/****************************************************************
CONIO.H
Old Borland C++ and Turbo C functions. Not Standard

The code of this library has been programmed by different authors,
to whom I thank. I have only been in charge of organizing and
grouping these functions in this library.

Developed by:

	JOSE LUIS DE LA CRUZ LAZARO
	contact@theworldofchaos.com

	YACSHA - Software & Desing, since 1999, Lima-Peru
	>> The World of chaos - EL MUNDO DEL CAOS - Unlimited Programming
	www.theworldofchaos.com

HISTORY...

Version 3 - 01-IV-2024
- wherex, wherey, textcolor, cgetch and ckbhit functions are added
- Comments are added to the declaration of each function
- If WinBGI is not used, the 16 default colors are defined for
  console mode
- The cgetch and ckbhit functions are defined in console mode
  (conio.h), so as not to cause the same conflict with the WinBGI
  getch and kbhit functions.

Version 2 - 27-III-2024
randomize function added

Version 1 - 20-III-2024
gotoxy, cls, clrscr, random functions are added

****************************************************************/
#include <Windows.h>

#ifndef WINBGI_H

// If WinBGI is not used, the 16 default colors are defined for console mode

enum colors {
	BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY, DARKGRAY,
	LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE
};

#endif 

// Move the console cursor to the x, y position
void gotoxy(int x, int y);

// Clear the console screen, pointed by hConsole
void cls(HANDLE hConsole);

// Clean the console screen
void clrscr();

// Generates a random from 0 to randomMax
int random(int randomMax);

// Start the seed to generate random numbers. Used with the random function
void randomize();

// Gets the x coordinate of the current position of the console cursor
int wherex();

// Gets the y coordinate of the current position of the console cursor
int wherey();

// choose the color of the text displayed in the console
void textcolor(int color);

// Pauses the console until the user presses a key on the console
// The code(ASCII) of the key pressed is returned, or zero otherwise
char cgetch();

// Returns true if the user has pressed a key on the console, or false otherwise
bool ckbhit();