/***********************************************************************
 ::: IMGBGI :::
  >> Versión 1.0 30-IV-2002
  Luego de tanto tiempo sin actualizar el PCXBGI, decidí hacer algo más
  productivo, como un cargador de imágenes universal, por el momento
  incorporé y optimizé las rutinas de carga del PCXBGI y el BMPPlus,
  para cargar ficheros PCX y BMP respectivamente

 :::Programado por:::
 José Luis De La Cruz Lázaro
 YACSHA - Software & Desing 2002
  >> yacsha@elmundodelcaos.tk    
  >> www.elmundodelcaos.tk -> EL MUNDO DEL CAOS - Unlimited Programming
  >> www.foros3d.tk  -> Foros de discusión  Flash/ActionScript - C/C++

***********************************************************************/

#include "grafimpl.h" //modos de video SVGA de la BGI
#include "imgbgi.h"   //clase para cargar im genes
#include <conio.h>    //getch();


void main(void)
{

 IMG pcx,bmp;
 char msg[40];

 //inicia el test de la carga de imagenes a diferentes modos de video
 for( int modo=4; modo>=0; modo--){


  IniciarSVGA( modo ); //cambia de modo de video


  sprintf( msg,"Test a resoluci¢n de %ix%i...",getmaxx()+1, getmaxy()+1 );

  cleardevice();

  outtextxy(10,0, msg ); //mensaje de test

  getch();
  cleardevice();

  // carga PCX
  if( pcx.leer_cabecera( "bella.pcx") ){

   ventana(10,10,30+pcx.ancho,40+pcx.alto); //ventana de marco
   pcx.Dibujar( 20, 30 ); //dibuja el pcx

   outtextxy(0,0,"PCX cargado exitosamente!!! Presione una tecla para continuar...");
   getch();
   cleardevice();
  }

  // carga BMP
  if( bmp.leer_cabecera( "bella.bmp") ){
   ventana(10,10,30+bmp.ancho,40+bmp.alto); //ventana de marco
   bmp.Dibujar( 20, 30 ); //dibuja el bmp


   outtextxy(0,0,"BMP cargado exitosamente!!! Presione una tecla para continuar...");
   getch();
  }

 }

 closegraph();


}
