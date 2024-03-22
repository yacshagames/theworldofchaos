/*******************************
Conio.h
By Yacsha - 2024-03-20
*******************************/

#pragma once
#include <Windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>


void gotoxy(int x, int y);

void cls(HANDLE hConsole);

void clrscr();

// Genera un aleatorio desde 0 hasta nRangoMayor
int random(int nRangoMayor);

bool RedirectConsoleIO();

bool ReleaseConsole();

void AdjustConsoleBuffer(int16_t minLength);

bool CreateNewConsole(int16_t minLength);