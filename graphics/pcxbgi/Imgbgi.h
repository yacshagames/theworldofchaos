/****************************************************************************
IMGBGI
Based on the original PCXBGI and BMPPlus routines.
 
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

 >> Version 2 - 21-III-2024
	- Porting to VC++ 2017 using winbgi
	- Optimizes the Dibujar routine for faster painting
	- Add IMAGETYPE to handle different types of images when drawing

 Version 1.4 - 30 Abril 2002
 -Luego de tanto tiempo sin actualizar el PCXBGI, decidí hacer algo
  mas productivo, como un cargador de imágenes universal, por el
  momento incorporé y optimizé las rutinas de carga del PCXBGI y
  el BMPPlus, para cargar ficheros PCX y BMP respectivamente.

 Version 1.3 - 29 Dic 1999
 - se modifica la funcion leer_cabecera() y Dibujar(), luego se logra
   eliminar el molesto error de Null pointer asigment que a veces
   aparecia.

 Version 1.2 - 16 Nov 1999
 - Se crea la funcion leer_cabecera() para leer solo una vez la
   cabecera del pcx
 - Se modifica la funcion Dibujar para dibujar sin leer la paleta
   solo leyendo el bitmap

 Version 1.1 - 20 Set 1999
 CARGA UN PCX EN PANTALLA utilizando el controlador bgi SVGA256

****************************************************************************/
#ifndef __IMGBGI_H
#define __IMGBGI_H

#include <stdio.h>
#include <dos.h>
#include <string.h>
#include <algorithm>
#include <string>

#ifndef __GRAPHICS_H
#include "graphics.h"
#endif

class IMG
{
public:
	enum class IMAGETYPE {
		PCX,
		BMP
	};

  IMG(); //constructor
  ~IMG(); //destructor

  unsigned char paleta[256][3]; //Array que contendrá la paleta de colores
			       // del IMG

 long ancho;
 long alto;


 private:

  char nombre[64];
  int bytes_por_linea;
  IMAGETYPE eImageType;

  //void Paleta(void);
  //void CorrerPaleta(void);
 public:
  //Carga un PCX
  int leer_cabeceraPCX( const char * );
  int DibujarPCX( int, int );
  //Carga un BMP
  int leer_cabeceraBMP( const char * );
  int DibujarBMP( int, int );
  //Detecta el tipo de imagen según la extención del fichero
  int leer_cabecera( const std::string& );
  int Dibujar( int, int );
  int getRGBFromPalette(unsigned char cColor);

};

IMG::IMG()
{
 alto=ancho=0;
 bytes_por_linea=0;
 eImageType = IMAGETYPE::PCX;
}

IMG::~IMG()
{

}

/*void IMG::Paleta(void)
{
	 int i,j;

	 //El código que sigue a continuación pasa el contenido del array "Paleta"
	 //a la paleta de la VGA
	 for (i=0;i<256;i++)
	 {
	  outportb (0x03c8,i);
	  for (j=0;j<3;j++)
	   outportb (0x03c9,paleta[i][j]);
	 }
}


void IMG::CorrerPaleta( void)
{

 int i,j;
 // Movemos 2 bits
 // hacia la derecha todos los bytes leídos en la paleta de la imagen.
 // Los componentes RGB de la paleta se encuentran en los 6 bits
 // de mayor peso de los valores leídos del fichero
 for(i=0;i<256;i++)
  for(j=0;j<3;j++)
    paleta[i][j]>>=2;

}*/

int IMG::leer_cabecera( const std::string& _nombre ){

	std::string snombre(_nombre);
	std::transform(snombre.begin(), snombre.end(), snombre.begin(), ::toupper);

	if(snombre.find(".PCX") != std::string::npos) {
		eImageType = IMAGETYPE::PCX;
		return leer_cabeceraPCX(snombre.c_str());
	}else if(snombre.find(".BMP") != std::string::npos) {
		eImageType = IMAGETYPE::BMP;
		return leer_cabeceraBMP(snombre.c_str());
	}else 
		return 0;
}

int IMG::Dibujar( int x, int y ){

	switch (eImageType) {
	case IMG::IMAGETYPE::BMP:
		return DibujarBMP(x, y);
	default:
		return DibujarPCX(x, y);
	} 
	
	return 0;
}

// Converts a palette index (cColor) to an RGB color, using the palette loaded from the image
int IMG::getRGBFromPalette(unsigned char cColor)
{
	int rgb = paleta[cColor][2];
	rgb = (rgb << 8) + paleta[cColor][1];
	rgb = (rgb << 8) + paleta[cColor][0];
	
	return rgb;
}



int IMG::leer_cabeceraPCX( const char * _nombre)
{


	strcpy(nombre,_nombre);

	FILE *fp;

	if ( (fp=fopen(nombre,"rb"))==NULL ) return 0 ;

	fseek(fp,-768L,SEEK_END);  // Nos situamos en el comienzo de la paleta
	fread(paleta,768,1,fp);    // Leemos los bytes componentes del RGB
	//CorrerPaleta();
	//Paleta();

	//Leemos sus dimensiones
	fseek (fp,8L,SEEK_SET);
	fread(&ancho,2,1,fp);
	fread(&alto,2,1,fp);
	ancho++;
	alto++;

	fseek (fp,66L,SEEK_SET);
	fread(&bytes_por_linea,2,1,fp);

	fclose(fp);
	return 1;
}


//DIBUJA EL GRAFICO DIRECTAMENTE MIENTRAS LO LEE, EN LA POSICION (x,y)
int IMG::DibujarPCX( int x, int y )
{


 FILE *fp;


 if ( (fp=fopen(nombre,"rb"))==NULL ) return 0 ;

 fseek (fp,128L,SEEK_SET); // Nos saltamos la cabecera del PCX

 setviewport(x,y,x+ancho,y+alto,1);

   int i,j;
   unsigned char num_bytes,data;

   for(j=0;j<alto;j++)
    for(i=0;i<bytes_por_linea;)
    {
      data = fgetc(fp); //Leemos el bitmap byte por byte

      if( data>0xbf ) //if (data >= 192)      // es un rle?
	{
	 num_bytes = data&0x3f; //num_bytes = data - 192; // Cuantos veces se repite el color?
	 data = fgetc(fp);  // Leemos el color que se repite

	 while(num_bytes-- > 0)  //Pintamos el color que se repite num_bytes veces
	      //putpixel(i++,j,data);
	      putpixel(i++, j, getRGBFromPalette(data));
	}
       else  //si no hay repeticion de color pintamos una vez
		  //putpixel(i++,j,data);
		  putpixel(i++, j, getRGBFromPalette(data));	
    }

	//se vuelve al puerto por defecto
	setviewport(0,0,getmaxx(),getmaxy(),1);

    fclose(fp);

  return 1;

}

int IMG::leer_cabeceraBMP( const char * _nombre)
{

  strcpy(nombre,_nombre);


  int bits_por_pixel;
  unsigned long n_indices;

  FILE *fp;

  if ((fp=fopen(nombre,"rb"))==NULL) return 0;


  //LEE INFO DEL BMP
  fseek(fp,18L,SEEK_SET);
  fread(&ancho, 4, 1, fp);
  fread(&alto, 4, 1, fp);
  fseek(fp,2L,SEEK_CUR);
  fread(&bits_por_pixel,2, 1, fp);
  fseek(fp,16L,SEEK_CUR);
  fread(&n_indices,4, 1, fp);
  fseek(fp,4L,SEEK_CUR);


  if (n_indices==0 && bits_por_pixel==8) n_indices=256;

  for(int i=0;i<n_indices;i++){
   paleta[i][2] = fgetc(fp);
   paleta[i][1] = fgetc(fp);
   paleta[i][0] = fgetc(fp);
   fgetc(fp);
  }

  //CorrerPaleta();
  //Paleta();


  fclose(fp);


  return 1;
}

//DIBUJA EL GRAFICO DIRECTAMENTE MIENTRAS LO LEE, EN LA POSICION (x,y)
int IMG::DibujarBMP( int x, int y ){

  FILE *fp;


  if ((fp=fopen(nombre,"rb"))==NULL) return 0;

  long offset = -(long)ancho*(long)alto;

  fseek(fp, offset, SEEK_END);  // Nos situamos al comienzo del BMP


  int ex_ancho=(4-ancho%4)%4,i,j,k;

  for (j=alto-1;j>=0;j--){


	  for (i = 0; i < ancho; i++) {
		  //putpixel(x + i, y + j, (unsigned char)fgetc(fp));	
		  putpixel(x + i, y + j, getRGBFromPalette(fgetc(fp)));
	  }

   for(k=0;k<ex_ancho;k++)
    fgetc(fp);
  }

  fclose(fp);

  return 1;
}



/*
Ejemplo
void main(void)
{


 IniciarSVGA( _640x480 );

 PCX pcx,bmp;

 pcx.leer_cabecera(0, "bella.pcx");
 pcx.Dibujar( 10, 20 );

 getch();
 cleardevice();

 bmp.leer_cabecera(0, "bella.bmp");
 bmp.Dibujar( 30, 80 );



 getch();
 closegraph();

}
*/

#endif

