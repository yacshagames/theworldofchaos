#pragma once
/*****************************************************************************
SCREEN BITMAP

This class allows you to define a bitmap with or without a color palette, 
which is compatible with winbgi's putimage function, in such a way that it
stores the bitmap in memory and quickly draws it in the winbgi window. This
class should be used to replace winbgi's putpixel function, since the latter
is very slow when drawing to the screen.

Developed by:

	JOSE LUIS DE LA CRUZ LAZARO
	contact@theworldofchaos.com

	YACSHA - Software & Desing, since 1999, Lima-Peru
	>> The World of Chaos - EL MUNDO DEL CAOS - Unlimited Programming
	www.theworldofchaos.com

LICENSE
	This file is released under the terms of the BSD 3-Clause License.
	Read LICENSE file for more information.

HISTORY...

  >> Version 1 - 11-IV-2024
	- First version, to be used to quickly draw fractals

*****************************************************************************/


#include <Windows.h>

class CScreenBitmap
{
public:

	CScreenBitmap(unsigned int with, unsigned int height);
	~CScreenBitmap();

	void setpalette(int red, int green, int blue);
	void setrgbpalette(int paletteColor, int red, int green, int blue);
	void putpixel(int x, int y, int paletteColor);
	void putpixel(int x, int y, int red, int green, int blue);
	void draw(int x, int y);

private:
	int getRGBFromPalette(unsigned char paletteColor);
	int getRGB(const int& red, const int& green, const int& blue);

private:
	unsigned char palette[256][3];
	BITMAP bmpScreen;
};

