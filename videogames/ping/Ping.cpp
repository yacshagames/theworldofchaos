/***********************************************************************
 ::: PING PONG :::
  >> Versión 1.0 11-III-2001

 Clásico juego de Ping Pong hecho mediante una rutina residente que
 modifica el vector de interrupción referido al control del teclado
 mediante el puerto 0x60.

 :::Programado por:::
 José Luis De La Cruz Lázaro
 YACSHA - Software & Desing 2002
  >> yacsha@elmundodelcaos.tk    
  >> www.elmundodelcaos.tk -> EL MUNDO DEL CAOS - Unlimited Programming
  >> www.foros3d.tk  -> Foros de discusión  Flash/ActionScript - C/C++

***********************************************************************/

#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <dos.h>

/****************************************************
Rutina Residente para controlar el TECLADO utilizando
directamente el puerto 0x60. Mediante SCANCODE.
*****************************************************/

#ifdef __cplusplus
    #define __CPPARGS ...
#else
    #define __CPPARGS
#endif

char Tecla[128];     //Tabla de booleanos para las consultas
unsigned char Actual; //Aqu¡ guardamos el c¢digo scan le¡do

//Procedimiento que limpia el buffer de teclado
void RutinaAux()
{

bucle:asm{
	 mov    ah,0x11
	 int    16h
	 jz     salida
	 mov    ah,0x10
	 int    16h
	 jmp    bucle
	 }
salida:
}

void interrupt (*IRQ9_PROC)(__CPPARGS); //Guardaremos en esta variable
				       //la rutina original controladora
				       //del teclado para poder llamarla
				       //desde nuestra funci¢n

//Esta funci¢n que ser  nuestro controlador de teclado. Se ejecutar  cada
//vez que se pulse o libere una tecla.
void interrupt Rutina(__CPPARGS)
{
  Actual = inportb(0x60);        //Leemos el c¢digo scan
  if( Actual<0x80 )              //¨es un c¢digo make?
       Tecla[Actual]=1;      //SI ponemos a true la var. correspondiente
  else
     Tecla[Actual-0x80]=0; //NO restamos 128 al c¢digo y ponemos a False
  IRQ9_PROC();                  //Llamamos al procedimiento original
  RutinaAux();                  //Limpia el buffer de teclado
}

//Procedimiento que salva la direcci¢n de la rutina BIOS del teclado y la
//sustituye por nuestro procedimiento
void Instalar()
{
 int i;
  for(i=0;i<128;i++)             //Inicializa la tabla de booleanos
    Tecla[i]=0;

  IRQ9_PROC = _dos_getvect(0x9); //Salva la direcci¢n original
  _dos_setvect(0x9,Rutina);      //Situa en la posici¢n 0x9 la direcci¢n de
				 //nuestra rutina
}

//Procedimiento que deja la posici¢n 9 de la tabla de vectores de interrupci¢n
//con la direcci¢n original.
void DesInstalar()
{
  _dos_setvect(0x9,IRQ9_PROC);      //Sit£a en la tabla la direcci¢n original
}
/*****************************FIN**************************/


#define diam 6
#define mov 20

int maxx,maxy;

class pelota{
    int dirx, diry;
    int x,y;
    int vel;
   public:
    pelota();
    int rebotar(int j1y,int j2y);
    void mover();
    void posicion();
   };

pelota::pelota(){
   x=maxx/2;
   y=maxy/2;
   randomize();
   dirx=random(2)+1;
   diry=random(2)+1;
   vel=3;
   };

int pelota::rebotar(int j1y,int j2y){
  int ret=0;
  if (x>maxx-10-(diam))
   if (y>j2y && (y+diam)<j2y+80)
    {
     dirx=0;
    // vel++;
    }
  if (x<10+(diam))
   if (y>j1y && (y+diam)<j1y+80)
    {
     dirx=1;
     //vel++;
    }
  if (x<diam)
   ret=1;
  if (x>maxx+diam)
   ret=1;
  if (y>maxy-(diam))
   diry=0;
  if (y<2)
   diry=1;
 return ret;
 };

void pelota::mover(){
  if (dirx==1)
   x+=vel;
  else
   x-=vel;
  if (diry==1)
   y+=vel;
  else
   y-=vel;
  };

void pelota::posicion(){
  circle(x,y,diam);
};

class jugador{
   public:
    int x,y,xa,ya;
    jugador (int j);
    void mover(int dir);
    void dibujar();
   };

jugador::jugador(int j){
  y=(maxy-80)/2;
  if (j==1)
   x=1;
  else
   x=maxx-11;
  xa=10;
  ya=80;
 };

void jugador::mover(int dir){
  if (dir==1)
   y=y-mov;
  else
   y=y+mov;
  if (y<=0)
   y=0;
  if (y+ya>maxy)
   y=maxy-ya;
 };

void jugador::dibujar(){
 rectangle(x,y,x+xa,y+ya);
 };

void main(){
 // char tec=0;
  int driver=DETECT, mode;
  initgraph (&driver, &mode, "");
  maxx=getmaxx();
  maxy=getmaxy();
  pelota ob;
  jugador j1(1),j2(2);


  Instalar(); //Instala controlador residente

  while( !Tecla[0x1] )
  {
     if ( Tecla[0x1E] ) //A
      j1.mover(1);
     if ( Tecla[0x2C] ) //Z
      j1.mover(2);
     if (Tecla[0x48])   //Arriba
      j2.mover(1);
     if (Tecla[0x50])   //Abajo
      j2.mover(2);

   delay(10);
   cleardevice();
   if(ob.rebotar(j1.y,j2.y))
    break;
   ob.mover();
   ob.posicion();
   j1.dibujar();
   j2.dibujar();
  }

  DesInstalar(); //desinstala controlador residente

  closegraph();
}
