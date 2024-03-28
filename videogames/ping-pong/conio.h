/*******************************
Conio.h
Old Borland C++ and Turbo C functions. Not Standard

Version 2 - 27-III-2024
randomize function added

Version 1 - 20-III-2024
gotoxy, cls, clrscr, random functions are added

By Yacsha
*******************************/

#pragma once
#include <Windows.h>

void gotoxy(int x, int y);

void cls(HANDLE hConsole);

void clrscr();

// Generates a random from 0 to randomMax
int random(int randomMax);

// Start the seed to generate random numbers. Used with the random function
void randomize();