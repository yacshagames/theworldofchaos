/***********************************************************************
::: IMGBGI :::
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

  >> Version 2 - 21 - III - 2024
	- Update graphics / imgbgi - Porting to VC++ 2017 using winbgi

  >> Versi�n 1.0 30-IV-2002
  Luego de tanto tiempo sin actualizar el PCXBGI, decid� hacer algo m�s
  productivo, como un cargador de im�genes universal, por el momento
  incorpor� y optimiz� las rutinas de carga del PCXBGI y el BMPPlus,
  para cargar ficheros PCX y BMP respectivamente

***********************************************************************/

#include "grafimpl.h" //modos de video SVGA de la BGI
#include "imgbgi.h"   //clase para cargar im�genes
#include "conio.h"    //getch();


int main(void)
{

 IMG pcx,bmp;
 char msg[40];

 //inicia el test de la carga de imagenes a diferentes modos de video
 for( int modo=4; modo>=0; modo--){


  IniciarSVGA( modo ); //cambia de modo de video


  sprintf( msg,"Test at a resolution of %ix%i...",getmaxx()+1, getmaxy()+1 );

  cleardevice();

  outtextxy(10,0, msg ); //mensaje de test

  getch();
  cleardevice();

  // carga PCX
  if( pcx.leer_cabecera( "bella.pcx") ){

   ventana(10,20,30+pcx.ancho,40+pcx.alto); //ventana de marco
   pcx.Dibujar( 20, 30 ); //dibuja el pcx

   outtextxy(0,0,"PCX loaded successfully!!! Press a key to continue...");
   getch();
   cleardevice();
  }

  // carga BMP
  if( bmp.leer_cabecera( "bella.bmp") ){
   ventana(10,20,30+bmp.ancho,40+bmp.alto); //ventana de marco
   bmp.Dibujar( 20, 30 ); //dibuja el bmp


   outtextxy(0,0, "BMP loaded successfully!!! Press a key to continue...");
   getch();
  }

 }

 closegraph();

 return 1;

}
