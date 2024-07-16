/*************************************************************************

LICENSE

	This file is released under the terms of the BSD 3-Clause License.
	Read LICENSE.txt file for more information.

*************************************************************************/

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

