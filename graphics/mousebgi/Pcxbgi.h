/****************************************************************************
 Clase PCX 

 Version 1.2 - 16 Nov 1999
 - Se crea la funcion leer_cabecera() para leer solo una vez la
   cabecera del pcx
 - Se modifica la funcion Dibujar para dibujar sin leer la paleta
   solo leyendo el bitmap

 Version 1.1 - 20 Set 1999
 CARGA UN PCX EN PANTALLA utilizando el controlador bgi SVGA256

programado por:
JOSE LUIS DE LA CRUZ LAZARO 
ramondc@hotmail.com
Pagina Web: http://www.geocities.com/joseluisdl/jldl.htm
****************************************************************************/
#ifndef __PCXBGI_H
#define __PCXBGI_H


#include <stdio.h>
#include <dos.h>

#ifndef __GRAPHICS_H
#include <graphics.h>
#endif

class PCX
{
 public:

  PCX(); //constructor
  ~PCX(); //destructor

 unsigned char paleta[256][3]; //Array que contendr  la paleta de colores
			       // del PCX
// int tamano_paleta;
 int orden; //contiene el orden en que la paleta del pcx se a¤adira a la paleta de la vga
 /*
 NOTA:
 se crea la variable orden por el simple hecho, de que para visualizar varias
 imagenes en pantalla al mismo tiempo, se nesecita que cada paleta de cada
 imagen este cargada en la vga, es por eso que se nesecita, clasificarlas
 en algun orden dentro de la paleta de la vga, utilizare 64 colores para
 desplegar cada imagen en pantalla es decir se podran visualizar hasta 4
 imagenes con paleta independiente simultaneamente en la pantalla
 */

 private:
 FILE *fp;

 public:
 int ancho;
 int alto;
 private:

 int bytes_por_linea;

  void Paleta(void);
  void CorrerPaleta(void);
  public:
  void Dibujar( int, int );
  void leer_cabecera(int,char*);

};

PCX::PCX()
{
 alto=ancho=0;
 bytes_por_linea=0;
 orden=0;
 fp=new FILE;
}

PCX::~PCX()
{

  fclose(fp);   // Cerramos el fichero pcx
  delete fp;

}

void PCX::Paleta(void)
{
	unsigned char cont1;
	int cont;

	cont=0;
	cont1=0;

	/* El c¢digo que sigue a continuaci¢n pasa el contenido del array "Paleta"
	a la paleta de la VGA */
	for (cont=0;cont<64;cont++)
	{
		outportb (0x03c8,cont+orden*64+16);
		for (cont1=0;cont1<3;cont1++)
			outportb (0x03c9,paleta[cont][cont1]);
	}
}


void PCX::CorrerPaleta( void)
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

void PCX::leer_cabecera(int _orden, char *nombre)
{

	if( nombre == NULL ) return;
	if ( (fp=fopen(nombre,"rb"))==NULL ) return ;

	orden=_orden;

	fseek(fp,-768L,SEEK_END);  // Nos situamos en el comienzo de la paleta
	fread(paleta,768,1,fp);    // Leemos los bytes componentes del RGB
	CorrerPaleta();
	Paleta();

	//Leemos sus dimensiones
	fseek (fp,8L,SEEK_SET);
	fread(&ancho,2,1,fp);
	fread(&alto,2,1,fp);
	ancho++;
	alto++;

	fseek (fp,66L,SEEK_SET);
	fread(&bytes_por_linea,2,1,fp);
}


//DIBUJA EL GRAFICO DIRECTAMENTE MIENTRAS LO LEE, EN LA POSICION (x,y)
void PCX::Dibujar( int x, int y )
{


 if( fp==NULL ) return;

 fseek (fp,128L,SEEK_SET); // Nos saltamos la cabecera del PCX

 setviewport(x,y,x+ancho,y+alto,1);

   int i,j;
   unsigned char num_bytes,data;

   for(j=0;j<alto;j++)
    for(i=0;i<bytes_por_linea;)
    {
      data = fgetc(fp); //Leemos el bitmap byte por byte
      if( i<ancho )
      {
       if (data >= 192)      // es un rle?
	{
	 num_bytes = data - 192; // Cuantos veces se repite el color?
	 data = fgetc(fp);  // Leemos el color que se repite

	 while(num_bytes-- > 0)
	      putpixel(i++,j,data+orden*64+16);
	}
       else  //si no hay repeticion de color
	putpixel(i++,j,data+orden*64+16);
      }else i++;
    }

	//se vuelve al puerto por defecto
	setviewport(0,0,getmaxx(),getmaxy(),1);

}


/*
Ejemplo
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