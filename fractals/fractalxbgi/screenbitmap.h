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
	ramondc@hotmail.com

	UNIVERSIDAD NACIONAL DE INGENIERIA
	Faculty of Electrical and Electronic Engineering
	Lima-Peru

	YACSHA - Software & Desing
	>> The World of chaos - EL MUNDO DEL CAOS - Unlimited Programming

HISTORY...

  >> Version 2 - 13-IV-2024
	- Added getpixel, putpixelRGB, getPixelRGB, bar and barRGB methods
	- The draw method now has optional x and y parameters
	- Saving the palette color of a pixel in a bitmap screen is enabled, an
	  additional container of the same size as the bmpScreen, which saves
	  the colors but in RGB format

  >> Version 1 - 11-IV-2024
	- First version, to be used to quickly draw fractals

*****************************************************************************/
#include <vector>
#include <Windows.h>
using std::vector;

class CScreenBitmap
{
public:

	CScreenBitmap(unsigned int width, unsigned int height, bool enableBmpPalette = false);
	~CScreenBitmap();

	void setpalette(int red, int green, int blue);
	void setrgbpalette(int paletteColor, int red, int green, int blue);
	void putpixel(int x, int y, unsigned char paletteColor);
	void putpixelRGB(int x, int y, int rgbColor);
	void putpixel(int x, int y, int red, int green, int blue);
	unsigned char getpixel(const int& x, const int& y); // return int rgbColor
	int getpixelRGB(const int& x, const int& y); // return int rgbColor
	void bar(int left, int top, int right, int bottom, unsigned char paletteColor);
	void barRGB(int left, int top, int right, int bottom, int rgbColor);
	void draw(int x=0, int y=0);
	void clear();

private:
	int getRGBFromPalette(unsigned char paletteColor);
	int getRGB(const int& red, const int& green, const int& blue);

private:
	bool bmpPaletteIsEnabled;
	vector<vector<unsigned char>> bmpPaletteScreen;
	unsigned char palette[256][3];
	BITMAP bmpScreen;
};

