/***************************************************************************
JOYSTICK.H

RUTINAS PARA EL CONTROL DEL JOYSTICK o JOYPAD

programado por:
JOSE LUIS DE LA CRUZ LAZARO 
ramondc@hotmail.com
Pagina Web: http://www.geocities.com/joseluisdl/jldl.htm

Version 1.0 ( 21 Dic 1999 )
 - Rutinas para la comunicacion con el puerto del joystick
 - creacion de funciones para leer la posicion del joystick
 - creacion de funciones para leer los eventos generados por
   cualquier boton del joystick
 - Creacion de una funcion para leer la posicion de un joystick Pad
***************************************************************************/

/*
Informacion sobre el funcionamiento del Joystick gracias a
(John Allen)


1.  Trigger the joystick oneshots with an 'out' to 0x201.
    This will set all of the joystick bits on.

2.  Read (in) 0x201, finding:

	Bit		Contents
	0		Joystick A X coordinate
	1		Joystick A Y coordinate
	2		Joystick B X coordinate
	3		Joystick B Y coordinate
	4		Button A 1
	5		Button A 2
	6		Button B 1
	7		Button B 2

3.  Continue reading 0x201 until all oneshots return to zero,
    recording the loop during which each bit falls to zero.
    The duration of the pulse from each oneshot may be used to
    determine the resistive load (from 0 to 100K) from each
    Joystick, as: Time = 24.2msec. + .011 (r) msec.

4.  To do this correctly, I recommend calibrating the joystick;
    have the user move the stick to each corner, then center it,
    while recording the resulting values.
*/

#ifndef __JOYSTICK_H
#define __JOYSTICK_H

//#include <time.h>
#include <dos.h>
#include <math.h>
#include <conio.h>
#include <iostream.h>

/*
Valores con los que hay que definir la variable JOY_PUERTO:
El Joystick se puede conectar en los siguientes puertos:
0x201 ( GamePort  Standar )
0x209 ( MidiPort ) Normalmente incluido en la tarjeta de sonido
*/
#define JOY_PUERTO 0x201
//Numero de maximo de botones que puede tener un joystick
#define NUM_BOTONES 4

//se define las mascaras de los 4 botones A B C D del joystick
const BOTONMASC[4]={	0x10, //Boton A
			0x20, //Boton B
			0x40, //Boton C
			0x80  //Boton D
		    };

unsigned Comunicar_con_Puerto( void)
{
 //se envia un byte al puerto del joystick
 outportb(JOY_PUERTO,0xff);
 //se retorna la respuesta del puerto
 return inportb(JOY_PUERTO);
}

//se definen los eventos que puede tomar un boton del joystick
#define SINEVENTO		0x00 //no hay eventos
#define BOTON_DOWN 		0x01 //Se presiona el boton ( este evento siempre sucede despues del evento SINEVENTO )
#define BOTON_STILL_DOWN 	0x03 //Se deja presionado el boton sin soltarlo ( este evento siempre sucede despues del evento BOTON_DOWN)
#define BOTON_UP		0x02 //se suelta el boton (este evento siempre sucede despues del evento BOTON_STILL_DOWN )

typedef struct {
    int m1,m2,m3; //mascaras de la posicion del joystick
		  //m1=3 m2=1 m3=2
    int jx,jy;  /* Contienen el numero de ticks actuales en cada eje.
		   El numero de ticks es proporcional a la duracion del pulso
		    tiempo que demora
		   una se¤al en salir del puerto recorrer el joystick y
		   regresar al puerto. Esto sucede en menos de un segundo,
		   mientras se mantiene el joystick estatico en
		   una posicion. Si la posicion en el eje x
		   es cercana a la posicion izquierda del mando se
		   obtienen pocos ticks( entre 3 y 5 aprox ) mientras si lo es
		   a la posicion derecha se obtienen varios ticks ( entre 630
		   y 635 aprox ), analogamente con la posicion del eje y
		   se obtienen pocos ticks en la posicion SUPERIOR del mando
		   y varios si se esta en la posicion INFERIOR.
		*/

    int x,y;//contiene las coordenadas actuales de la posicion del joystick
    int cenx,ceny,minx,maxx,miny,maxy;  //contiene las coordenadas limite de la posicion del joystick
					//para habilitarlas es nesesario calibrar el joystick
    int Padx,Pady; //contiene las posiciones del control PAD o JoyPad ( vease su definicion mas abajo )

    } Posicion_stick;

//se inicializa la estructura
Posicion_stick joy = {  3,1,2,
			0,0,
			0,0,
			0,0,0,0};

typedef struct
 {
  //- estado1 contiene 1 si el boton se encuentra presionado y
  //  0 si se encuentra suelto
  //- estado0 contiene el estado anterior a estado1
  unsigned estado0,estado1;

  //contiene el evento actual generado por un boton del joystick (estado del boton)
  unsigned evento;

 } EventoBoton;

//se crean las estructuras que contendran los eventos para cada boton del joystick
EventoBoton boton[NUM_BOTONES];

//contiene el byte con la respuesta del puerto acerca del estado actual del joystick
unsigned Byte;

//se Lee eventos en todos los botones del joystick
//la variable evento ( en la estructura boton ) es actulizada contiendo
//el evento actual para cada boton
void LeerEventos( void )
{
 //se obtiene respuesta del puerto
 Byte=Comunicar_con_Puerto();

 //se busca eventos en todos los botones del joystick
 for(int i=0;i<NUM_BOTONES;i++)
 {
  boton[i].evento = SINEVENTO;

  // verifica si se presiono algun boton del joystick comparando Byte con la mascara del boton
  boton[i].estado1= !(Byte & BOTONMASC[i]); //se actualiza estado1

  //Los eventos se generan segun los contenidos de estado 0 y estado1
  //de la siguiente manera
  //estado0 estado1    evento generado
  //   1        1      BOTON_STILL_DOWN
  //   0        1      BOTON_DOWN
  //   1        0      BOTON_UP

  if( boton[i].estado0 & boton[i].estado1) boton[i].evento = BOTON_STILL_DOWN;
  else if( !boton[i].estado0 & boton[i].estado1) boton[i].evento = BOTON_DOWN;
  else if( boton[i].estado0 & !boton[i].estado1) boton[i].evento = BOTON_UP;

  boton[i].estado0=boton[i].estado1; //se actualiza estado0 con el valor de estado1
 }

}

//Busca si se genero algun evento en cualquier boton del joystick y
//luego se retorna el evento
unsigned ObtenerEvento( void )
{
  //se obtiene los eventos de todos los botones
  LeerEventos();

  //se busca si alguno de los botones presenta un evento
  for( int i=0;i<NUM_BOTONES;i++)
  if( boton[i].evento != SINEVENTO ) return boton[i].evento;

  return SINEVENTO;
}

//se lee la posicion x e y del joystick
void LeerPosicion( void )
{

// contendra la respuesta del puerto
   unsigned byte;

// se envia una se¤al al puerto
   byte=Comunicar_con_Puerto();

// se inicializa los valores de jx y jy
   joy.jx=joy.jy=0;

// se obtienen los valores de los ticks jx y jy
// mientras dure la se¤al enviada al puerto
    while( (byte & joy.m1) )//la se¤al caduco
     {
	if ( byte & joy.m2 ) joy.jx++;
	if ( byte & joy.m3 ) joy.jy++;
	byte = inportb(JOY_PUERTO);   //se obtiene informacion del puerto
      }

    //se obtiene la posicion actual
    joy.x = joy.jx - joy.cenx;
    joy.y = joy.jy - joy.ceny;

}

int Moda( unsigned *N , int n)
{
// n: cantidad de numeros
// N: arreglo muestra
int f=0, // frecuencia del numero
    ftmp,// frecuencia temporal
    num, // moda
    i,j;

for(i=0;i<n-1;i++)
 {
  ftmp=1;
  for(j=i+1;j<n;j++)
   if(N[i]==N[j])ftmp++;

  if( ftmp>f )
   {
   f=ftmp;
   num=N[i];
   }
 }

 return num; //retorna la moda
}

//variables estadisticas
const TM=10;//tama¤o de muestra
unsigned Muestra[2][TM],k=0,moda[2];

//Se obtiene la posicion de una forma presisa estadisticamente
//por medio de un muestreo
void LeerPosicionPrecisa( void )
{

  unsigned c;

// se obtiene respuesta del puerto
   c=Comunicar_con_Puerto();

// Obtener posiciones X e Y
   joy.jx=joy.jy=0;

    while( (c & joy.m1) )
     {
	if ( c & joy.m2 ) joy.jx++;
	if ( c & joy.m3 ) joy.jy++;
	c = inportb(JOY_PUERTO);
     }

     Muestra[0][k]=joy.jx; //se obtiene una muestra de los jx
     Muestra[1][k]=joy.jy; //se obtiene una muestra de los jy
     k++;
     k%=TM; //se asegura que Muestra contenga 5 muestras anteriores

     //se obtiene modaMax como la mayor de todas las muestras
     int i,j;
     for( j=0;j<2;j++)
     {

      moda[j]=Moda( Muestra[j], TM );

     /*
     modaMax[j]=Muestra[j][0];
     for( i=1;i<4;i++ )
      if( Muestra[j][i]>modaMax[j] ) modaMax[j]=Muestra[j][i];
      */
     }

    // se verifica si los valores de jx y jy son los valores modales
    if( joy.jx==moda[0] && joy.jy==moda[1] )
    {
     joy.x = joy.jx - joy.cenx;
     joy.y = joy.jy - joy.ceny;
    }

}

//se define las posiciones que puede tomar el joystick Pad
#define CEN_ 0x00 //centro
#define IZQ_ 0x01 //izquierda
#define DER_ 0x02 //derecha
#define ARR_ 0x03 //arriba
#define ABA_ 0x04 //abajo

//Se restringe la posicion del joystick a las posiciones anteriores
//y sus combinaciones
//Este tipo de movimiento es tipico de un "Joystick Pad" o "JoyPad"
const DE=10;//Desviacion Estandar de la posicion
void LeerPosicionPad( void )
{
 LeerPosicionPrecisa();

 if( abs(joy.x)<=DE ) joy.Padx = CEN_;
 else if( abs(joy.x - joy.minx)<=DE ) joy.Padx = IZQ_;
 else if( abs(joy.x - joy.maxx)<=DE ) joy.Padx = DER_;

 if( abs(joy.y)<=DE ) joy.Pady = CEN_;
 else if( abs(joy.y - joy.miny)<=DE ) joy.Pady = ARR_;
 else if( abs(joy.y - joy.maxy)<=DE ) joy.Pady = ABA_;

}

/*
void LeerPosicionEstadisca( void )
{
 unsigned Frec[2][800],moda[2];

 for(int i=0;i<800;i++)
 {
  Frec[0][i]=0;
  Frec[1][i]=0;
 }

    clock_t ini,t;
    ini=clock();

    //obtener dist de frecuencias de jx y jy
    do
    {
     LeerPosicion1();
     Frec[0][joy.jx]++;
     Frec[1][joy.jy]++;
     t=clock()-ini;
    } while( t<2 );

  //obtener modas para jx y jy

  for(i=0;i<800;i++)
  {
      if( Frec[0][i]>5 )
      {
       moda[0]=i;
       //gotoxy(1,2);cout<<Frec[0][i]<<" ";
       break;
      }

  }

    for(i=0;i<800;i++)
   {
       if( Frec[1][i]>5 )
       {
	moda[1]=i;
	//gotoxy(1,3);cout<<Frec[1][i]<<" ";
	break;
       }
   }

//   gotoxy(1,2);cout<<moda[0]<<" "<<moda[1]<<" ";

   joy.x = moda[0] - joy.cenx;
   joy.y = moda[1] - joy.ceny;

}
*/

//espera hasta que se presione un boton del joystick
//Actualiza los valores de la posicion del joystick
void Joy_Pausa( void )
{
 do
  LeerPosicionPrecisa();
 while( ObtenerEvento() != BOTON_DOWN );
}

#endif

/*
//EJEMPLO
main()
{
   clrscr();
   Calibrar_Joystick();

   ModoGrafico();
   cleardevice();

   Ventana_de_Calibracion_JoyPad(10,10,200,200);

   while ( !kbhit() )
    {

    LeerEventos();

    //LeerPosicionPrecisa();
    LeerPosicionPad();

    //Mostrar_Posicion_Joystick(10,10);
    Mostrar_Posicion_JoyPad(10,10,200,200);

    gotoxy(1,2);cout<<joy.Padx<<" "<<joy.Pady;

    }

   closegraph();
}
*/