#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "conio.h"

using namespace std;

class Menu
{
public:
	Menu();
	~Menu();

	// show menu
	int DrawOptions(std::vector<std::string>& vec, int x, int y, int col);

	// Print a box in console text mode
	void DrawBox(int x1, int y1, int ancho, int largo, int col);
};

