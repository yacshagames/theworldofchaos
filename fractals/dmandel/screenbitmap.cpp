#include "screenbitmap.h"
#include "graphics.h"

CScreenBitmap::CScreenBitmap(unsigned int with, unsigned int height)
{
	bmpScreen.bmHeight = height;
	bmpScreen.bmWidth = with;
	bmpScreen.bmWidthBytes = sizeof(unsigned int) * bmpScreen.bmWidth;
	bmpScreen.bmBits = new unsigned int[bmpScreen.bmHeight*bmpScreen.bmWidth];
}

CScreenBitmap::~CScreenBitmap()
{
}

void CScreenBitmap::setpalette( int red, int green, int blue) {
	int i;

	for (i = 0; i < 256; i++)
	{
		//Paleta[cont * 3 + 0] = r * (cont + 1);
		//Paleta[cont * 3 + 1] = g * (cont + 1);
		//Paleta[cont * 3 + 2] = b * (cont + 1);
		setrgbpalette(i, red*i, green*i, blue*i);
	}
}

void CScreenBitmap::setrgbpalette(int paletteColor, int red, int green, int blue) {

	palette[paletteColor][0] = red;
	palette[paletteColor][1] = green;
	palette[paletteColor][2] = blue;

}

void CScreenBitmap::putpixel(int x, int y, int paletteColor)
{
	auto screen = (unsigned int*)bmpScreen.bmBits;
	screen[x + bmpScreen.bmWidth * y] = getRGBFromPalette(paletteColor);
}

void CScreenBitmap::putpixel(int x, int y, int red, int green, int blue)
{
	auto screen = (unsigned int*)bmpScreen.bmBits;
	screen[x + bmpScreen.bmWidth * y] = getRGB(red, green, blue);
}


void CScreenBitmap::draw(int x, int y)
{
	putimage(x, y, &bmpScreen, COPY_PUT);
}

// Converts a palette index (cColor) to an RGB color, using the palette loaded from the image
int CScreenBitmap::getRGBFromPalette(unsigned char paletteColor)
{
	//int rgb = palette[paletteColor][2];			// blue
	//rgb = (rgb << 8) + palette[paletteColor][1];	// green
	//rgb = (rgb << 8) + palette[paletteColor][0];	// red

	//return rgb;

	return getRGB(palette[paletteColor][0], palette[paletteColor][1], palette[paletteColor][2]);
}


// Converts a palette index (cColor) to an RGB color, using the palette loaded from the image
int CScreenBitmap::getRGB(const int& red, const int& green, const int& blue)
{
	int rgb = blue;			// blue
	rgb = (rgb << 8) + green;	// green
	rgb = (rgb << 8) + red;	// red

	return rgb;
}