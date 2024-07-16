/*********************************************************************
:: MENU ::

Functions to draw a menu in text mode

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

  >> Version 1 - 07-IV-2024
	- First version

**********************************************************************/

#pragma once
#include <vector>

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

