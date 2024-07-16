#pragma once
/***********************************************************************
 ::: BMPPlus :::
 LOADS AN 8-BIT BMP (256 COLORS) AND PLOTS IT ON THE SCREEN

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

  >> Version 2 - 25-III-2024
	- Update: Porting to VC++ 2017 using winbgi
	- The old VIDEO class and the BMP class methods related to drawing and
	  setting the palette are removed, since they were obsolete in Windows
	- getRGBFromPalette is Added to convert a palette color into an RGB color,
	  and use it in the WinBGI putpixel that requires an RGB color as a
	  parameter and not a palette color like the old borland c or turbo c putpixel
	- dibujarppp is optimized to plot pixel by pixel on the screen from a
	  preloaded bitmap
	- It is allowed to choose whether to read the bitmap (preloaded), since there
	  are cases in which it will only be required to read the header
	- Minor improvements in the definition of classes and member variables
	- Load and fast plot a BMP and JPG using WinBGI
	- Show BMP Data from header for bella.bmp
	- Show BMP and JPG in original size and fit size using readimagefile
	- Fix: The readimagefile parameters were defined well so as not to
	  distort the image when displayed in the original size
	- The drawing order of text and images is optimized, the text is
	  always displayed first and then the images.

  >> Versi?n 1.0 8-IX-2000
	- Similar al PCXPlus pero grafica mapas de bits (BMP) utilizando
	  rutinas de dibujo a bajo nivel en las resoluciones de 320x200
	  y 640x480 con 256 colores.

***********************************************************************/

/*
BMP class developed by:

  Routines to control the paddle thanks to:
   Emmanuel Garc?s - Manolo_1981@yahoo.com

  Information about the internal structure of the BMP, thanks to:
   Fabi?n Sierra C. - magic_century@hotmail.com

Type is a 'magic number' used to check that the file is .bmp.
size is the size of the bmp file including the header and bmp_info
Reserved is not normally used (at least until 2000 it was not used).
Offset is the offset of the data relative to the start of the file.
It is equal to the size of the header structures, when there is no pallet and
When there is a palette, the bytes used by the palette are added.

Bytes_en_cabecera is exactly that and it seems like useless data to me.
Plans is a field that I have never used. Bits_per_pixel is important;
I will explain it in detail. Compression... I have no idea.
If I come across a file with an abnormal value in this field, I discard it.
Colors are generated on the screen using a combination of red, green
and blue. The set of combinations is called the color palette.
A color is referenced as a number. The range of the number depends on the
bits used to reference it. If it is 1 bit, 2 colors are allowed.
If they are 4, 16, etc. For each pixel, its color is specified. So the field
bits_per_pixel indicates how many bits represent a pixel on the screen.
If you read pixel by pixel...
Immediately after both headings begins the specification that
Red, green and blue components will be used for each color. The size of this
section is calculated knowing the number of colors and that 4 bytes are used
to specify each color; one for red, one for green and one for
the blue; The other one is not used, I don't know why. You must use setpalette to
specify the palette to use.
Two pieces of information. The colors are inverted on the palette; first the blue and then
final red. The pixels are in reverse order; They start on the last line.

Spanish:

 Clase BMP desarrollada por:

 Rutinas para control de la paleta gracias a:


Desplazamiento es el desplazamiento de los datos con respecto al inicio del archivo.
cuando hay paleta se suman los bytes utilizados por la paleta.

Planos es un campo que nunca he utilizado. Bits_por_pixel es importante;
y azul. Al conjunto de combinaciones se le llama la paleta de colores.
bits usados para referenciarlo. Si es 1 bit, se permiten 2 colores.
Si son 4, 16, etc. Para cada pixel se especifica su color. Entonces, el campo
Si vas leyendo pixel a pixel...
para especificar cada color; uno para el rojo, otro para el verde y otro para
el azul; el otro no se utiliza, no se por que. Debes usar setpalette para
especificar la paleta a usar.
*/


//#define PALETTE_INDEX       0x03c8
//#define PALETTE_DATA        0x03c9

class BMP
{
protected:

	unsigned char* bitmap;
	unsigned char paleta[256 * 3];

public:
	////////////////////////////////////////////////////////////////////////
	// Header Info: https://es.wikipedia.org/wiki/Windows_bitmap  //
	////////////////////////////////////////////////////////////////////////
	// CABECERA     					//#bytes
	char tipo[2];         		        //2
	unsigned long tamano;  				//4
	char reservado[4];     				//4
	unsigned long desplazamiento;		//4
										//Total: 14 bytes

	// INFORMACION DEL BMP				//#bytes
	unsigned long bytes_en_cabecera;	//4
	unsigned long ancho;				//4
	unsigned long alto;					//4
	int planos;							//2 - Number of color planes
	int bits_por_pixel;					//2
	unsigned long compresion;			//4
	unsigned long tamano_de_imagen;		//4
	unsigned long resolucion_h;			//4
	unsigned long resolucion_v;			//4
	unsigned long n_indices;			//4  - retorna el numero de colores de la paleta - Number of actually used colors
	unsigned long n_i_indices;			//4  - Number of important colors 0=all
										//Total: 40 bytes
	BMP();
	~BMP();
	int abrir(const char *nom, bool readBitmap);
	//void asign_paleta();
	void rotar_paleta();
	//void dibujar(VIDEO &video,int x,int y);
	void dibujarppp(int x,int y);
private:
	int getRGBFromPalette(unsigned char cColor);
};

BMP::BMP()
{
	bitmap = NULL;
}

BMP::~BMP()
{
	if (bitmap)
		delete bitmap;
}

int BMP::abrir(const char *nom, bool readBitmap )
{
	FILE *fp;

	if ((fp = fopen(nom, "rb")) == NULL) return 0;

	//LEE LA CABECERA
	fread(&tipo, 2, 1, fp);
	fread(&tamano, 4, 1, fp);
	fread(&reservado, 4, 1, fp);
	fread(&desplazamiento, 4, 1, fp);

	//LEE INFO DEL BMP
	fread(&bytes_en_cabecera, 4, 1, fp);
	fread(&ancho, 4, 1, fp);
	fread(&alto, 4, 1, fp);
	fread(&planos, 2, 1, fp);
	fread(&bits_por_pixel, 2, 1, fp);
	fread(&compresion, 4, 1, fp);
	fread(&tamano_de_imagen, 4, 1, fp);
	fread(&resolucion_h, 4, 1, fp);
	fread(&resolucion_v, 4, 1, fp);
	fread(&n_indices, 4, 1, fp);
	fread(&n_i_indices, 4, 1, fp);

	if (n_indices == 0 && bits_por_pixel == 8)
		n_indices = 256;

	int i;

	for (i = 0; i < n_indices; i++){

		// Load the color and move all the bytes read in 
		// the PCX palette 2 bits to the right. The RGB 
		// components of the palette are found in the
		// 6 bits with the greatest weight of the values
		// read from the file
		paleta[i * 3 + 2] = fgetc(fp) >> 2;
		paleta[i * 3 + 1] = fgetc(fp) >> 2;
		paleta[i * 3 + 0] = fgetc(fp) >> 2;
		fgetc(fp);
	}

	
	if (readBitmap) {

		// bitmap = (unsigned char far *)
		//		   farmalloc(sizeof(unsigned char far)*(ancho)*(alto));

		bitmap = new unsigned char[alto*ancho];

		int ex_ancho = (4 - ancho % 4) % 4, k;

		for (int j = alto - 1; j >= 0; j--) {
			for (i = 0; i < ancho; i++)
				bitmap[j*ancho + i] = (unsigned char)fgetc(fp);

			for (k = 0; k < ex_ancho; k++)
				fgetc(fp);
		}

	} else {

		bitmap = NULL;
	}

	fclose(fp);

	return 1;
}
/*
void BMP::asign_paleta()
{
  outp(PALETTE_INDEX,0);

  for (int i=0;i<256*3;i++)
   outp(PALETTE_DATA,paleta[i]);
}*/

void BMP::rotar_paleta()
{
	int r, g, b;

	r = paleta[3];
	g = paleta[4];
	b = paleta[5];

	for (int i = 3; i < 256 * 3 - 3; i++)
		paleta[i] = paleta[i + 3];

	paleta[256 * 3 - 3] = r;
	paleta[256 * 3 - 2] = g;
	paleta[256 * 3 - 1] = b;

	//asign_paleta();
}

/*void BMP::dibujar(VIDEO &video,int x,int y)
{
  unsigned int pos_pantalla = 320*y;//(y<<8)+(y<<6);
  unsigned int indice_bmp = 0;
  unsigned char byte;

  for(int i=0;i<alto;i++)
  {
	for (int j=0;j<ancho;j++)
		{
		 byte=bitmap[indice_bmp];
		 video.vga[pos_pantalla+x+j]=byte;
		 indice_bmp++;
		 }
		 pos_pantalla+=320;
  }

  video.desplegar();
}*/

//Dibujar pixel por pixel
void BMP::dibujarppp(int x, int y)
{
	int i, j;
	for (i = 0; i < alto; i++)
		for (j = 0; j < ancho; j++)
			putpixel(j + x, i + y, getRGBFromPalette(bitmap[i*ancho + j]));
}

// Converts a palette index (cColor) to an RGB color, using the palette loaded from the image
int BMP::getRGBFromPalette(unsigned char cColor)
{
	int rgb = paleta[cColor*3+2];			// blue
	rgb = (rgb << 8) + paleta[cColor*3+1];	// green
	rgb = (rgb << 8) + paleta[cColor*3+0];	// red

	return rgb;
}
