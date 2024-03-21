/****************************************************************************
 Clase PCX 1.1
 20/09/1999
 PCX 1.1
 CARGA UN PCX EN PANTALLA utilizando el controlador bgi SVGA256

 JOSE LUIS DE LA CRUZ LAZARO UNI-FIEE
	ramondc@hotmail.com
****************************************************************************/
#ifndef __PCXBGI_H
#define __PCXBGI_H


#include <stdio.h>
#include <dos.h>
#include <alloc.h>
#include <conio.h>
#include <mem.h>

#ifndef __GRAPHICS_H
#include <graphics.h>
#endif

//#include <iostream.h>

//#ifndef __MOUSEC_H
//#include "mousec.h"
//#endif

//void ModoGrafico( int );
//void putpixel(unsigned int x,unsigned int y,unsigned char color);

class PCX
{
 public:

 unsigned char paleta[256][3]; //Array que contendr  la paleta de colores
			       // del PCX
// int tamano_paleta;

 int ancho;
 int alto;
 int bytes_por_linea;


  PCX(); //constructor
  ~PCX(); //destructor

  void Paleta( int );
  void CorrerPaleta();
//  void Dibujar( int modo );
//  unsigned char Leer( char *nombre );
  unsigned char Dibujar( int, int, int, char *nombre );
//  void ModoGrafico( void );

};

PCX::PCX()
{
 alto=ancho=0;
 bytes_por_linea=0;
// tamano_paleta=0;

}

PCX::~PCX()
{
}


void PCX::Paleta(int salto)
{
	unsigned char cont1;
	int cont;

	cont=0;
	cont1=0;

	/* El c¢digo que sigue a continuaci¢n pasa el contenido del array "Paleta"
	a la paleta de la VGA */
	for (cont=0;cont<240;cont++)
	{
		outportb (0x03c8,cont+salto);
		for (cont1=0;cont1<3;cont1++)
			outportb (0x03c9,paleta[cont][cont1]);
	}
}


void PCX::CorrerPaleta()
{
	unsigned char cont1;
	int cont;

	for (cont=0;cont<256;cont++)
		for (cont1=0;cont1<3;cont1++)
			paleta[cont][cont1]=(paleta[cont][cont1]>>2);
			//Movemos 2 bits
			//	  hacia la derecha todos los bytes le¡dos en la paleta del PCX.
			  //	  Los componentes RGB de la paleta se encuentran en los 6 bits
			    //	  de mayor peso de los valores le¡dos del fichero

}

//DIBUJA DIRECTAMENTE MIENTRAS LO LEE
unsigned char PCX::Dibujar( int x, int y, int salto, char *nombre )
{

	FILE *fp;

	if ((fp=fopen(nombre,"rb"))==NULL) return (0);
	fseek(fp,-768L,SEEK_END);  // Nos situamos en el comienzo de la paleta
	fread(paleta,768,1,fp);    // Leemos los bytes componentes del RGB
	CorrerPaleta();
	Paleta(salto);

	//Leemos sus dimensiones
	fseek (fp,8L,SEEK_SET);
	fread(&ancho,2,1,fp);
	fread(&alto,2,1,fp);
	ancho++;
	alto++;
	fseek (fp,66L,SEEK_SET);
	fread(&bytes_por_linea,2,1,fp);
	fseek (fp,128L,SEEK_SET); // Nos saltamos la cabecera del PCX

	//se crea un puerto virutal para desplegar la imagen
	setviewport(x,y,x+ancho,y+alto,1);

   int i,j;
   unsigned char num_bytes,data;

   for(j=0;j<alto;j++)
    for(i=0;i<bytes_por_linea;)
    {
      data = getc(fp); //Leemos el bitmap byte por byte
      if( i<ancho )
      {
       if (data >= 192)      // es un rle?
	{
	 num_bytes = data - 192; // Cuantos veces se repite el color?
	 data = getc(fp);  // Leemos el color que se repite

	 while(num_bytes-- > 0)
	      putpixel(i++,j,data+salto);
	}
       else  //si no hay repeticion de color
	putpixel(i++,j,data+salto);
      }else i++;
    }

	//se vuelve al puerto por defecto
	setviewport(0,0,getmaxx(),getmaxy(),1);

	fclose(fp);   // Cerramos el fichero pcx
	return (1);
}

/*
void main(void)
{

 ModoGrafico();

 PCX pcx,pcx1;

 pcx1.Dibujar("c:\\windows\\escrit~1\\logouni.PCX");

 void *arrow;
 unsigned int size;

size = imagesize(0,0,pcx1.ancho,pcx1.alto);

arrow = malloc(size);

getimage(0,0,pcx1.ancho,pcx1.alto,arrow);


 getch();

 pcx.Dibujar("c:\\windows\\escrit~1\\prueba3.PCX");


getch();

pcx1.Paleta();

putimage(0, 0, arrow, COPY_PUT);


 getch();
 closegraph();


}
*/

#endif